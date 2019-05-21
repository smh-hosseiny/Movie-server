#include "Interface.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Netflix.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"

#define ZERO 0
#define USERNAME "username"
#define PASSWORD "password"
#define AGE "age"
#define EMAIL "email"
#define PUBLISHER "publisher"
#define POST "POST"
#define PUT "PUT"
#define GET "GET"
#define DELETE "DELETE"
#define NOTIFICATIONS "notifications"
#define QUESTION_SIGN "?"
#define LIMIT "limit"
#define READ "read"
#define FILMS "films"
#define NAME "name"
#define YEAR "year"
#define LENGTH "length"
#define PRICE "price"
#define SUMMARY "summary"
#define DIRECTOR "director"
#define PUBLISHED "published"
#define BUY "buy"
#define PURCHASED "purchased"
#define RATE "rate"
#define COMMENTS "comments"
#define SCORE "score"
#define CONTENT "content"
#define MIN_YEAR "min_year"
#define MAX_YEAR "max_year"
#define MIN_RATE "min_rate"
#define REPLIES "replies"
#define COMMENT_ID "comment_id"

#define SIGNUP "signup"
#define LOGIN "login"
#define MONEY "money"
#define AMOUNT "amount"
#define FOLLOWERS "followers"
#define USER_ID "user_id"
#define FILM_ID "film_id"

using namespace std;

shared_ptr<Interface> Interface::the_instance =0;

shared_ptr<Interface> Interface::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<Interface>(Interface());
	return the_instance;
}

void Interface::run_netflix()
{
	string command;
	while(getline(cin, command,'\n'))
	{
		if(command != "")
			handle_input(split(command));
	}   
}


vector<string> Interface::split(string input)
{
	vector<string> splited;
    string token={};
    stringstream tokenStream(input);
    while (getline(tokenStream, token,' '))
        splited.push_back(token); 
    return splited;
}



void Interface::handle_input(const vector<string> &input)
{
    try
    {
    	if(Netflix::get_instance() -> is_loggedin_user(input))
    		identify_command(input);
    }

    catch(const Exception &e)
    {
       cout << e.what();
    }
}


void Interface::identify_command(const vector<string> &command)
{
    if(command[0] != POST && command[0] != PUT &&
                 command[0] != GET && command[0] != DELETE)
            throw BadRequest();

	try
	{
	    if(command[0] == POST)
	    {
	        handle_post_command(command);
	    }             

	    else if(command[0] == GET)
	    {
	        handle_get_command(command);
	    } 

	    else if(command[0] == PUT)
	    {
	        handle_put_command(command);
	    } 

	    else if(command[0] == DELETE)
	    {
	        handle_delete_command(command);
	    } 
    }
    catch(const Exception &e)
    {
    	throw;
    }         
}

string Interface::get_parameter(const vector<string> &input, string parameter)
{
    for(int i=0; i<input.size(); i++)
    {
        if(input[i] == parameter && i != input.size()-1)
            return input[i+1];
    }
    throw BadRequest();
}


bool Interface::isNumber(const string &input) 
{ 
    for(auto &elem : input)
    { 
        if(!isdigit(elem)) 
            return false;
    } 
    return true; 
} 


int Interface::get_film_id(const vector<string> &input)
{
	if(!isNumber(get_parameter(input, FILM_ID)))
	{
		throw BadRequest();
	}
	int film_id =  stoi(get_parameter(input, FILM_ID));
	return film_id;
}

bool Interface::is_publisher(const vector<string> &input)
{
    bool publisher;
    for(int i=0; i<input.size(); i++)
    {
        if(input[i] == PUBLISHER)
        {
            input[i+1] == "true" ? publisher = true : publisher = false;
            return publisher;
        }
    }
    return false;
}


void Interface::check_syntax_errors(const vector<string> &input)
{
    if(input[2] != QUESTION_SIGN)
        throw BadRequest();
}


