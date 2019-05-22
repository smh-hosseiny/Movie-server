#ifndef DELETE_Handler_H
#define DELETE_Handler_H

#include "Command_Handler.h"

class DELETE_Handler : public Command_Handler
{
private:
	static std::shared_ptr<DELETE_Handler> the_instance;

public:
	static std::shared_ptr<DELETE_Handler> get_instance();
	virtual void handle(const std::vector<std::string> &command);
	void handle_removing_film(const std::vector<std::string> &command);
	void handle_deleting_comment(const std::vector<std::string> &command);

};

#endif