#ifndef BADPARENTID_H
#define BADPARENTID_H

#include <exception>
#include <string>

class BadParentId : public std :: exception
{
public:
const char* what() const throw();

};


#endif