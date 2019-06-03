#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

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

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(std::string filePath);
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


std::vector<std::string> generate_signup_request(std::string username, std::string password, 
	std::string email, std::string age, std::string publisher);
std::vector<std::string> generate_login_request(std::string username, std::string password);
std::vector<std::string> generate_charge_account_request(std::string amount);
std::vector<std::string> generate_logout_request();
std::vector<std::string> generate_add_movie_request(std::string name, std::string director,
 std::string summary, std::string length, std::string price, std::string year);
std::string is_publisher_or_not(std::string publisher);


#endif
