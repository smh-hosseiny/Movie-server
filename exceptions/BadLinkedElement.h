#ifndef BADLINKEDELEMENT_H
#define BADLINKEDELEMENT_H

#include <exception>
#include <string>

class BadLinkedElement : public std :: exception
{
public:
const char* what() const throw();

};


#endif