#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include<vector>
#include <string>
#include <memory>
#include <algorithm>
#include "Exception.h"
#include "BadRequest.h"
#include "PermissionDenied.h"
#include "NotFound.h"
#include "Netflix.h"


#define ZERO 0
#define T_R_U_E "true"
#define USERNAME "username"
#define PASSWORD "password"
#define AGE "age"
#define EMAIL "email"
#define PUBLISHER "publisher"
#define POST "POST"
#define PUT "PUT"
#define GET "GET"
#define DELETE "DELETE"
#define NOTIFICATIONS "notifications"
#define QUESTION_SIGN "?"
#define LIMIT "limit"
#define READ "read"
#define FILMS "films"
#define NAME "name"
#define YEAR "year"
#define LENGTH "length"
#define PRICE "price"
#define SUMMARY "summary"
#define DIRECTOR "director"
#define PUBLISHED "published"
#define BUY "buy"
#define PURCHASED "purchased"
#define RATE "rate"
#define COMMENTS "comments"
#define SCORE "score"
#define CONTENT "content"
#define MIN_YEAR "min_year"
#define MAX_YEAR "max_year"
#define MIN_RATE "min_rate"
#define REPLIES "replies"
#define COMMENT_ID "comment_id"

#define SIGNUP "signup"
#define LOGIN "login"
#define MONEY "money"
#define AMOUNT "amount"
#define FOLLOWERS "followers"
#define USER_ID "user_id"
#define FILM_ID "film_id"

class Command_Handler
{
public:
	virtual void handle(const std::vector<std::string> &command) = 0;


	std::string get_parameter(const std::vector<std::string> &input, std::string parameter);
	int get_film_id(const std::vector<std::string> &input);
	bool isNumber(const std::string &input);
	bool is_publisher(const std::vector<std::string> &input);
	void check_syntax_errors(const std::vector<std::string> &input);


};

#endif