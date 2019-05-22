#ifndef PUT_Handler_H
#define PUT_Handler_H

#include "Command_Handler.h"


class PUT_Handler : public Command_Handler
{
private:
	static std::shared_ptr<PUT_Handler> the_instance;

public:
	static std::shared_ptr<PUT_Handler> get_instance();
	virtual void handle(const std::vector<std::string> &command);
	void handle_editing_film(const std::vector<std::string> &input);
	void set_changed_parameters(const std::vector<std::string> &input, std::string &name, int &year, int &length,
 								double &price,	std::string &summary, std::string &director);


};

#endif