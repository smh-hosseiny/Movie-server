#include "handlers.hpp"
#include "Interface.h"
#include "Netflix.h"
#include "Exception.h"
#include "Movie.h"
#include <memory>
#include <vector>
#include <map>

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

vector<shared_ptr<Movie> > get_movies_of_publisher()
{
  vector<shared_ptr<Movie> > publishers_movies = Interface::get_instance()->get_publishers_movies();
  return publishers_movies;
}

void set_other_movies( map<string, string> &context)
{
  vector<shared_ptr<Movie> > not_purchased_movies = Netflix::get_instance() -> get_not_purchased_movies();
  int i = 0;
  for(auto &elem : not_purchased_movies)
  {

    context["other_movies_name" + to_string(i)] = elem->get_name();
    context["other_movies_director" + to_string(i)] = elem->get_director();
    context["other_movies_summary" + to_string(i)] = elem->get_summary();
    context["other_movies_rate" + to_string(i)] = to_string(elem->get_rate());
    context["other_movies_price" + to_string(i)] = to_string(elem->get_price());
    context["other_movies_year" + to_string(i)] = to_string(elem->get_year());
    context["other_movies_length" + to_string(i)] = to_string(elem->get_length());
    context["other_movies_film_id" + to_string(i)] = to_string(elem->get_id());
    i++;
  }
  context["number_of_other_movies"] = to_string(not_purchased_movies.size());
}


void set_purchased_movies( map<string, string> &context)
{
  vector<shared_ptr<Movie> > purchased_movies = (Netflix::get_instance()-> get_current_user()) -> get_purchased_movies();
  int i = 0;
  for(auto &elem : purchased_movies)
  {
    context["purchased_movies_name" + to_string(i)] = elem->get_name();
    context["purchased_movies_director" + to_string(i)] = elem->get_director();
    context["purchased_movies_summary" + to_string(i)] = elem->get_summary();
    context["purchased_movies_rate" + to_string(i)] = to_string(elem->get_rate());
    context["purchased_movies_price" + to_string(i)] = to_string(elem->get_price());
    context["purchased_movies_year" + to_string(i)] = to_string(elem->get_year());
    context["purchased_movies_length" + to_string(i)] = to_string(elem->get_length());
    context["purchased_movies_film_id" + to_string(i)] = to_string(elem->get_id());
    i++;
  }
  context["number_of_purchased_movies"] = to_string(purchased_movies.size());
}


void set_published_movies(map<string, string> &context)
{
  vector<shared_ptr<Movie> > publishers_movies = get_movies_of_publisher();
  int i = 0;
  for(auto &elem : publishers_movies)
  {
    context["published_movies_name" + to_string(i)] = elem->get_name();
    context["published_movies_director" + to_string(i)] = elem->get_director();
    context["published_movies_summary" + to_string(i)] = elem->get_summary();
    context["published_movies_rate" + to_string(i)] = to_string(elem->get_rate());
    context["published_movies_price" + to_string(i)] = to_string(elem->get_price());
    context["published_movies_year" + to_string(i)] = to_string(elem->get_year());
    context["published_movies_length" + to_string(i)] = to_string(elem->get_length());
    context["published_movies_film_id" + to_string(i)] = to_string(elem->get_id());
    i++;
  }
  context["number_of_published_movies"] = to_string(publishers_movies.size());
}


void set_recomended_movies(map<string, string> &context, int film_id)
{
  vector<shared_ptr<Movie> > recommended_movies = Netflix::get_instance() -> get_recommended_movies(film_id);
  int i = 0;
  for(auto &elem : recommended_movies)
  {
    context["recommended_movies_name" + to_string(i)] = elem->get_name();
    context["recommended_movies_director" + to_string(i)] = elem->get_director();
    context["recommended_movies_summary" + to_string(i)] = elem->get_summary();
    context["recommended_movies_rate" + to_string(i)] = to_string(elem->get_rate());
    context["recommended_movies_price" + to_string(i)] = to_string(elem->get_price());
    context["recommended_movies_year" + to_string(i)] = to_string(elem->get_year());
    context["recommended_movies_length" + to_string(i)] = to_string(elem->get_length());
    context["recommended_movies_film_id" + to_string(i)] = to_string(elem->get_id());
    i++;
  }
  context["number_of_recommended_movies"] = to_string(recommended_movies.size());
}



void set_comments_and_replies(map<string, string> &context, int film_id)
{
 map<int, vector<string>> comments_and_replies= Netflix::get_instance() -> get_comments_and_replies(film_id);
  int i = 0;
  for(auto &elem : comments_and_replies)
  {
    context["comments" + to_string(i)] = elem.second[0];
    if(elem.second.size() > 1)
    {
      for(int j=1; j<elem.second.size(); j++)
      {
         context["replies" + to_string(i)] = elem.second[j];
      }
    }
    i++;
  }
  context["number_of_comments"] = to_string(comments_and_replies.size());
}


PublishersHomePageHandler::PublishersHomePageHandler(string filePath) : TemplateHandler(filePath) {}

