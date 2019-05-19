#include "Publisher.h"
#include "Member.h"
#include <algorithm>
#include <iostream>

using namespace std;


Publisher :: Publisher(string user_name, string pass, string e_mail, int Age, int id)
	: Member(user_name, pass, e_mail, Age, id)
{}

string Publisher :: get_membership_type()
{
	return "Publisher";
}


void Publisher :: add_followers(shared_ptr<Member> follower)
{
	if(find(followers.begin(), followers.end(), follower) == followers.end())
		followers.push_back(follower);
}


void Publisher::show_followers()
{
	cout << "List of followers\n";
	cout << "#. User Id | User Username | User Email" << endl;
	if(followers.size() > 0)
	{
		for(int i=0; i<followers.size(); i++)
		cout << i+1 << ". " << followers[i]-> get_id() << " " << followers[i]-> get_username() 
		<< " " << followers[i]-> get_email() << endl;
	}
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


// void post_movie(string film_name, int year_of_production, int length_of_movie,
// 	 double price_of_movie, string summary_of_movie, string director_of_movie)
// {}
