#inclued <iostream>

using namespace std;

class Exceptions
{
public:
	virtual string what() const = 0;

};


class NotFound : public Exceptions
{
public:
	string what() {return "Not Found";}

};


class BadRequest : public Exceptions
{
public:
	string what() {return "BadRequest";}

};

class PermissionDenied : public Exceptions
{
public:
	string what() {return "Permission Denied";}

};