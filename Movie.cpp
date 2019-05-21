#include "Movie.h"
#include "Member.h"
#include "Comment.h"
#include "NotFound.h"
#include "Exception.h"
#include <algorithm>
#include <iostream>

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
	rate = 0;
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


void Movie::set_score(int score, const string username)
{
	scores[username] = score;
	update_rate(username);
}

void Movie::update_rate(const string username)
{
	double num_of_scores = scores.size();
	int sum_of_scores = 0;
	sum_of_scores += scores.at(username);
	rate = sum_of_scores/num_of_scores;
}

void Movie::set_comment(const string &content, shared_ptr<Member> author)
{
	int comment_id = comments.size()+1;
	comments.push_back(make_shared<Comment>(Comment(content, comment_id, author)));
}


shared_ptr<Comment> Movie::get_comment(int comment_id)
{
	for(auto &elem : comments)
	{
		if(elem->get_id() == comment_id)
			return elem;
	}
	throw NotFound();
}


void Movie::set_reply_to_comment(int comment_id, const string &content, const string name_of_movie,
	const shared_ptr<Member> publisher)
{
	try
	{
		shared_ptr<Comment> comment = get_comment(comment_id);
		comment -> set_reply(content);
		shared_ptr<Member> author = comment->get_author();
		author -> recieve_notification("Publisher " + publisher->get_username() +
		" with id " + to_string(publisher->get_id()) + " reply to your comment");
	}
	catch(const Exception &e)
	{
		throw;
	}
}


void Movie:: remove_comment(int comment_id)
{
	try
	{
		for(auto &elem : comments)
		{
			if(elem -> get_id() == comment_id)
			{
				comments.erase(find(comments.begin(), comments.end(), elem));
				return;
			}
		}
		throw NotFound();
	}
	catch(const Exception &e)
	{
		throw;
	}
}

void Movie::display_comments()
{
	for(auto &elem : comments)
	{
		cout << elem->get_id() << elem->get_content() << endl;
		elem -> get_replies();
	}
	cout << endl;
}