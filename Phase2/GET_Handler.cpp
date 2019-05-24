#include "GET_Handler.h"


using namespace std;

shared_ptr<GET_Handler> GET_Handler::the_instance =0;

shared_ptr<GET_Handler> GET_Handler::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<GET_Handler>(GET_Handler());
	return the_instance;
}


void GET_Handler::handle(const vector<string> &command)
{
	if(command[1] == NOTIFICATIONS && command.size() == 2)
    {
        Netflix :: get_instance() -> get_unread_notifications();
    }

    else if(command[1] == NOTIFICATIONS)
    {
    	check_syntax_errors(command);
    	if(command[2] == READ && command[4] == LIMIT)
    	{
	    	int limit = stoi(get_parameter(command, LIMIT));
	        Netflix :: get_instance() -> get_read_notifications(limit);
        }
        else
        	throw BadRequest();
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

    else if(command[1] == FOLLOWERS  && command.size() == 2)
    {
        handle_displaying_followers();
    }

    else if(command[1] == MONEY)
    {
        handle_showing_member_money();
    }
    else
    	throw NotFound();
}



void GET_Handler::handle_displaying_followers()
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




void GET_Handler::set_filters(const vector<string> &input, string &name, int &min_year,
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


void GET_Handler::handle_showing_films(const vector<string> &command)
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


void GET_Handler::handle_displaying_all_films(const vector<string> &command)
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


void GET_Handler::handle_showing_purchased_films(const vector<string> &command)
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


void GET_Handler::handle_showing_member_money()
{
    Netflix::get_instance() -> get_members_money();
}