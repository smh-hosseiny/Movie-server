#include "handlers.hpp"
#include "Interface.h"
#include "Exception.h"
#include <vector>

using namespace std;

int sid = 1;

Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>NETFLIX</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

vector<string> generate_login_request(string username, string password)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("login"); input.push_back("?");
  input.push_back("username"); input.push_back(username); input.push_back("password"); 
  input.push_back(password);
  return input;
}


vector<string> generate_signup_request(string username, string password, string email, string age, string publisher)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("signup"); input.push_back("?");
  input.push_back("email"); input.push_back(email); input.push_back("username");
  input.push_back(username); input.push_back("password"); input.push_back(password);
  input.push_back("age"); input.push_back(age); input.push_back("publisher");
  input.push_back(is_publisher_or_not(publisher));
  return input;
}

vector<string> generate_logout_request()
{
  vector<string> input;
  input.push_back("POST"); input.push_back("logout");
  return input;
}


vector<string> generate_charge_account_request(string amount)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("money");
  input.push_back("?");input.push_back("amount");input.push_back(amount);
  return input;
}


vector<string> generate_add_movie_request(string name, string director, string summary, string length, string price, string year)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("films"); input.push_back("?");
  input.push_back("name"); input.push_back(name); input.push_back("year");
  input.push_back(year); input.push_back("length"); input.push_back(length);
  input.push_back("price"); input.push_back(price); input.push_back("summary");
  input.push_back(summary);input.push_back("director"); input.push_back(director);
  return input;
}


string is_publisher_or_not(string publisher)
{
  if(publisher == "on")
    return "true";
  return "false";
}


Response *SignupHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string confirm_password = req->getBodyParam("confirm_password");
  string email = req->getBodyParam("email");
  string age = req->getBodyParam("age");
  string publisher = req->getBodyParam("publisher");
  if(password != confirm_password)
    throw Server::Exception("password was not confirmed.");

  vector<string> signup_input = generate_signup_request(username, password, email, age, publisher);
  try
  {
   Interface::get_instance() -> handle_input(signup_input);
  }
  catch(const Exception &e)
  {
    throw Server::Exception(e.what() + "this username exists in the server");  
  }

  if (username == "root")
    throw Server::Exception("Remote root access has been disabled.");

  Response *res;
  if(publisher == "on")
    res = Response::redirect("/publishers-homepage");
  else
    res = Response::redirect("/homepage");
  res->setSessionId(to_string(sid));
  sid++;
  return res;
}



Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  vector<string> login_input = generate_login_request(username, password);
  try
  {
    Interface::get_instance() -> handle_input(login_input);
  }
  catch(const Exception &e)
  {
    throw Server::Exception(e.what());  
  }
 

  if (username == "root")
    throw Server::Exception("Remote root access has been disabled.");
  Response *res;
  if(Interface::get_instance()->is_publisher())
    res = Response::redirect("/publishers-homepage");
  else
    res = Response::redirect("/homepage");
  res->setSessionId(to_string(sid));
  sid++;
  return res;
}


Response *LogoutHandler::callback(Request *req) {
  Response *res = Response::redirect("/home");
  vector<string> logout_input = generate_logout_request();
  Interface::get_instance() -> handle_input(logout_input);
  res->setSessionId("");
  return res;
}

Response *ChargeAccountHandler::callback(Request *req) {
  Response *res = Response::redirect("/charge-account");
  res->setSessionId(to_string(sid));
  return res;
}



Response *ChargeMoneyHandler::callback(Request *req) {
  string amount = req->getBodyParam("amount");
  vector<string> charge_account_input = generate_charge_account_request(amount);
  try
  {
   Interface::get_instance() -> handle_input(charge_account_input);
  }
  catch(const Exception &e)
  {
    throw Server::Exception(e.what());  
  }

  Response *res;
  if(Interface::get_instance()->is_publisher())
    res = Response::redirect("/publishers-homepage");
  else
    res = Response::redirect("/homepage");
  res->setSessionId(to_string(sid));
  sid++;
  return res;
}

Response *MovieAddingHandler::callback(Request *req) {
  Response *res = Response::redirect("/add-movie");
  res->setSessionId(to_string(sid));
  return res;
}


Response *FilmAddingHandler::callback(Request *req) {
  string name = req->getBodyParam("name");
  string director = req->getBodyParam("director");
  string summary = req->getBodyParam("summary");
  string length = req->getBodyParam("length");
  string year = req->getBodyParam("year");
  string price = req->getBodyParam("price");
  
  vector<string> add_movie_input = generate_add_movie_request(name, director, summary, length, price, year);
  try
  {
   Interface::get_instance() -> handle_input(add_movie_input);
  }
  catch(const Exception &e)
  {
    throw Server::Exception(e.what());  
  }

  Response *res = Response::redirect("/publishers-homepage");
  res->setSessionId(to_string(sid));
  sid++;
  return res;
}



Response *UploadHandler::callback(Request *req) {
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");
  cout << name << " (" << file.size() << "B):\n" << file << endl;
  Response *res = Response::redirect("/");
  return res;
}

ColorHandler::ColorHandler(string filePath) : TemplateHandler(filePath) {}

map<string, string> ColorHandler::handle(Request *req) {
  map<string, string> context;
  string newName = "I am " + req->getQueryParam("name");
  context["name"] = newName;
  context["color"] = req->getQueryParam("color");
  return context;
}
