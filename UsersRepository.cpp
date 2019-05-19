#include "UsersRepository.h"
#include "Member.h"
#include "Publisher.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"


using namespace std;

shared_ptr<UsersRepository> UsersRepository :: the_instance=0;

shared_ptr<UsersRepository> UsersRepository :: get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<UsersRepository>(UsersRepository());
	return the_instance;
}

void UsersRepository :: add_member(string user_name, string pass, string e_mail, int age, bool publisher)
{
	int user_id = all_members.size()+1;
	if(publisher)
	{
		all_members.push_back(make_shared<Publisher>(Publisher(user_name, pass, e_mail, age, user_id)));
	}

	else
		all_members.push_back(make_shared<Member>(Member(user_name, pass, e_mail, age, user_id)));
}

bool UsersRepository :: login_member(string username, string password)
{
	for(auto &elem : all_members)
	{
		if(elem-> get_username() == username && elem-> get_password() == password)
		{
			return true;
		}
	}
	return false;
}

shared_ptr<Member> UsersRepository :: get_member(string username, string password)
{
	for(auto &elem : all_members)
	{
		if(elem-> get_username() == username && elem-> get_password() == password)
		{
			return elem;
		}
	}
	throw NotFound();
}


shared_ptr<Member> UsersRepository :: get_member(int id)
{
	for(auto &elem : all_members)
	{
		if(elem->get_id() == id)
			return elem;
	}
	throw NotFound();
}