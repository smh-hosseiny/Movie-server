#include "Comment.h"
#include <iostream>


using namespace std;


Comment :: Comment(string comment_content, int comment_id, shared_ptr<Member> author)
{
	id = comment_id;
	content = comment_content;
	author_of_comment = author;
}

void Comment::set_reply(string comment_reply)
{
	reply.push_back(comment_reply);
}

int Comment::get_id()
{
	return id;
}

string Comment:: get_content()
{
	return content;
}

shared_ptr<Member> Comment::get_author()
{
	return author_of_comment;
}

void Comment::get_replies()
{
	for(int i=0; i<reply.size(); i++)
	{
		cout << id << "." << i+1 << " " << reply[i] << endl;
	}
}
