#include "BadParentId.h"

using namespace std;

const char * BadParentId :: what() const throw()
{
    return "Parent ID is not referring to a directory!";
}