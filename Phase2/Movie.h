#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include <map>
#include <memory>

class Publisher;
class Member;
class Comment;

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
	void set_score(int score, const std::string username);
	void update_rate(const std::string username);
	void set_comment(const std::string &content, std::shared_ptr<Member> author);
	std::shared_ptr<Comment> get_comment(int comment_id);
	void set_reply_to_comment(int comment_id, const std::string &content, const std::string name_of_movie,
	const std::shared_ptr<Member> publisher);
	void remove_comment(int comment_id);
	void handle_remove_comment(int comment_id);
	void display_comments();

private:
	std::string film_name;
	int id;
	int year_of_production;
	int length_of_movie;
	double price_of_movie;
	std::string director_of_movie;
	std::string summary_of_movie;

	double rate;
	std::map<std::string, int> scores;

	std::shared_ptr<Publisher> my_publisher;
	std::vector<std::shared_ptr<Comment> > comments;

};


#endif