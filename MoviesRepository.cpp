#include "MoviesRepository.h"
#include "Movie.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"
#include <iostream>
#include <algorithm>
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
 	if(movies.size() == 0)
		return;
 	for(int i=0; i<movies.size(); i++)
 	{
 		cout << i+1 << ". " << movies[i]->get_id() << " | " << 
 		movies[i]->get_name() << " | " << movies[i]->get_length() << " | " <<
 		movies[i]->get_price() << " | " << setprecision(8) << movies[i]->get_rate() << 
 		" | " << movies[i]->get_year() << " | " << movies[i]->get_director() << endl;
 	}
}


vector<shared_ptr<Movie> > MoviesRepository::get_recommended_movies(int film_id)
{
	if(all_movies.size() <= 4)
	{
		vector<shared_ptr<Movie> > recommended_movies = all_movies;
		shared_ptr<Movie> this_movie = get_movie(film_id);
		recommended_movies.erase(find(recommended_movies.begin(), recommended_movies.end(), this_movie));
		return recommended_movies;
	}
	else
	{
		vector<shared_ptr<Movie> > top_movies;
		vector<double> rates;
		for(auto &elem : all_movies)
		{
			if(elem->get_id() != film_id)
				rates.push_back(elem->get_rate());
		}
		int number_of_recommended_movies = 0;
		while(number_of_recommended_movies < 4)
		{
			int top_rate = max_element(rates.begin(), rates.end()) - rates.begin();
			top_movies.push_back(all_movies[top_rate]);
			rates.erase(max_element(rates.begin(), rates.end()));
			number_of_recommended_movies++;
		}
		return top_movies;
	}
}


void MoviesRepository::show_this_film(int film_id)
{
	shared_ptr<Movie> movie = get_movie(film_id);
	cout << "Details of Film " << movie->get_name() << endl;
	cout << "Id = " << movie->get_id() << endl;
	cout << "Director = " << movie->get_director() << endl;
	cout << "Length = " << movie->get_length() << endl;
	cout << "Year = " << movie->get_year() << endl;
	cout << "Summary = " << movie->get_summary() << endl;
	cout << "Rate = " << movie->get_rate() << endl;
	cout << "Price = " << movie->get_price() << endl;

	cout << endl << "Comments\n";
	movie-> display_comments();

	vector<shared_ptr<Movie> > top_movies = get_recommended_movies(film_id);
	display_recommendation(top_movies);
}


void MoviesRepository::display_recommendation(vector<shared_ptr<Movie> > movies)
{
	cout << "Recommendation Film \n";
	cout << "#. Film Id | Film Name | Film Length | Film Director" << endl;
	if(movies.size() == 0)
		return;
 	for(int i=0; i<movies.size(); i++)
 	{
 		cout << i+1 << ". " << movies[i]->get_id() << " | " << 
 		movies[i]->get_name() << " | " << movies[i]->get_length() << " | " <<
		movies[i]->get_director() << endl;
 	}
}



void MoviesRepository::show_movies(shared_ptr<Publisher> publisher, const string &name, 
	int min_year, int max_year, double min_rate, double price, const string &director)
{
	vector<shared_ptr<Movie> > movies_of_publisher = get_movies_of_publisher(publisher);
	vector<shared_ptr<Movie> > filtered_movies = filter(movies_of_publisher, name, min_year,
		max_year, min_rate, price, director);
	display_films_info(filtered_movies);
}



void MoviesRepository::show_all_movies(const string &name, int min_year, int max_year,
 double min_rate, double price, const string &director)
{
	vector<shared_ptr<Movie> > filtered_movies = filter(all_movies, name, min_year,
		max_year, min_rate, price, director);
	display_films_info(filtered_movies);
}


bool MoviesRepository::apply_name_filter(shared_ptr<Movie> movie, const string name)
{
	if(name != "" && movie->get_name() != name)
		return false;
	return true;
}


bool MoviesRepository::apply_min_year_filter(shared_ptr<Movie> movie, int min_year)
{
	if(min_year != 0 && movie->get_year() < min_year)
		return false;
	return true;
}


bool MoviesRepository::apply_max_year_filter(shared_ptr<Movie> movie, int max_year)
{
	if(max_year != 0 && movie->get_year() > max_year)
		return false;
	return true;
}


bool MoviesRepository::apply_min_rate_filter(shared_ptr<Movie> movie, double min_rate)
{
	if(min_rate != 0 && movie->get_rate() < min_rate)
		return false;
	return true;
}


bool MoviesRepository::apply_price_filter(shared_ptr<Movie> movie, double price)
{
	if(price != 0 && movie->get_price() != price)
		return false;
	return true;
}


bool MoviesRepository::apply_director_filter(shared_ptr<Movie> movie, const string &director)
{
	if(director != "" && movie->get_director() != director)
		return false;
	return true;
}

vector<shared_ptr<Movie> > MoviesRepository::filter(vector<shared_ptr<Movie> > all_movies_of_publisher, 
	const string &name, int min_year, int max_year, double min_rate, double price, const string &director)
{
	vector<shared_ptr<Movie> > filtered_movies;
	for(auto &elem : all_movies_of_publisher)
	{
		if((apply_name_filter(elem, name) && apply_min_year_filter(elem, min_year) &&
		apply_max_year_filter(elem, max_year) && apply_min_rate_filter(elem, min_rate) &&
		apply_price_filter(elem, price) && apply_director_filter(elem, director)))
		{
			filtered_movies.push_back(elem);
		}
	}
	return filtered_movies;
}


void MoviesRepository:: remove_movie(int film_id)
{
	try
	{
		shared_ptr<Movie> movie = get_movie(film_id);	
		all_movies.erase(find(all_movies.begin(), all_movies.end(), movie));
	}
	catch(const Exception &e)
	{
		throw;
	}
}
