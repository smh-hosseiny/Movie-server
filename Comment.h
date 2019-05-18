#ifndef COMMENT_H
#define COMMENT_H

#include <string>

class Comment
{

public:
	Comment(std::string comment_content, int comment_id);
	void set_reply(std::string comment_reply);
	   

private:
	int id;
	std::string content;
	std::string reply;

};


#endif