#include "DELETE_Handler.h"

using namespace std;

shared_ptr<DELETE_Handler> DELETE_Handler::the_instance =0;

shared_ptr<DELETE_Handler> DELETE_Handler::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<DELETE_Handler>(DELETE_Handler());
	return the_instance;
}


void DELETE_Handler::handle(const vector<string> &command)
{
	try
	{
		if(command[1] == FILMS)
		{
			check_syntax_errors(command);
	        handle_removing_film(command);
		}

		else if(command[1] == COMMENTS)
		{
			check_syntax_errors(command);
	        handle_deleting_comment(command);
		}
		else
			throw NotFound();
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


void DELETE_Handler::handle_removing_film(const vector<string> &command)
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




void DELETE_Handler::handle_deleting_comment(const vector<string> &command)
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
