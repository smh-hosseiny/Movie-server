#include "Customer.h"
#include "Member.h"

using namespace std;


Customer :: Customer(string user_name, string pass, string e_mail, int Age, int id)
	: Member(user_name, pass, e_mail, Age, id)
{}


string Customer :: get_membership_type()
{
	return "Customer";
}