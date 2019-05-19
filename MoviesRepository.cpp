#include "MoviesRepository.h"
#include "Movie.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"
#include <iostream>
#include <iomanip> 



using namespace std;

shared_ptr<MoviesRepository> MoviesRepository::the_instance=0;

shared_ptr<MoviesRepository> MoviesRepository::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<MoviesRepository>(MoviesRepository());
	return the_instance;
}

void MoviesRepository::add_movie(string name, int year, int length,
 double price, string summary, string director, shared_ptr<Publisher> publisher)
{
	int id = all_movies.size()+1;
	shared_ptr<Movie> new_movie = make_shared<Movie>(Movie(id, name, year, length,
		price, summary, director, publisher));
	if(film_is_new(new_movie->get_name()))
	{
		all_movies.push_back(new_movie);
	}
}


void MoviesRepository::edit_movie(int film_id, string name, int year, 
	int length, double price, string summary, string director)
{
	try
	{
		shared_ptr<Movie> movie = get_movie(film_id);
		movie -> edit(name, year, length, price, summary, director);
	}
	catch(Exception &e)
	{
		e.what();
	}
}


bool MoviesRepository::film_is_new(string name)
{
	for(auto &elem : all_movies)
	{
		if(elem->get_name() == name)
			return false;
	}
	return true;
}


shared_ptr<Movie> MoviesRepository::get_movie(int movie_id)
{
	for(auto &elem : all_movies)
	{
		if(elem->get_id() == movie_id)
			return elem;
	}
	throw NotFound();
}


vector<shared_ptr<Movie> > MoviesRepository::get_movies_of_publisher(shared_ptr<Publisher> publisher)
{
	vector<shared_ptr<Movie> > movies;
	for(auto &elem : all_movies)
	{
		if(elem->get_publisher() == publisher)
			movies.push_back(elem);
	}
	return movies;
}


void MoviesRepository::display_films_info(vector<shared_ptr<Movie> > movies)
{
	cout << "#. Film Id | Film Name | Film Length | Film price |"<<
							 " Rate | Production Year | Film Director" << endl;
 	for(int i=0; i<movies.size(); i++)
 	{
 		cout << i+1 << ". " << movies[i]->get_id() << " | " << 
 		movies[i]->get_name() << " | " << movies[i]->get_length() << " | " <<
 		movies[i]->get_price() << " | " << setprecision(2) << movies[i]->get_rate() << 
 		" | " << movies[i]->get_year() << " | " << movies[i]->get_director() << endl;
 	}
}


void MoviesRepository::show_movies(shared_ptr<Publisher> publisher)
{
	vector<shared_ptr<Movie> > movies_of_publisher = get_movies_of_publisher(publisher);
	if(movies_of_publisher.size() == 0)
		return;
	display_films_info(movies_of_publisher);
}


void MoviesRepository:: remove_movie(int film_id)
{
	// try
	// {
	// 	shared_ptr<Movie> movie = get_movie(film_id);	
	// 	vector<shared_ptr<Movie> >::iterator position = find(all_movies.begin(), all_movies.end(), movie);
	// 	if(position != all_movies.end())
	// 			all_movies.erase(position);
	// }
	// catch(NotFound e)
	// {
	// 	cout << "Not Found\n";
	// }
}
