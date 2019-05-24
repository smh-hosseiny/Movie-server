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
	std::string get_email();
	int get_id();
	std::vector<std::shared_ptr<Movie> > get_purchased_movies();
	std::vector<int> get_purchased_movies_ids();
	virtual std::string get_membership_type();
	bool follow_publisher(std::shared_ptr<Member> publisher);
	void recieve_notification(std::string message);
	void get_unread_messages();
	void display_unread_messages();
	void get_read_messages(int limit);
	void display_read_messages(int number_of_messages_to_display);
	void buy_film(std::shared_ptr<Movie> movie);
	void display_purchased_films(const std::string &name, double price, int min_year,
	int max_year, const std::string &director);
	bool has_purchased_this_film(std::shared_ptr<Movie> movie);
	double get_money();
   

private:
	int ID;
	std::string username;
	std::string password;
	std::string email;
	int age;
	double account;
	std::vector<std::shared_ptr<Member> > followings;
	std::vector<std::string> unread_messages;
	std::vector<std::string> read_messages;

	std::vector<std::shared_ptr<Movie> > my_movies;

};


#endif