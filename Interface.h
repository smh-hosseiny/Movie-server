#ifndef INTERFACE_H
#define INTERFACE_H

#include<vector>
#include <string>


std::vector<std::string> read_input();
std::vector<std::vector<std::string> > get_input();
std::vector<std::vector<std::string> > split(std::vector<std::string>);

std::string get_parameter(const std::vector<std::string> &input, std::string parameter);
bool is_publisher(const std::vector<std::string> &input);
void check_syntax_errors(const std::vector<std::string> &input);

void handle_input(const std::vector<std::vector<std::string> > &input);
void identify_command(const std::vector<std::string> &command);
void handle_post_command(const std::vector<std::string> &command);
void handle_get_command(const std::vector<std::string> &command);
void handle_put_command(const std::vector<std::string> &command);
void handle_delete_command(const std::vector<std::string> &command);

void handle_signup(const std::vector<std::string> &input);
void handle_login(const std::vector<std::string> &input);
void handle_charge_account(const std::vector<std::string> &input);
void handle_following(const std::vector<std::string> &input);

void handle_adding_film(const std::vector<std::string> &input);
void handle_editing_film(const std::vector<std::string> &input);
void set_changed_parameters(const std::vector<std::string> &input, std::string &name, int &year, 
	int &length, double &price,	std::string &summary, std::string &director);
void handle_showing_films(const std::vector<std::string> &command);
void handle_removing_film(const std::vector<std::string> &command);
void handle_buying_film(const std::vector<std::string> &command);
void handle_showing_purchased_films(const std::vector<std::string> &command);



#endif