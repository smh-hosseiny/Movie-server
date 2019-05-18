#include "Publisher.h"
#include "Member.h"
#include <algorithm>

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


// void post_movie(string film_name, int year_of_production, int length_of_movie,
// 	 double price_of_movie, string summary_of_movie, string director_of_movie)
// {}
