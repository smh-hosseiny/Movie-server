#include "POST_Handler.h"
#include "Netflix.h"

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
	    if(command[1] == SIGNUP && (command.size() == 11 || command.size() == 13))
	    {
	        check_syntax_errors(command);
	        handle_signup(command);
	    }

	    else if(command[1] == LOGIN && command.size() == 7)
	    {
	        check_syntax_errors(command);
	        handle_login(command);
	    }

	    else if(command[1] == MONEY)
	    {
	    	if(command.size() == 2)
	    		handle_getting_money();
	    	else if (command.size() == 5)
	    	{
		        check_syntax_errors(command);
		        handle_charging_account(command);
	        }
	    }

	    else if(command[1] == FOLLOWERS && command.size() == 5)
	    {
	        check_syntax_errors(command);
	        handle_following(command);
	    }

	    else if(command[1] == FILMS)
	    {
	        check_syntax_errors(command);
	        handle_adding_film(command);
	    }

	    else if(command[1] == BUY && command.size() == 5)
	    {
	        check_syntax_errors(command);
	        handle_buying_film(command);
	    }

	    else if(command[1] == RATE && command.size() == 7)
	    {
	        check_syntax_errors(command);
	        handle_rating_film(command);
	    }

	    else if(command[1] == COMMENTS && command.size() == 7)
	    {
	        check_syntax_errors(command);
	        handle_commenting_film(command);
	    }


		else if(command[1] == REPLIES && command.size() == 9)
	    {
	        check_syntax_errors(command);
	        handle_replying(command);
	    }

	    else if(command[1] == PUT_FILMS)
		{
			check_syntax_errors(command);
	        handle_editing_film(command);
		}


		else if(command[1] == DELETE_FILMS && command.size() == 5)
		{
			check_syntax_errors(command);
	        handle_removing_film(command);
		}

		else if(command[1] == DELETE_COMMENTS && command.size() == 7)
		{
			check_syntax_errors(command);
	        handle_deleting_comment(command);
		}

		else if(command[1] == LOG_OUT && command.size() == 2)
		{
			handle_logout();
		}

	    else
	    	throw NotFound();
    }
    catch(const Exception &e)
    {
    	throw;
    }
}


void POST_Handler::check_if_there_is_no_logged_in_member()
{
	if(Netflix::get_instance() -> get_current_user() != NULL)
		throw BadRequest();
}


void POST_Handler::handle_signup(const vector<string> &input)
{
	try
	{
		check_if_there_is_no_logged_in_member();
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
	   //check_if_there_is_no_logged_in_member();
	   if(handle_if_its_admin(username, password))
			return;
	   Netflix :: get_instance() -> login_member(username, password);
	}
	catch(const Exception &e)
    {
    	throw;
    }
}


bool POST_Handler::handle_if_its_admin(const string &username, const string &password)
{
	if(username == ADMIN && password == ADMIN)
	{
		Netflix::get_instance()->login_admin();
		return true;
	}
	return false;
}

void POST_Handler::handle_logout()
{
	try
	{
	   Netflix :: get_instance() -> logout_member();
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




void POST_Handler::set_changed_parameters(const vector<string> &input, string &name, int &year, int &length,
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

void POST_Handler::apply_editing_film(const vector<string> &input)
{
	string name;
    int year=0 ;
    int length=0;
    double price=0;
    string summary;
    string director;

	int film_id =  get_film_id(input);
	set_changed_parameters(input, name, year, length, price, summary, director);
    Netflix::get_instance() -> edit_film(film_id, name, year, length, price, summary, director);

}
void POST_Handler::handle_editing_film(const vector<string> &input)
{
	try
	{
		apply_editing_film(input);
    }
    catch(const Exception &e)
    {
    	throw;
    }
}




void POST_Handler::handle_removing_film(const vector<string> &command)
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




void POST_Handler::handle_deleting_comment(const vector<string> &command)
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


