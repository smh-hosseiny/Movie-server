#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <vector>
#include <memory>
#include <map>
#include "Member.h"

class Movie;

class Publisher : public Member
{

public:
	Publisher(std::string username, std::string password, std::string email, int age, int id);
	virtual std::string get_membership_type();
	void add_followers(std::shared_ptr<Member> follower);
	void show_followers();
	void earn_money(std::shared_ptr<Movie> movie);
	int clculate_income(int price_of_movie, double rate);
	void recieve_money();
	int get_movie_sale_income();
	void print_followers();

private:
	double movie_sale_income = 0;
	double blocked_income = 0;
	std::map<int , std::shared_ptr<Member> > followers;
	std::vector<std::shared_ptr<Movie> > my_movies;


};


#endif