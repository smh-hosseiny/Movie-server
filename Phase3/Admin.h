#ifndef ADMIN_H
#define ADMINR_H

#include <vector>
#include <memory>
#include "Movie.h"


class Admin
{

public:
	static std::shared_ptr<Admin> get_instance();
	Admin(std::string user_name, std::string pass);	
	double get_money();
	void login();
	void logout();
	bool is_logged_in();
   

private:
	static std::shared_ptr<Admin> the_instance;
	std::string username;
	std::string password;
	bool logged_in;
};


#endif