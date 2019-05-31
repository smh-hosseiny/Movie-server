#ifndef GET_Handler_H
#define GET_Handler_H

#include "Command_Handler.h"


class GET_Handler : public Command_Handler
{
private:
	static std::shared_ptr<GET_Handler> the_instance;

public:
	static std::shared_ptr<GET_Handler> get_instance();

	virtual void handle(const std::vector<std::string> &command);
	
	void handle_displaying_followers();
	std::string set_filter(const std::vector<std::string> &command, const std::string &parameter);
	void set_filters(const std::vector<std::string> &input, std::string &name, int &min_year,
		int &max_year, double &min_rate, double &price, std::string &director);
	void handle_showing_films(const std::vector<std::string> &command);
	void handle_showing_purchased_films(const std::vector<std::string> &command);
	void handle_displaying_all_films(const std::vector<std::string> &command);
	void show_all_movies(const std::vector<std::string> &command);
	void handle_showing_member_money();
};

#endif