void Interface::handle_delete_command(const vector<string> &command)
{
	try
	{
		if(command[1] == FILMS)
		{
			check_syntax_errors(command);
	        handle_removing_film(command);
		}

		if(command[1] == COMMENTS)
		{
			check_syntax_errors(command);
	        handle_deleting_comment(command);
		}
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_put_command(const vector<string> &command)
{
	try
	{
		if(command[1] == FILMS)
		{
			check_syntax_errors(command);
	        handle_editing_film(command);
		}
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_get_command(const vector<string> &command)
{
    if(command[1] == NOTIFICATIONS && command.size() == 2)
    {
        Netflix :: get_instance() -> get_unread_notifications();
    }

    else if(command[1] == NOTIFICATIONS && command[3] == QUESTION_SIGN)
    {
    	if(command[2] == READ && command[4] == LIMIT)
    	{
	    	int limit = stoi(get_parameter(command, LIMIT));
	        Netflix :: get_instance() -> get_read_notifications(limit);
        }
    }
    else if(command[1] == PUBLISHED)
    {
    	if(command.size() > 2)
        	check_syntax_errors(command);
    	handle_showing_films(command);
    }

    else if(command[1] == FILMS)
    {
    	if(command.size() > 2)
        	check_syntax_errors(command);
    	handle_displaying_all_films(command);
    }

    else if(command[1] == PURCHASED)
    {
    	if(command.size() > 2)
        	check_syntax_errors(command);
        handle_showing_purchased_films(command);
    }

    else if(command[1] == FOLLOWERS)
    {
        handle_displaying_followers();
    }
    else
    	throw BadRequest();
}



void Interface::handle_post_command(const vector<string> &command)
{
	try
	{
	    if(command[1] == SIGNUP)
	    {
	        check_syntax_errors(command);
	        handle_signup(command);
	    }

	    if(command[1] == LOGIN)
	    {
	        check_syntax_errors(command);
	        handle_login(command);
	    }

	    if(command[1] == MONEY)
	    {
	    	if(command.size() == 2)
	    	{
	    		handle_getting_money();
	    	}
	    	else
	    	{
		        check_syntax_errors(command);
		        handle_charging_account(command);
	        }
	    }

	    if(command[1] == FOLLOWERS)
	    {
	        check_syntax_errors(command);
	        handle_following(command);
	    }

	    if(command[1] == FILMS)
	    {
	        check_syntax_errors(command);
	        handle_adding_film(command);
	    }

	    if(command[1] == BUY)
	    {
	        check_syntax_errors(command);
	        handle_buying_film(command);
	    }

	    if(command[1] == RATE)
	    {
	        check_syntax_errors(command);
	        handle_rating_film(command);
	    }

	    if(command[1] == COMMENTS)
	    {
	        check_syntax_errors(command);
	        handle_commenting_film(command);
	    }

		if(command[1] == REPLIES)
	    {
	        check_syntax_errors(command);
	        handle_replying(command);
	    }
    }
    catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_signup(const vector<string> &input)
{
	try
	{
	    string username = get_parameter(input, USERNAME);
	    string password = get_parameter(input, PASSWORD);
	    string email = get_parameter(input, EMAIL);
	    int age = stoi( get_parameter(input, AGE));
	    bool publisher = is_publisher(input);
	    Netflix :: get_instance() ->add_member(username, password, email, age, publisher);
    }
    catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_login(const vector<string> &input)
{
	try
	{
	   string username = get_parameter(input, USERNAME);
	   string password = get_parameter(input, PASSWORD);
	   Netflix :: get_instance() -> login_member(username, password);
	}
	catch(const Exception &e)
    {
    	throw;
    }
}



void Interface::handle_charging_account(const vector<string> &input)
{
	try
	{
	    double amount = stoi(get_parameter(input, AMOUNT));
	    Netflix :: get_instance() -> charge_account(amount);
    }
    catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_getting_money()
{
    Netflix :: get_instance() -> recieve_money();
}


void Interface::handle_following(const vector<string> &input)
{
	try
	{
	    int id = stoi(get_parameter(input, USER_ID));
	    Netflix :: get_instance() -> follow(id);
    }
    catch(const Exception &e)
    {
    	throw;
    }
}



void Interface::handle_displaying_followers()
{
	try
	{
	    Netflix :: get_instance() -> get_followers();
    }
    catch(const Exception &e)
    {
    	throw;
    }
}



void Interface::handle_adding_film(const vector<string> &input)
{
	try
	{
	    string name =  get_parameter(input, NAME);
	    int year =  stoi(get_parameter(input, YEAR));
	    int length =  stoi(get_parameter(input, LENGTH));
	    double price =  stoi(get_parameter(input, PRICE));
	    string summary =  get_parameter(input, SUMMARY);
	    string director =  get_parameter(input, DIRECTOR);
	    Netflix::get_instance() -> post_film(name, year, length, price, summary, director);
    }
    catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::set_changed_parameters(const vector<string> &input, string &name, int &year, int &length,
 								double &price,	string &summary, string &director)
{
	if(find(input.begin(), input.end(), NAME) != input.end())
    	name =  get_parameter(input, NAME);
    if(find(input.begin(), input.end(), YEAR) != input.end())
	    year =  stoi(get_parameter(input, YEAR));
	if(find(input.begin(), input.end(), LENGTH) != input.end())
	    length =  stoi(get_parameter(input, LENGTH));
	if(find(input.begin(), input.end(), PRICE) != input.end())
	    price =  stoi(get_parameter(input, PRICE));
	if(find(input.begin(), input.end(), SUMMARY) != input.end())
	    summary =  get_parameter(input, SUMMARY);
	if(find(input.begin(), input.end(), DIRECTOR) != input.end())
	    director =  get_parameter(input, DIRECTOR);
}

void Interface::handle_editing_film(const vector<string> &input)
{
 	string name;
    int year=0 ;
    int length=0;
    double price=0;
    string summary;
    string director;
	try
	{
		int film_id =  get_film_id(input);
		set_changed_parameters(input, name, year, length, price, summary, director);
	    Netflix::get_instance() -> edit_film(film_id, name, year, length, price, summary, director);
    }
    catch(const Exception &e)
    {
    	throw;
    }
}



void Interface::set_filters(const vector<string> &input, string &name, int &min_year,
	int &max_year, double &min_rate, double &price, string &director)
{
	if(find(input.begin(), input.end(), NAME) != input.end())
    	name =  get_parameter(input, NAME);
    if(find(input.begin(), input.end(), MIN_YEAR) != input.end())
	    min_year =  stoi(get_parameter(input, MIN_YEAR));
	if(find(input.begin(), input.end(), MAX_YEAR) != input.end())
	    max_year =  stoi(get_parameter(input, MAX_YEAR));
	if(find(input.begin(), input.end(), PRICE) != input.end())
	    price =  stod(get_parameter(input, PRICE));
	if(find(input.begin(), input.end(), MIN_RATE) != input.end())
	    min_rate =  stod(get_parameter(input, MIN_RATE));
	if(find(input.begin(), input.end(), DIRECTOR) != input.end())
	    director =  get_parameter(input, DIRECTOR);
}


void Interface::handle_showing_films(const vector<string> &command)
{
	string name;
    int min_year=0;
    int max_year=0;
    double price=0;
    double min_rate=0;
    string director;

    try
	{
		if(command.size() >2)
			set_filters(command, name, min_year, max_year, min_rate, price, director);
	   	Netflix::get_instance() -> show_publishers_films(name, min_year, max_year, min_rate, price, director);
    }
    catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_displaying_all_films(const vector<string> &command)
{
	if(find(command.begin(), command.end(), FILM_ID) != command.end())
	{
		int film_id =  get_film_id(command);
		Netflix::get_instance() -> show_one_single_film(film_id);
	}

	else
	{
		string name;
	    int min_year=0;
	    int max_year=0;
	    double price=0;
	    double min_rate=0;
	    string director;

	    try
		{
			if(command.size() >2)
				set_filters(command, name, min_year, max_year, min_rate, price, director);
		   	Netflix::get_instance() -> show_all_films(name, min_year, max_year, min_rate, price, director);
	    }
	    catch(const Exception &e)
	    {
	    	throw;
	    }
    }
}


void Interface::handle_showing_purchased_films(const vector<string> &command)
{
	string name;
    int min_year=0;
    int max_year=0;
    double price=0;
    double min_rate=0;
    string director;

    try
	{
		if(command.size() >2)
			set_filters(command, name, min_year, max_year, min_rate, price, director);
		Netflix::get_instance() -> show_purchased_films(name , price, min_year, max_year, director);
	}
	 catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_removing_film(const vector<string> &command)
{
	try
	{
		int film_id =  get_film_id(command);
		Netflix::get_instance() -> remove_film(film_id);
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_buying_film(const vector<string> &command)
{
	try
	{
		int film_id =  get_film_id(command);
		Netflix::get_instance() -> buy_film(film_id);
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_rating_film(const vector<string> &command)
{
	try
	{
		int film_id =  get_film_id(command);
		int score =  stoi(get_parameter(command, SCORE));
		if(score < 1 || score >10)
			throw BadRequest();
		Netflix::get_instance() -> rate_film(film_id, score);
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_commenting_film(const vector<string> &command)
{
	try
	{
		int film_id =  get_film_id(command);
		string content =  get_parameter(command, CONTENT);
		Netflix::get_instance() -> comment_film(film_id, content);
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_deleting_comment(const vector<string> &command)
{
	try
	{
		int film_id =  get_film_id(command);
		int comment_id =  stoi(get_parameter(command, COMMENT_ID));
		Netflix::get_instance() -> delete_comment(film_id, comment_id);
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void Interface::handle_replying(const vector<string> &command)
{
	try
	{
		int film_id =  get_film_id(command);
		int comment_id =  stoi(get_parameter(command, COMMENT_ID));
		string content = get_parameter(command, CONTENT);
		Netflix::get_instance() -> reply_to_film_comments(film_id, comment_id, content);
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


