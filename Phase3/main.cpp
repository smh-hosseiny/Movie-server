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
    server.get("/homepage", new HomePageHandler("static/homepage.html"));
    server.get("/publishers-homepage", new PublishersHomePageHandler("static/publishers-homepage.html"));
    server.get("/home", new ShowPage("static/home.html"));
    server.post("/home", new LogoutHandler());
    server.get("/login", new ShowPage("static/login.html"));
    server.get("/charge-account", new ShowPage("static/charge_account.html"));
    server.post("/charge-account", new ChargeAccountHandler());
    server.post("/charge-money", new ChargeMoneyHandler());
    server.get("/add-movie", new ShowPage("static/add-movie.html"));
    server.post("/add-movie", new MovieAddingHandler());
    server.post("/add-film", new FilmAddingHandler());
    server.post("/remove-movie", new RemoveMovieHandler());
    server.post("/movie-page", new MoviePageHandler("static/movie-page.html"));
    server.post("/profile", new GotoProfileHandler());
    server.post("/comment-movie", new CommentMovieHandler());
    server.post("/rate-movie", new RateMovieHandler());
    server.post("/buy-movie", new BuyMovieHandler());
    server.get("/rand", new RandomNumberHandler());
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/background.jpg", new ShowImage("static/background.jpg"));
    server.get("/netflix.png", new ShowImage("static/netflix.png"));
    server.get("/netflix_name.jpeg", new ShowImage("static/netflix_name.jpeg"));
    server.get("/theater.jpg", new ShowImage("static/theater.jpg"));
    server.get("/form_background.jpg", new ShowImage("static/form_background.jpg"));
    server.get("/paypal.png", new ShowImage("static/paypal.png"));
    server.get("/pay.jpg", new ShowImage("static/pay.jpg"));
    server.get("/add-movie.jpg", new ShowImage("static/add-movie.jpg"));
    server.get("/", new ShowPage("static/home.html"));
    server.get("/bootstrap.css", new ShowPage("static/css/bootstrap.css"));
    server.get("/bootstrap.js", new ShowPage("static/js/bootstrap.js"));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}


// int main(int argc,char* avgv[])
// {
//   Interface::get_instance() -> run_netflix();
// }
