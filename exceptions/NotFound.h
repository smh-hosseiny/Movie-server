#ifndef NOTFOUND_H
#define NOTFOUND_H
#include <exception>
#include <string>


class NotFound : public std::exception
{
public:
	const char* what() const;
};



#endif