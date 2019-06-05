#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <memory>
#include <map>
#include "Movie.h"

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *);
};


class HomePageHandler : public TemplateHandler {
public:
  HomePageHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

class PublishersHomePageHandler : public TemplateHandler {
public:
  PublishersHomePageHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

class LogoutHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ChargeAccountHandler : public RequestHandler {
public:
  Response *callback(Request *req);
};

class ChargeMoneyHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class MovieAddingHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class FilmAddingHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class RemoveMovieHandler : public RequestHandler {
public:
  Response *callback(Request *);
};


class MoviePageHandler : public TemplateHandler {
public:
  MoviePageHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

class GotoProfileHandler : public RequestHandler {
public:
  Response *callback(Request *);
};


class CommentMovieHandler : public RequestHandler {
public:
  Response *callback(Request *);
};


class BuyMovieHandler : public RequestHandler {
public:
  Response *callback(Request *);
};


class RateMovieHandler : public RequestHandler {
public:
  Response *callback(Request *);
};



std::vector<std::shared_ptr<Movie> > get_movies_of_publisher();

std::vector<std::string> generate_signup_request(std::string username, std::string password, 
	std::string email, std::string age, std::string publisher);
std::vector<std::string> generate_login_request(std::string username, std::string password);
std::vector<std::string> generate_charge_account_request(std::string amount);
std::vector<std::string> generate_logout_request();
std::vector<std::string> generate_add_movie_request(std::string name, std::string director,
 std::string summary, std::string length, std::string price, std::string year);
std::vector<std::string> generate_remove_movie_request(std::string film_id);
std::vector<std::string> generate_comment_movie_request(std::string film_id, std::string comment);
std::vector<std::string> generate_buy_movie_request(std::string film_id);
std::vector<std::string> generate_rate_movie_request(std::string film_id, std::string rate);
std::string is_publisher_or_not(std::string publisher);

void set_published_movies( std::map<std::string, std::string> &context);
void set_purchased_movies( std::map<std::string, std::string> &context);
void set_not_purchased_movies( std::map<std::string, std::string> &context);
void set_recomended_movies(std::map<std::string, std::string> &context, int film_id);
void set_comments_and_replies(std::map<std::string, std::string> &context, int film_id);


#endif
