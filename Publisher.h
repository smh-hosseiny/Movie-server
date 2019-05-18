#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <vector>
#include <memory>
#include "Member.h"

class Movie;

class Publisher : public Member
{

public:
	Publisher(std::string username, std::string password, std::string email, int age, int id);
   	virtual std::string get_membership_type();
   	void add_followers(std::shared_ptr<Member> follower);
  //void post_movie(std::string film_name, int year_of_production, int length_of_movie,
  // double price_of_movie, std::string summary_of_movie,  std::string director_of_movie);
   	

private:
	std::vector<std::shared_ptr<Member> > followers;
	std::vector<std::shared_ptr<Movie> > my_movies;


};


#endif