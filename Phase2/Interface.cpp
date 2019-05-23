#include "Interface.h"
#include <iostream>
#include <sstream>
#include "GET_Handler.h"
#include "POST_Handler.h"
#include "Netflix.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"

#define POST "POST"
#define PUT "PUT"
#define GET "GET"
#define DELETE "DELETE"
#define ZERO 0

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
    		handle_command(input);
    }

    catch(const Exception &e)
    {
       cout << e.what();
    }
}

void Interface::handle_command(const vector<string> &command)
{
    try
    {
        if(command[0] == POST)
        {
            POST_Handler::get_instance() -> handle(command);
        }             

        else if(command[0] == GET)
        {
            GET_Handler::get_instance() -> handle(command);
        } 
        else
            throw BadRequest();
    }
    catch(const Exception &e)
    {
        throw;
    }         
}