map<string, string> PublishersHomePageHandler::handle(Request *req) {
  map<string, string> context;
  set_published_movies(context);
  set_purchased_movies(context);
  set_other_movies(context);
  return context;  
}


HomePageHandler::HomePageHandler(string filePath) : TemplateHandler(filePath) {}

map<string, string> HomePageHandler::handle(Request *req) {
  map<string, string> context;
  set_purchased_movies(context);
  set_other_movies(context);
  return context;  
  
}


MoviePageHandler::MoviePageHandler(string filePath) : TemplateHandler(filePath) {}

  map<string, string> MoviePageHandler::handle(Request *req) {
  map<string, string> context;
  int film_id = stoi(req->getBodyParam("id"));
  set_comments_and_replies(context, film_id);
  shared_ptr<Movie> movie = Netflix::get_instance()->get_film(film_id);
  context["name"] =movie->get_name();;
  context["director"] =movie->get_director();
  context["rate"] = to_string(movie->get_rate());
  context["price"] = to_string(movie->get_price());
  context["year"] = to_string(movie->get_year());
  context["length"] = to_string(movie->get_length());
  context["film_id"] = to_string(movie->get_id());
  context["number_of_movies"] = "1";
  return context;
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


vector<string> generate_remove_movie_request(string film_id)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("delete_films");
  input.push_back("?");input.push_back("film_id");input.push_back(film_id);
  return input;
}



vector<string> generate_buy_movie_request(string film_id)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("buy");
  input.push_back("?");input.push_back("film_id");input.push_back(film_id);
  return input;
}


vector<string> generate_comment_movie_request(string film_id, string comment)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("comments");
  input.push_back("?");input.push_back("film_id");input.push_back(film_id);
  input.push_back("content");input.push_back(comment);

  return input;
}


vector<string> generate_rate_movie_request(string film_id, string rate)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("rate");
  input.push_back("?");input.push_back("film_id");input.push_back(film_id);
  input.push_back("score");input.push_back(rate);

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
  if((Netflix::get_instance()-> get_current_user() ->get_membership_type()) == "Publisher")
    res = Response::redirect("/publishers-homepage");
  else
    res = Response::redirect("/homepage");
  res->setSessionId(to_string(sid));
  // sid++;
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
  if((Netflix::get_instance()-> get_current_user() ->get_membership_type()) == "Publisher")
    res = Response::redirect("/publishers-homepage");
  else
    res = Response::redirect("/homepage");
  res->setSessionId(to_string(sid));
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
  return res;
}


Response *RemoveMovieHandler::callback(Request *req) {
 string film_id = req->getBodyParam("film_id");
 vector<string> remove_movie_input = generate_remove_movie_request(film_id);
 for(auto &elem : remove_movie_input)
   cout << elem ;
cout << endl;
  try
  {
   Interface::get_instance() -> handle_input(remove_movie_input);
  }
  catch(const Exception &e)
  {
    throw Server::Exception(e.what());  
  }
  Response *res = Response::redirect("/publishers-homepage");
  res->setSessionId(to_string(sid));
  return res;
}



Response *GotoProfileHandler::callback(Request *req) {
  Response *res;
  if((Netflix::get_instance()-> get_current_user() ->get_membership_type()) == "Publisher")
    res = Response::redirect("/publishers-homepage");
  else
    res = Response::redirect("/homepage");
  res->setSessionId(to_string(sid));
  return res;
}




Response *CommentMovieHandler::callback(Request *req) {
  Response *res;
  string film_id = req->getBodyParam("film_id");
  string comment = req->getBodyParam("comment");
  vector<string> comment_movie_input = generate_comment_movie_request(film_id, comment);
  try
  {
   Interface::get_instance() -> handle_input(comment_movie_input);
  }
  catch(const Exception &e)
  {
    throw Server::Exception(e.what());  
  }

  // if((Netflix::get_instance()-> get_current_user() ->get_membership_type()) == "Publisher")
  //   res = Response::redirect("/publishers-homepage");
  // else
  //   res = Response::redirect("/homepage");
  res->setSessionId(to_string(sid));
  return res;
}


Response *BuyMovieHandler::callback(Request *req) {
  Response *res;
  string film_id = req->getBodyParam("film_id");
  vector<string> buy_movie_input = generate_buy_movie_request(film_id);
  try
  {
   Interface::get_instance() -> handle_input(buy_movie_input);
  }
  catch(const Exception &e)
  {
    throw Server::Exception(e.what());  
  }

  // if((Netflix::get_instance()-> get_current_user() ->get_membership_type()) == "Publisher")
  //   res = Response::redirect("/publishers-homepage");
  // else
  //   res = Response::redirect("/homepage");
  res->setSessionId(to_string(sid));
  return res;
}


Response *RateMovieHandler::callback(Request *req) {
  Response *res;
  string film_id = req->getBodyParam("film_id");
  string rate = req->getBodyParam("rate");
  vector<string> rate_movie_input = generate_rate_movie_request(film_id, rate);
  try
  {
   Interface::get_instance() -> handle_input(rate_movie_input);
  }
  catch(const Exception &e)
  {
    throw Server::Exception(e.what());  
  }
  res->setSessionId(to_string(sid));
  return res;
}
