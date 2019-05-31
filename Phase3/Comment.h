#ifndef COMMENT_H
#define COMMENT_H
#include <string>
#include <memory>
#include <vector>


class Member;

class Comment
{

public:
	Comment(std::string comment_content, int comment_id, std::shared_ptr<Member> author);
	void set_reply(std::string comment_reply);
	int get_id();
	std::shared_ptr<Member> get_author();
	void get_replies();
	std::string get_content();
	   

private:
	int id;
	std::string content;
	std::vector<std::string> reply;
	std::shared_ptr<Member> author_of_comment;

};


#endif