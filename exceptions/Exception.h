#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception
{
public:
    virtual std::string what() = 0;
};


#endif