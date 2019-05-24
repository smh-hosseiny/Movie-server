#include "MoviesRepository.h"
#include "Movie.h"
#include "Member.h"
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"
#include <iostream>
#include <algorithm>
#include <iomanip> 

#define FILM_ID "Film Id"
#define FILM_NAME "Film Name"
#define FILM_LENGTH "Film Length"
#define FILM_PRICE "Film price"
#define RATE "Rate"
#define PRODUCTION_YEAR "Production Year"
#define FILM_DIRECTOR "Film Director"
#define SEPERATOR " | "
#define SHARP_SIGN "#. "
#define ID "Id"
#define DIRECTOR "Director"
#define LENGTH "Length"
#define YEAR "Year"
#define PRICE "Price"
#define SUMMARY "Summary"
#define DETAILS "Details of Film "
#define IS " = "
#define COMMENTS "Comments"
#define RECOMMENDATION_FILM "Recommendation Film"

using namespace std;

shared_ptr<MoviesRepository> MoviesRepository::the_instance=0;

shared_ptr<MoviesRepository> MoviesRepository::get_instance()
{
	if(the_instance == 0)
		the_instance = make_shared<MoviesRepository>(MoviesRepository());
	return the_instance;
}

MoviesRepository::MoviesRepository()
{
	movie_graph = make_shared<MovieGraph>(MovieGraph());
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
		movie_graph->add_node();
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

void MoviesRepository::display_info(vector<shared_ptr<Movie> > movies)
{
	for(int i=0; i<movies.size(); i++)
 	{
 		cout << i+1 << ". " << movies[i]->get_id() << SEPERATOR << 
 		movies[i]->get_name() << SEPERATOR << movies[i]->get_length() << SEPERATOR <<
 		movies[i]->get_price() << SEPERATOR << setprecision(8) << movies[i]->get_rate() << 
 		SEPERATOR << movies[i]->get_year() << SEPERATOR << movies[i]->get_director() << endl;
 	}
}


void MoviesRepository::display_films_info(vector<shared_ptr<Movie> > movies)
{
	cout << SHARP_SIGN << FILM_ID << SEPERATOR << FILM_NAME << SEPERATOR << FILM_LENGTH
	<< SEPERATOR << FILM_PRICE << SEPERATOR << RATE << SEPERATOR << PRODUCTION_YEAR << 
	SEPERATOR << FILM_DIRECTOR << endl;
							
 	if(movies.size() == 0)
		return;
	display_info(movies); 	
}

void MoviesRepository::ignore_members_own_films(vector<shared_ptr<Movie> > &movies, 
	const vector<shared_ptr<Movie> > &members_movies)
{
	for(auto &elem : movies)
	{
		if(find(members_movies.begin(), members_movies.end(), elem) != members_movies.end())
			movies.erase(find(movies.begin(), movies.end(), elem));
	}
}

vector<shared_ptr<Movie> > MoviesRepository::find_movies_by_index(vector<int> movies_ids)
{
	vector<shared_ptr<Movie> > movies;
	for(auto &elem : movies_ids)
	{
		movies.push_back(all_movies[elem]);
	}
	return movies;
}


vector<shared_ptr<Movie> > MoviesRepository::send_recommendations(vector<int> users_movies_ids, int film_id)
{
	vector<shared_ptr<Movie> > recommended_movies;
	vector<int> recommended_movies_index = recommend_based_on_graph(users_movies_ids, film_id);
	recommended_movies = find_movies_by_index(recommended_movies_index);
	return recommended_movies;
}


vector<int> MoviesRepository::recommend_based_on_graph(vector<int> users_movies_ids, int film_id)
{
	return movie_graph->recommend_movie(users_movies_ids, film_id);
}


vector<shared_ptr<Movie> > MoviesRepository::get_recommended_movies(int film_id, shared_ptr<Member> member)
{
	vector<int> users_purchased_movies = member -> get_purchased_movies_ids();
	return send_recommendations(users_purchased_movies, film_id);
}


void MoviesRepository::display_comments_and_recommendations(int film_id, shared_ptr<Member> member)
{
	shared_ptr<Movie> movie = get_movie(film_id);
	cout << endl << COMMENTS << endl;
	movie-> display_comments();

	vector<shared_ptr<Movie> > top_movies = get_recommended_movies(film_id, member);
	display_recommendation(top_movies);
}


void MoviesRepository::show_this_film(int film_id, shared_ptr<Member> member)
{
	shared_ptr<Movie> movie = get_movie(film_id);
	cout << DETAILS << movie->get_name() << endl;
	cout << ID << IS << movie->get_id() << endl;
	cout << DIRECTOR << IS << movie->get_director() << endl;
	cout << LENGTH << IS << movie->get_length() << endl;
	cout << YEAR << IS << movie->get_year() << endl;
	cout << SUMMARY << IS << movie->get_summary() << endl;
	cout << RATE << IS << movie->get_rate() << endl;
	cout << PRICE << IS << movie->get_price() << endl;

	display_comments_and_recommendations(film_id, member);
}


void MoviesRepository::display(vector<shared_ptr<Movie> > movies)
{
	for(int i=0; i<movies.size(); i++)
 	{
 		cout << i+1 << ". " << movies[i]->get_id() << SEPERATOR << 
 		movies[i]->get_name() << SEPERATOR << movies[i]->get_length() << SEPERATOR <<
		movies[i]->get_director() << endl;
 	}
}



void MoviesRepository::display_recommendation(vector<shared_ptr<Movie> > movies)
{
	cout << RECOMMENDATION_FILM << endl;
	cout << SHARP_SIGN << FILM_ID << SEPERATOR << FILM_NAME << SEPERATOR << FILM_LENGTH <<
	SEPERATOR << FILM_DIRECTOR << endl;
	if(movies.size() == 0)
		return;
	display(movies);
 	
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


bool MoviesRepository::apply_filter(shared_ptr<Movie> movie_of_publisher, 
	const string &name, int min_year, int max_year, double min_rate, double price, const string &director)
{
	return ((apply_name_filter(movie_of_publisher, name) && apply_min_year_filter(movie_of_publisher, min_year) &&
	apply_max_year_filter(movie_of_publisher, max_year) && apply_min_rate_filter(movie_of_publisher, min_rate) &&
	apply_price_filter(movie_of_publisher, price) && apply_director_filter(movie_of_publisher, director)));
}


vector<shared_ptr<Movie> > MoviesRepository::filter(vector<shared_ptr<Movie> > all_movies_of_publisher, 
	const string &name, int min_year, int max_year, double min_rate, double price, const string &director)
{
	vector<shared_ptr<Movie> > filtered_movies;
	for(auto &elem : all_movies_of_publisher)
	{
		if(apply_filter(elem, name, min_year, max_year, min_rate, price, director));
			filtered_movies.push_back(elem);
	}
	return filtered_movies;
}


void MoviesRepository:: remove_movie(int film_id)
{
	try
	{
		all_movies.erase(find(all_movies.begin(), all_movies.end(), get_movie(film_id)));
		movie_graph->remove_node(film_id);
	}
	catch(const Exception &e)
	{
		throw;
	}
}


void MoviesRepository::show_graph()
{
	movie_graph->display_graph();
}

void MoviesRepository::check_members_favorite_movies(vector<int> purchased_movies_id)
{
	if(purchased_movies_id.size() > 1)
	{
		movie_graph->set_weights(purchased_movies_id);
	}
}
