#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "Netflix.h"
#include "Interface.h"

#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL)); // for rand
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler());
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler());
    server.get("/rand", new RandomNumberHandler());
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/img1.jpg", new ShowImage("static/img1.jpg"));
    server.get("/netflix.png", new ShowImage("static/netflix.png"));
    server.get("/img2.jpg", new ShowImage("static/img2.jpg"));
    server.get("/img3.jpg", new ShowImage("static/img3.jpg"));
    server.get("/", new ShowPage("static/home.html"));
    server.get("/colors", new ColorHandler("template/colors.html"));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}


// int main(int argc,char* avgv[])
// {
//   Interface::get_instance() -> run_netflix();
// }
