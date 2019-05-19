#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception
{
public:
    virtual std::string what() const = 0;
    virtual std::string type() const = 0;
};


#endif