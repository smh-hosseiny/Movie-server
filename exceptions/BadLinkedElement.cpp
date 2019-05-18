#include "BadLinkedElement.h"

using namespace std;

const char * BadLinkedElement :: what() const throw()
{
    return "Invalid element type requested!";
}