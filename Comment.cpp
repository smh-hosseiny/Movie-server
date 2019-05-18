#include "Comment.h"


using namespace std;


Comment :: Comment(string comment_content, int comment_id)
{
	id = comment_id;
	content = comment_content;
}

void Comment::set_reply(string comment_reply)
{
	reply = comment_reply;
}
