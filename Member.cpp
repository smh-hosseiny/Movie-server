#include "Member.h"
#include "Movie.h"
#include "MoviesRepository.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"
#include <algorithm>
#include <iostream>

using namespace std;


Member::Member(string user_name, string pass, string e_mail, int Age, int  id)
{
	ID = id;
	username = user_name;
	password = pass;
	email = e_mail;
	age = Age;
	account = 0;
}

void Member::charge_your_account(double amount)
{
	this-> account += amount;
}

string Member::get_username()
{
	return username;
}

string Member::get_password()
{
	return password;
}

string Member::get_email()
{
	return email;
}

int Member::get_id()
{
	return ID;
}

void Member::follow_publisher(shared_ptr<Member> publisher)
{
	if(find(followings.begin(), followings.end(), publisher) == followings.end())
		followings.push_back(publisher);
}

void Member::recieve_notification(string message)
{
	unread_messages.push_back(message);
}


void Member::get_unread_messages()
{
	if(unread_messages.size() > 0)
	{
		cout << "#. Notification Message\n";
		for(int i=0; i<unread_messages.size(); i++)
		{
			cout << i+1 <<". "<< unread_messages[unread_messages.size()-i-1] << endl;
			read_messages.push_back(unread_messages[i]);
		}
		unread_messages.erase(unread_messages.begin(), unread_messages.begin()+unread_messages.size());
	}
	else
	{
		cout << "#. Notification Message\n";
	}
}


void Member::get_read_messages(int limit)
{
	int number_of_read_messages = read_messages.size();
	int number_of_messages_to_display;
	(limit <= number_of_read_messages) ? number_of_messages_to_display= limit : 
						number_of_messages_to_display= number_of_read_messages;
	if(read_messages.size() > 0)
	{
		cout << "#. Notification Message\n";
		for(int i=0; i<number_of_messages_to_display; i++)
		{
			cout << i+1 <<". "<< read_messages[read_messages.size()-i-1] << endl;
		}
	}
	else
	{
		cout << "#. Notification Message\n";
	}
}


void Member::buy_film(shared_ptr<Movie> movie)
{
	try
	{
		if(movie->get_price() > account)
			throw PermissionDenied();
		my_movies.push_back(movie);
	}
	catch(Exception &e)
	{
		e.what();
	}
}

void Member::display_purchased_films()
{
	if(my_movies.size() == 0)
		return;
	MoviesRepository::display_films_info(my_movies);
}


bool Member:: has_purchased_this_film(shared_ptr<Movie> movie)
{
	for(auto elem : my_movies)
	{
		if(elem == movie)
			return true;
	}
	return false;
}


string Member::get_membership_type()
{}