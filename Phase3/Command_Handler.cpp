#include "Command_Handler.h"

using namespace std;


string Command_Handler::get_parameter(const vector<string> &input, string parameter)
{
    for(int i=0; i<input.size()-1; i++)
    {
        if(input[i] == parameter)
            return input[i+1];
    }
    throw BadRequest();
}


bool Command_Handler::isNumber(const string &input) 
{ 
    for(auto &elem : input)
    { 
        if(!isdigit(elem)) 
            return false;
    } 
    return true; 
} 


int Command_Handler::get_film_id(const vector<string> &input)
{
	if(!isNumber(get_parameter(input, FILM_ID)))
	{
		throw BadRequest();
	}
	int film_id =  stoi(get_parameter(input, FILM_ID));
	return film_id;
}


bool Command_Handler::is_publisher(const vector<string> &input)
{
    bool publisher;
    for(int i=0; i<input.size(); i++)
    {
        if(input[i] == PUBLISHER)
        {
            input[i+1] == T_R_U_E ? publisher = true : publisher = false;
            return publisher;
        }
    }
    return false;
}


void Command_Handler::check_syntax_errors(const vector<string> &input)
{
    if(input[2] != QUESTION_SIGN)
        throw BadRequest();
}