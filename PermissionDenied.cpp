#include "PermissionDenied.h"

using namespace std;

string PermissionDenied::what() const
{
    return "Permission Denied\n";
}

string PermissionDenied::type() const
{
    return "PermissionDenied\n";
}