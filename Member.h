#ifndef MEMBER_H
#define MEMBER_H

#include <vector>
#include <memory>
#include "Movie.h"


class Member
{

public:
	Member(std::string username, std::string password, std::string email, int age, int id);
	void charge_your_account(double amount);
	std::string get_username();
	std::string get_password();
	int get_id();
	virtual std::string get_membership_type();
	void follow_publisher(std::shared_ptr<Member> publisher);
	void recieve_notification(std::string message);
	void get_unread_messages();
	void get_read_messages(int limit);
	void buy_film(std::shared_ptr<Movie> movie);
	void display_purchased_films();
	bool has_purchased_this_film(std::shared_ptr<Movie> movie);
   

private:
	int ID;
	std::string username;
	std::string password;
	std::string email;
	int age;
	double account;
	bool logged_in;
	std::vector<std::shared_ptr<Member> > followings;
	std::vector<std::string> unread_messages;
	std::vector<std::string> read_messages;

	std::vector<std::shared_ptr<Movie> > my_movies;

};


#endif