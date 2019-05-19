#include <iostream>
#include <sstream>
#include <algorithm>
#include "Interface.h"
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

#define SIGNUP "signup"
#define LOGIN "login"
#define MONEY "money"
#define AMOUNT "amount"
#define FOLLOWERS "followers"
#define USER_ID "user_id"
#define FILM_ID "film_id"


using namespace std;

vector<string> read_input()
{
    vector<string> input;
    string Command;
    while (getline(cin, Command,'\n'))
        input.push_back(Command);
    return input;
}    


vector<vector<string> > split(vector<string> input)
{
	vector<vector<string> > splited(input.size());
    for (int j = ZERO; j < input.size(); j++)
    {
        string token={};
        stringstream tokenStream(input[j]);
        while (getline(tokenStream, token,' '))
        {
            splited[j].push_back(token); 
        }
    }
    return splited;
}


vector<vector<string> > get_input()
{
    return split(read_input());
}


string get_parameter(const vector<string> &input, string parameter)
{
    for(int i=0; i<input.size(); i++)
    {
        if(input[i] == parameter && i != input.size()-1)
            return input[i+1];
    }
    throw BadRequest();
}


bool isNumber(const string &input) 
{ 
    for(auto &elem : input)
    { 
        if(!isdigit(elem)) 
            return false;
    } 
    return true; 
} 


int get_film_id(const vector<string> &input)
{
	if(!isNumber(get_parameter(input, FILM_ID)))
	{
		throw BadRequest();
	}
	int film_id =  stoi(get_parameter(input, FILM_ID));
	return film_id;
}

bool is_publisher(const vector<string> &input)
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


void check_syntax_errors(const vector<string> &input)
{
    if(input[2] != QUESTION_SIGN)
        throw BadRequest();
}


void handle_input(const vector<vector<string> > &input)
{
    for(auto &elem : input)
    {
        try
        {
        	identify_command(elem);
        }

        catch(const Exception &e)
        {
           cerr << e.what();
        }
    }
}


void identify_command(const vector<string> &command)
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

void handle_delete_command(const vector<string> &command)
{
	try
	{
		if(command[1] == FILMS)
		{
			check_syntax_errors(command);
	        handle_removing_film(command);
		}
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void handle_put_command(const vector<string> &command)
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


void handle_get_command(const vector<string> &command)
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
    	check_syntax_errors(command);
        handle_showing_films(command);
    }
    else if(command[1] == PURCHASED)
    {
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



void handle_post_command(const vector<string> &command)
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
    }
    catch(const Exception &e)
    {
    	throw;
    }
}


void handle_signup(const vector<string> &input)
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


void handle_login(const vector<string> &input)
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



void handle_charging_account(const vector<string> &input)
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


void handle_getting_money()
{
    Netflix :: get_instance() -> recieve_money();
}


void handle_following(const vector<string> &input)
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



void handle_displaying_followers()
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



void handle_adding_film(const vector<string> &input)
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


void set_changed_parameters(const vector<string> &input, string &name, int &year, int &length,
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

void handle_editing_film(const vector<string> &input)
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


void handle_showing_films(const vector<string> &command)
{
	Netflix::get_instance() -> show_films();
}


void handle_showing_purchased_films(const vector<string> &command)
{
	Netflix::get_instance() -> show_purchased_films();
}


void handle_removing_film(const vector<string> &command)
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


void handle_buying_film(const vector<string> &command)
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


void handle_rating_film(const vector<string> &command)
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


void handle_commenting_film(const vector<string> &command)
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


