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
#include "Admin.h"

#define POST "POST"
#define PUT "PUT"
#define GET "GET"
#define DELETE "DELETE"
#define MONEY "money"
#define LOG_OUT "logout"
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
    if(handle_if_is_admin(command))
        return;
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


bool Interface::handle_if_is_admin(const std::vector<std::string> &command)
{
    if(Admin::get_instance() -> is_logged_in())
    {
        handle_admin_command(command);
        return true;
    }
    return false;
}

void Interface::handle_admin_command(const vector<string> &command)
{
    try
    {
        if(command[0] == GET && command[1] == MONEY && command.size() == 2)
        {
            Netflix::get_instance() -> handle_admin_request();
        }
        else if(command[0] == POST && command[1] == LOG_OUT && command.size() == 2) 
        {
            Netflix::get_instance() -> log_out_admin();
        }            
        else
            throw BadRequest();
    }
    catch(const Exception &e)
    {
        throw;
    }         
}