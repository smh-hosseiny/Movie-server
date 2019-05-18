#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <memory>
#include "Member.h"


class Customer : public Member
{

public:
	Customer(std::string username, std::string password, std::string email, int age, int id);
   	virtual std::string get_membership_type();

private:

};


#endif