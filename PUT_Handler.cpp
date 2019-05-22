#include "PUT_Handler.h"

using namespace std;

shared_ptr<PUT_Handler> PUT_Handler::the_instance =0;

shared_ptr<PUT_Handler> PUT_Handler::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<PUT_Handler>(PUT_Handler());
	return the_instance;
}



void PUT_Handler::handle(const vector<string> &command)
{
	try
	{
		if(command[1] == FILMS)
		{
			check_syntax_errors(command);
	        handle_editing_film(command);
		}
		else
			throw NotFound();
	}
	catch(const Exception &e)
    {
    	throw;
    }
}



void PUT_Handler::set_changed_parameters(const vector<string> &input, string &name, int &year, int &length,
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

void PUT_Handler::handle_editing_film(const vector<string> &input)
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
