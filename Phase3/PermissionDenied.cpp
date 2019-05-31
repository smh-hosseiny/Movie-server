#include "PermissionDenied.h"

using namespace std;

string PermissionDenied::what() const
{
    return "Permission Denied\n";
}