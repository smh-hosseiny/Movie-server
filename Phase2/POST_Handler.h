#ifndef POST_Handler_H
#define POST_Handler_H

#include "Command_Handler.h"


class POST_Handler : public Command_Handler
{
private:
	static std::shared_ptr<POST_Handler> the_instance;

public:
	static std::shared_ptr<POST_Handler> get_instance();
	virtual void handle(const std::vector<std::string> &command);
	void check_if_there_is_no_logged_in_member();
	void handle_signup(const std::vector<std::string> &input);
	void handle_login(const std::vector<std::string> &input);
	void handle_charging_account(const std::vector<std::string> &input);
	void handle_getting_money();
	void handle_following(const std::vector<std::string> &input);
	void handle_adding_film(const std::vector<std::string> &input);
	void handle_commenting_film(const std::vector<std::string> &command);
	void handle_replying(const std::vector<std::string> &command);
	void handle_buying_film(const std::vector<std::string> &command);
	void handle_rating_film(const std::vector<std::string> &command);

	void handle_editing_film(const std::vector<std::string> &input);
	void set_changed_parameters(const std::vector<std::string> &input, std::string &name, int &year, int &length,
		double &price,	std::string &summary, std::string &director);

	void handle_removing_film(const std::vector<std::string> &command);
	void handle_deleting_comment(const std::vector<std::string> &command);

	void handle_logout();
};


#endif