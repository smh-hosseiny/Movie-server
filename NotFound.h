#ifndef NOTFOUND_H
#define NOTFOUND_H
#include "Exception.h"
#include <string>


class NotFound : public Exception
{
public:
	virtual std::string what() ;
};

#endif