#include "Netflix.h"
#include "UsersRepository.h"
#include "MoviesRepository.h"
#include "Publisher.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"
#include <iostream>

#define PUBLISHER "Publisher"
#define OK "OK"


using namespace std;

shared_ptr<Netflix> Netflix::the_instance=0;

Netflix::Netflix()
{
	Users_repository = UsersRepository :: get_instance();
	Movies_repository = MoviesRepository :: get_instance();
	income = 0;
}


shared_ptr<Netflix> Netflix::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<Netflix>(Netflix());
	return the_instance;
}

bool Netflix::is_loggedin_user(const vector<string> &input)
{
	if(current_user != NULL || (input[0] == "POST" && input[1] == "signup"))
	{
		return true;
	}
	if(input[1] != "signup")
		throw PermissionDenied();
}


void Netflix::add_member(string username, string pass, string email, int age, bool publisher)
{
	try
	{
		Users_repository->add_member(username, pass, email, age, publisher);
		set_current_user(Users_repository-> get_member(username, pass));
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}

void Netflix::login_member(string username, string pass)
{
	try
	{
		if(Users_repository->login_member(username, pass))
			set_current_user(Users_repository-> get_member(username, pass));
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}

void Netflix::set_current_user(shared_ptr<Member> user)
{
	current_user = user;
}

void Netflix::charge_account(double amount)
{
	current_user -> charge_your_account(amount);
	cout << OK << endl;
}

void Netflix::recieve_money()
{
	try
	{
		if(current_user->get_membership_type() != PUBLISHER)
			throw(PermissionDenied());
		int publishers_share = dynamic_pointer_cast<Publisher>(current_user) -> get_movie_sale_income();
		income -= publishers_share;
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}

void Netflix::follow(int user_id)
{
	try
	{
		shared_ptr<Member> publisher = Users_repository-> get_member(user_id);
		if((Users_repository-> get_member(user_id)) -> get_membership_type() == PUBLISHER)
		{
			current_user -> follow_publisher(publisher);
			dynamic_pointer_cast<Publisher>(publisher)-> add_followers(current_user);
			publisher -> recieve_notification("User "+ current_user->get_username()+ " with id "+
			to_string(current_user->get_id()) +" follow you"); 
			cout << OK << endl;
		}
		else
			throw NotFound();
	}
 	catch(const Exception &e)
	{
		cout << e.what();	
	}
}


void Netflix::get_followers()
{
	try
	{
		if(current_user->get_membership_type() != PUBLISHER)
			throw(PermissionDenied());
		dynamic_pointer_cast<Publisher>(current_user) -> show_followers();
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}


void Netflix::get_unread_notifications()
{
	current_user -> get_unread_messages();
}

void Netflix::get_read_notifications(int limit)
{
	current_user -> get_read_messages(limit);
}

void Netflix::post_film(string name, int year, int length,
    double price, string summary,  string director)
{
	try
	{
		if(current_user->get_membership_type() != PUBLISHER)
			throw(PermissionDenied());
		Movies_repository-> add_movie(name, year, length,
			price, summary, director, dynamic_pointer_cast<Publisher>(current_user));
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}

void Netflix::edit_film(int film_id, string name, int year, int length,
    double price, string summary,  string director)
{
	try
	{
		if(current_user->get_membership_type() != PUBLISHER)
			throw(PermissionDenied());
		if((Movies_repository->get_movie(film_id)) -> get_publisher() != 
							dynamic_pointer_cast<Publisher>(current_user))
			throw(PermissionDenied());

		Movies_repository-> edit_movie(film_id, name, year, length,
			price, summary, director);
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}


void Netflix::show_publishers_films(const string &name, int min_year,
	int max_year, double min_rate, double price, const string &director)
{
	try
	{
		if(current_user->get_membership_type() != PUBLISHER)
			throw(PermissionDenied());
		Movies_repository-> show_movies(dynamic_pointer_cast<Publisher>(current_user), 
						name, min_year, max_year, min_rate, price, director);
	}
	catch(const Exception &e)
	{
		cout << e.what();
	}
}


void Netflix::show_all_films(const string &name, int min_year,
	int max_year, double min_rate, double price, const string &director)
{
	try
	{
		Movies_repository-> show_all_movies(name, min_year, max_year, min_rate, price, director);
	}
	catch(const Exception &e)
	{
		cout << e.what();
	}
}


void Netflix::show_one_single_film(int film_id)
{
	try
	{
		Movies_repository -> show_this_film(film_id);
	}
	catch(const Exception &e)
	{
		cout << e.what();
	}
}


void Netflix::remove_film(int film_id)
{
	try
	{
		if(current_user->get_membership_type() != PUBLISHER)
			throw(PermissionDenied());

		Movies_repository-> remove_movie(film_id);
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}

void Netflix::buy_film(int film_id)
{
	try
	{
		shared_ptr<Movie> movie = Movies_repository->get_movie(film_id);
		current_user -> buy_film(movie);
		shared_ptr<Publisher> publisher = movie->get_publisher();
		publisher -> earn_money(movie);
		income += movie->get_price();
		publisher -> recieve_notification("User " +current_user->get_username() +" with id " + 
		to_string(current_user->get_id()) + " buy your film " + movie->get_name() + " with id "+ to_string(movie->get_id()));
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}



void Netflix::show_purchased_films(const string &name, double price, int min_year,
	int max_year, const string &director)
{
	current_user-> display_purchased_films(name , price, min_year, max_year ,director);
}


void Netflix:: rate_film(int film_id, int score)
{
	try
	{
		shared_ptr<Movie> movie = Movies_repository->get_movie(film_id);
		if(!(current_user-> has_purchased_this_film(movie)))
			throw PermissionDenied();
		movie -> set_score(score, current_user->get_username());
		shared_ptr<Publisher> publisher = movie->get_publisher();
		publisher -> recieve_notification("User " +current_user->get_username() +" with id " + 
		to_string(current_user->get_id()) + " rate your film " + movie->get_name() + " with id "+ to_string(movie->get_id()));
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}

void Netflix::comment_film(int film_id, const string &content)
{
	try
	{
		shared_ptr<Movie> movie = Movies_repository->get_movie(film_id);
		if( !(current_user-> has_purchased_this_film(movie)))
			throw PermissionDenied();
		movie -> set_comment(content, current_user);
		shared_ptr<Publisher> publisher = movie->get_publisher();
		publisher -> recieve_notification("User "+current_user->get_username()+" with id " + 
		to_string(current_user->get_id())+" comment on your film "+ movie->get_name()+ " with id "+ to_string(movie->get_id()));
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}

void Netflix::delete_comment(int film_id, int comment_id)
{
	try
	{
		shared_ptr<Movie> movie = Movies_repository->get_movie(film_id);
		if(current_user->get_membership_type() != PUBLISHER)
			throw(PermissionDenied());
		if((Movies_repository->get_movie(film_id)) -> get_publisher() != 
							dynamic_pointer_cast<Publisher>(current_user))
			throw(PermissionDenied());

		movie -> remove_comment(comment_id);
		cout << OK << endl;
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}


void Netflix::reply_to_film_comments(int film_id, int comment_id, const string &content)
{
	try
	{
		shared_ptr<Movie> movie = Movies_repository->get_movie(film_id);
		if(movie->get_publisher() != current_user)
			throw PermissionDenied();
		string name_of_movie = movie->get_name();
		movie-> set_reply_to_comment(comment_id, content, name_of_movie, current_user);
		cout << OK << endl;	
	}
	catch(const Exception &e)
	{
		cout << e.what();	
	}
}