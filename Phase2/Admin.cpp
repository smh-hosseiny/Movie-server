#include "Admin.h"
#include "Netflix.h"

#define ADMIN "admin"

using namespace std;

shared_ptr<Admin> Admin::the_instance=0;

shared_ptr<Admin> Admin::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<Admin>(Admin(ADMIN, ADMIN));
	return the_instance;
}

Admin::Admin(string user_name, string pass)
{
	username = user_name;
	password = pass;
	logged_in = false;
}

double Admin::get_money()
{
	return Netflix::get_instance() -> get_server_money();
}

void Admin::login()
{
	logged_in = true;
}

void Admin::logout()
{
	logged_in = false;
}

bool Admin::is_logged_in()
{
	return logged_in;
}
