#ifndef INTERFACE_H
#define INTERFACE_H

#include<vector>
#include <string>
#include <memory>

class Interface
{
private:
	static std::shared_ptr<Interface> the_instance;

public:
	static std::shared_ptr<Interface> get_instance();
	void run_netflix();
	std::vector<std::string>  split(std::string input);
	void handle_input(const std::vector<std::string> &input);
	void identify_command(const std::vector<std::string> &command);

	std::string get_parameter(const std::vector<std::string> &input, std::string parameter);
	int get_film_id(const std::vector<std::string> &input);
	bool isNumber(const std::string &input);
	bool is_publisher(const std::vector<std::string> &input);
	void check_syntax_errors(const std::vector<std::string> &input);

	void handle_post_command(const std::vector<std::string> &command);
	void handle_get_command(const std::vector<std::string> &command);
	void handle_put_command(const std::vector<std::string> &command);
	void handle_delete_command(const std::vector<std::string> &command);

	void handle_signup(const std::vector<std::string> &input);
	void handle_login(const std::vector<std::string> &input);
	void handle_charging_account(const std::vector<std::string> &input);
	void handle_getting_money();
	void handle_following(const std::vector<std::string> &input);
	void handle_displaying_followers();

	void handle_adding_film(const std::vector<std::string> &input);
	void handle_editing_film(const std::vector<std::string> &input);
	void set_changed_parameters(const std::vector<std::string> &input, std::string &name, int &year, 
		int &length, double &price,	std::string &summary, std::string &director);

	void set_filters(const std::vector<std::string> &input, std::string &name, int &min_year,
		int &max_year, double &min_rate, double &price, std::string &director);
	void handle_showing_films(const std::vector<std::string> &command);
	void handle_removing_film(const std::vector<std::string> &command);
	void handle_buying_film(const std::vector<std::string> &command);
	void handle_showing_purchased_films(const std::vector<std::string> &command);
	void handle_displaying_all_films(const std::vector<std::string> &command);
	void handle_rating_film(const std::vector<std::string> &command);
	void handle_commenting_film(const std::vector<std::string> &command);
	void handle_deleting_comment(const std::vector<std::string> &command);
	void handle_replying(const std::vector<std::string> &command);


};

#endif