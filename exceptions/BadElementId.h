#ifndef BADELEMENTID_H
#define BADELEMENTID_H
#include <exception>
#include <string>

class BadElementId : public std::exception
{
public:
const char* what() const throw();

};


class NotFound : public std::exception
public:
	const char* what() const throw();

};



#endif