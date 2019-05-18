#include "BadElementId.h"

using namespace std;

const char * BadElementId :: what() const throw()
{
    return "Invalid element ID requested!‬";
}