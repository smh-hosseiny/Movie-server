#ifndef BADREQUEST_H
#define BADREQUEST_H
#include "Exception.h"
#include <string>


class BadRequest : public Exception
{
public:
	virtual std::string what() const;
	virtual std::string type() const;
};



#endif