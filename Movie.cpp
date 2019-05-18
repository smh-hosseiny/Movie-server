#include "Movie.h"
#include "Comment.h"

using namespace std;

Movie::Movie(int film_id, string name, int year, int length, double price,
 string summary, string director, shared_ptr<Publisher> publisher)
{
	id = film_id;
	film_name = name;
	year_of_production = year;
	length_of_movie= length;
	price_of_movie = price;
	summary_of_movie = summary;
	director_of_movie = director;
	my_publisher = publisher;
}

string Movie::get_name()
{
	return film_name;
}

int Movie::get_id()
{
	return id;
}

int Movie::get_length()
{
	return length_of_movie;
}

int Movie::get_year()
{
	return year_of_production;
}

double Movie::get_price()
{
	return price_of_movie;
}

string Movie::get_director()
{
	return director_of_movie;
} 

string Movie::get_summary()
{
	return summary_of_movie;
}

double Movie::get_rate()
{
	return rate;
}


shared_ptr<Publisher> Movie::get_publisher()
{
	return my_publisher;
}

void Movie::edit(string name, int year, int length, double price, string summary, string director)
{
	if(name != "")
		film_name = name;

	if(year != 0)
		year_of_production = year;

	if(length != 0)
		length_of_movie= length;

	if(price != 0)
		price_of_movie = price;

	if(summary != "")
		summary_of_movie = summary;

	if(director != "")
		director_of_movie = director;
}


void Movie::set_score(int score)
{
	scores.push_back(score);
	update_rate();
}

void Movie::update_rate()
{
	double num_of_scores = scores.size();
	int sum_of_scores;
	for(auto &elem : scores)
		sum_of_scores += elem;
	rate = sum_of_scores/num_of_scores;
}

void Movie::set_comment(string content)
{
	int comment_id = comments.size()+1;
	comments.push_back(make_shared<Comment>(Comment(content, comment_id)));
}

   