#include "BadRequest.h"

using namespace std;

string BadRequest::what() const
{
    return "Bad Request\n";
}

string BadRequest::type() const
{
    return "BadRequest\n";
}