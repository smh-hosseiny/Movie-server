#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include <memory>

class Publisher;

class Movie
{

public:
	Movie(int id, std::string name, int year, int length, double price,
		std::string summary,  std::string director, std::shared_ptr<Publisher> publisher);
   
   	void edit(std::string name, int year, int length, double price,
		std::string summary,  std::string director);
   
	std::string get_name();
	int get_id();
	int get_length();
	int get_year();
	double get_rate();
	double get_price();
	std::string get_director();
	std::string get_summary();
	std::shared_ptr<Publisher> get_publisher();

private:
	std::string film_name;
	int id;
	int year_of_production;
	int length_of_movie;
	double price_of_movie;
	std::string director_of_movie;
	std::string summary_of_movie;

	double rate=0;

	std::shared_ptr<Publisher> my_publisher;

};


#endif