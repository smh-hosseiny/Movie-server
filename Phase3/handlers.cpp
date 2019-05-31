#include "handlers.hpp"
#include "Interface.h"
#include <vector>

using namespace std;

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

Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  if (username == "root")
    throw Server::Exception("Remote root access has been disabled.");
  cout << "username: " << username << ",\tpassword: " << password << endl;
  Response *res = Response::redirect("/login");
  res->setSessionId("SID");
  return res;
}

string is_publisher(string publisher)
{
  if(publisher == "on")
    return "true";
  return "false";
}

vector<string> generate_signup_request(string username, string password, string email, string age, string publisher)
{
  vector<string> input;
  input.push_back("POST"); input.push_back("signup"); input.push_back("?");
  input.push_back("email"); input.push_back(email); input.push_back("username");
  input.push_back(username); input.push_back("password"); input.push_back(password);
  input.push_back("age"); input.push_back(age); input.push_back("publisher");
  input.push_back(is_publisher(publisher));
  
  return input;
}


Response *SignupHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string email = req->getBodyParam("email");
  string age = req->getBodyParam("age");
  string publisher = req->getBodyParam("publisher");
  vector<string> signup_input = generate_signup_request(username, password, email, age, publisher);
  Interface::get_instance() -> handle_input(signup_input);

  if (username == "root")
    throw Server::Exception("Remote root access has been disabled.");
  cout << "username: " << username << ",\tpassword: " << password << endl;
  Response *res = Response::redirect("/rand");
  res->setSessionId("SID");
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
