#include "Member.h"
#include "Movie.h"
#include "MoviesRepository.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"
#include <algorithm>
#include <iostream>

using namespace std;


Member::Member(string user_name, string pass, string e_mail, int Age, int  id)
{
	ID = id;
	username = user_name;
	password = pass;
	email = e_mail;
	age = Age;
	account = 0;
}

void Member::charge_your_account(double amount)
{
	account += amount;
}

string Member::get_username()
{
	return username;
}

string Member::get_password()
{
	return password;
}

string Member::get_email()
{
	return email;
}

int Member::get_id()
{
	return ID;
}


vector<shared_ptr<Movie> > Member::get_purchased_movies()
{
	return my_movies;
}

vector<int> Member::get_purchased_movies_ids()
{
	vector<int> my_movies_ids;
	for(auto &elem : my_movies)
		my_movies_ids.push_back(elem->get_id());
	return my_movies_ids;
}



bool Member::follow_publisher(shared_ptr<Member> publisher)
{
	if(find(followings.begin(), followings.end(), publisher) == followings.end())
	{
		followings.push_back(publisher);
		return true;
	}
	return false;
}

void Member::recieve_notification(string message)
{
	unread_messages.push_back(message);
}


void Member::display_unread_messages()
{
	for(int i=0; i<unread_messages.size(); i++)
	{
		cout << i+1 <<". "<< unread_messages[unread_messages.size()-i-1] << "." <<endl;
		read_messages.push_back(unread_messages[i]);
	}
}


void Member::get_unread_messages()
{
	cout << "#. Notification Message\n";
	if(unread_messages.size() > 0)
	{
		display_unread_messages();
		unread_messages.clear();
	}
}


void Member::display_read_messages(int number_of_messages_to_display)
{
	if(read_messages.size() > 0)
	{
		for(int i=0; i<number_of_messages_to_display; i++)
			cout << i+1 <<". "<< read_messages[read_messages.size()-i-1] << endl;
	}
}



void Member::get_read_messages(int limit)
{
	int number_of_read_messages = read_messages.size();
	int number_of_messages_to_display;
	(limit <= number_of_read_messages) ? number_of_messages_to_display= limit : 
						number_of_messages_to_display= number_of_read_messages;
	cout << "#. Notification Message\n";
	display_read_messages(number_of_messages_to_display);
}


void Member::buy_film(shared_ptr<Movie> movie)
{
	try
	{
		if(movie->get_price() > account)
			throw PermissionDenied();
		if(find(my_movies.begin(), my_movies.end(), movie) == my_movies.end())
		{
			my_movies.push_back(movie);
			account -= movie->get_price();
		}
	}
	catch(const Exception &e)
	{
		e.what();
	}
}

void Member::display_purchased_films(const string &name, double price, int min_year,
	int max_year, const string &director)
{
	vector<shared_ptr<Movie> > my_filtered_movies = MoviesRepository::filter(my_movies, name,
	 min_year, max_year, 0, price, director);
	MoviesRepository::display_films_info(my_filtered_movies);
}


bool Member:: has_purchased_this_film(shared_ptr<Movie> movie)
{
	for(auto elem : my_movies)
	{
		if(elem == movie)
			return true;
	}
	return false;
}


double Member::get_money()
{
	return account;
}

string Member::get_membership_type()
{}