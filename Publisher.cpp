#include "Publisher.h"
#include "Member.h"
#include <algorithm>
#include <iostream>

using namespace std;


Publisher::Publisher(string user_name, string pass, string e_mail, int Age, int id)
	: Member(user_name, pass, e_mail, Age, id)
{}

string Publisher::get_membership_type()
{
	return "Publisher";
}


void Publisher::add_followers(shared_ptr<Member> follower)
{
	int id = follower -> get_id();
	followers[id] = follower;
}


void Publisher::print_followers()
{
	int i = 1;
	for(auto &elem : followers)
	{
		cout << i << ". " << elem.first << " | " << elem.second-> get_username() 
		<< " | " << elem.second-> get_email() << endl;
		i++;
	}
}


void Publisher::show_followers()
{
	cout << "List of Followers\n";
	cout << "#. User Id | User Username | User Email" << endl;
	if(followers.size() > 0)
		print_followers();
}

int Publisher::clculate_income(int price_of_movie, double rate)
{
	int publisher_income;
	if(rate < 5)
		publisher_income = 0.50 * price_of_movie;
	if(rate >= 8)
		publisher_income = 0.95 * price_of_movie;
	else
		publisher_income = 0.90 * price_of_movie;
	return publisher_income;
}

void Publisher::earn_money(std::shared_ptr<Movie> movie)
{
	double rate = movie->get_rate();
	int price_of_movie = movie->get_price();
	int publisher_income = clculate_income(price_of_movie, rate);
	movie_sale_income += publisher_income;
}

int Publisher::get_movie_sale_income()
{
	return movie_sale_income;
}