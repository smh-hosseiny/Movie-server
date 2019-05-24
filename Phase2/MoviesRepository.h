#ifndef MOVIES_REPOSITORY_H
#define MOVIES_REPOSITORY_H

#include <vector>
#include <memory>
#include "Movie.h"
#include "MovieGraph.h"


class MoviesRepository
{

public:
	MoviesRepository();
	static std::shared_ptr<MoviesRepository> get_instance();

	void add_movie(std::string film_name, int year_of_production, int length_of_movie, double price_of_movie,
	 std::string summary_of_movie,  std::string director_of_movie, std::shared_ptr<Publisher> publisher);

	void edit_movie(int film_id, std::string film_name, int year_of_production, int length_of_movie, 
		double price_of_movie, std::string summary_of_movie,  std::string director_of_movie);

	std::vector<std::shared_ptr<Movie> > get_movies_of_publisher(std::shared_ptr<Publisher> publisher);

	bool film_is_new(std::string film_name);
	std::shared_ptr<Movie> get_movie(int movie_id);
	void show_movies(std::shared_ptr<Publisher> publisher, const std::string &name, 
	 int min_year, int max_year, double min_rate, double price, const std::string &director);

	void show_all_movies(const std::string &name, int min_year, int max_year,
	 double min_rate, double price, const std::string &director);

	void show_this_film(int film_id, std::shared_ptr<Member> member);

	void display_comments_and_recommendations(int film_id, std::shared_ptr<Member> member);


	void ignore_members_own_films(std::vector<std::shared_ptr<Movie> > &movies, 
	const std::vector<std::shared_ptr<Movie> > &members_movies);

	std::vector<std::shared_ptr<Movie> > send_recommendations(std::vector<int> users_movies_ids, int film_id);

	std::vector<std::shared_ptr<Movie> > get_recommended_movies(int film_id, std::shared_ptr<Member> member);

	std::vector<int> recommend_based_on_graph(std::vector<int> users_movies_ids, int film_id);

	std::vector<std::shared_ptr<Movie> > find_movies_by_id(std::vector<int> movies_ids);

	void display_recommendation(std::vector<std::shared_ptr<Movie> > movies);
	void display(std::vector<std::shared_ptr<Movie> > movies);


	static std::vector<std::shared_ptr<Movie> > filter(std::vector<std::shared_ptr<Movie> > all_movies_of_publisher, 
	const std::string &name, int min_year, int max_year, double min_rate, double price, const std::string &director);

	static bool apply_filter(std::shared_ptr<Movie> movie_of_publisher, const std::string &name, int min_year,
	 int max_year, double min_rate, double price, const std::string &director);

	static bool apply_director_filter(std::shared_ptr<Movie> movie, const std::string &director);

 	static bool apply_name_filter(std::shared_ptr<Movie> movie, const std::string name);

	static bool apply_min_year_filter(std::shared_ptr<Movie> movie, int min_year);

	static bool apply_max_year_filter(std::shared_ptr<Movie> movie, int max_year);

	static bool apply_min_rate_filter(std::shared_ptr<Movie> movie, double min_rate);

	static bool apply_price_filter(std::shared_ptr<Movie> movie, double price);


	static void display_films_info(std::vector<std::shared_ptr<Movie> > movies);
	static void display_info(std::vector<std::shared_ptr<Movie> > movies);

	void remove_movie(int film_id);

	void show_graph();

	void check_members_favorite_movies(const std::vector<int> purchased_movies_id);


private:
	static std::shared_ptr<MoviesRepository> the_instance;
	std::vector<std::shared_ptr<Movie> > all_movies;
	std::shared_ptr<MovieGraph> movie_graph;
} ;


#endif