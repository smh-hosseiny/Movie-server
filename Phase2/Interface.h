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
	void handle_command(const std::vector<std::string> &command);
	bool handle_if_is_admin(const std::vector<std::string> &command);
	void handle_admin_command(const std::vector<std::string> &command);

};

#endif