#include "POST_Handler.h"

using namespace std;

shared_ptr<POST_Handler> POST_Handler::the_instance =0;

shared_ptr<POST_Handler> POST_Handler::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<POST_Handler>(POST_Handler());
	return the_instance;
}

void POST_Handler::handle(const vector<string> &command)
{
	try
	{
	    if(command[1] == SIGNUP)
	    {
	        check_syntax_errors(command);
	        handle_signup(command);
	    }

	    else if(command[1] == LOGIN)
	    {
	        check_syntax_errors(command);
	        handle_login(command);
	    }

	    else if(command[1] == MONEY)
	    {
	    	if(command.size() == 2)
	    		handle_getting_money();
	    	else
	    	{
		        check_syntax_errors(command);
		        handle_charging_account(command);
	        }
	    }

	    else if(command[1] == FOLLOWERS)
	    {
	        check_syntax_errors(command);
	        handle_following(command);
	    }

	    else if(command[1] == FILMS)
	    {
	        check_syntax_errors(command);
	        handle_adding_film(command);
	    }

	    else if(command[1] == BUY)
	    {
	        check_syntax_errors(command);
	        handle_buying_film(command);
	    }

	    else if(command[1] == RATE)
	    {
	        check_syntax_errors(command);
	        handle_rating_film(command);
	    }

	    else if(command[1] == COMMENTS)
	    {
	        check_syntax_errors(command);
	        handle_commenting_film(command);
	    }

		else if(command[1] == REPLIES)
	    {
	        check_syntax_errors(command);
	        handle_replying(command);
	    }
	    else
	    	throw NotFound();
    }
    catch(const Exception &e)
    {
    	throw;
    }
}



void POST_Handler::handle_signup(const vector<string> &input)
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


void POST_Handler::handle_login(const vector<string> &input)
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


void POST_Handler::handle_getting_money()
{
    Netflix :: get_instance() -> recieve_money();
}

void POST_Handler::handle_following(const vector<string> &input)
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


void POST_Handler::handle_charging_account(const vector<string> &input)
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


void POST_Handler::handle_adding_film(const vector<string> &input)
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



void POST_Handler::handle_buying_film(const vector<string> &command)
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


void POST_Handler::handle_rating_film(const vector<string> &command)
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


void POST_Handler::handle_commenting_film(const vector<string> &command)
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



void POST_Handler::handle_replying(const vector<string> &command)
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


