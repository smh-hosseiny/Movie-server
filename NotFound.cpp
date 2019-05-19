#include "NotFound.h"

using namespace std;

string NotFound::what() const
{
    return "Not Found\n";
}

string NotFound::type() const
{
    return "NotFound\n";
}