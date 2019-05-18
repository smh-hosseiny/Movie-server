#ifndef MOVIES_REPOSITORY_H
#define MOVIES_REPOSITORY_H

#include <vector>
#include <memory>
#include "Movie.h"


class MoviesRepository
{

public:
	static std::shared_ptr<MoviesRepository> get_instance();

	void add_movie(std::string film_name, int year_of_production, int length_of_movie, double price_of_movie,
	 std::string summary_of_movie,  std::string director_of_movie, std::shared_ptr<Publisher> publisher);

	void edit_movie(int film_id, std::string film_name, int year_of_production, int length_of_movie, 
		double price_of_movie, std::string summary_of_movie,  std::string director_of_movie);

	std::vector<std::shared_ptr<Movie> > get_movies_of_publisher(std::shared_ptr<Publisher> publisher);


	bool film_is_new(std::string film_name);

	std::shared_ptr<Movie> get_movie(int movie_id);

	void show_movies(std::shared_ptr<Publisher> publisher);

	static void display_films_info(std::vector<std::shared_ptr<Movie> > movies);

	void remove_movie(int film_id);


private:
	static std::shared_ptr<MoviesRepository> the_instance;
	std::vector<std::shared_ptr<Movie> > all_movies;
} ;


#endif