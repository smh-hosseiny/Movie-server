#ifndef PERMISSIONDENIED_H
#define PERMISSIONDENIED_H
#include "Exception.h"
#include <string>


class PermissionDenied : public Exception
{
public:
	virtual std::string what() const;
};



#endif