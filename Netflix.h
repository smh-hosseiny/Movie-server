#ifndef NETFLIX_H
#define NETFLIX_H

#include <vector>
#include <memory>
#include "Member.h"


class UsersRepository;
class MoviesRepository;

class Netflix
{

public:
   Netflix();
   static std::shared_ptr<Netflix> get_instance();

   void add_member(std::string username, std::string pass, 
            std::string email, int age, bool publisher);

   void login_member(std::string username, std::string pass);

   void charge_account(double amount);

   void set_current_user(std::shared_ptr<Member> user);

   void follow(int user_id);

   void get_unread_notifications();

   void get_read_notifications(int limit);

   void post_film(std::string name, int year, int length_of_movie,
    double price, std::string summary,  std::string director);

   void edit_film(int film_id, std::string name, int year, int length_of_movie,
    double price, std::string summary,  std::string director);

   void show_films();

   void show_purchased_films();

   void remove_film(int film_id);

   void buy_film(int film_id);


private:
	static std::shared_ptr<Netflix> the_instance;
   std::shared_ptr<UsersRepository> Users_repository;
   std::shared_ptr<MoviesRepository> Movies_repository;
   std::shared_ptr<Member> current_user;

};


#endif