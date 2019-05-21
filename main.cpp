#include <iostream>
#include "Netflix.h"
#include "Interface.h"

using namespace std;

int main(int argc,char* avgv[])
{
	Interface::get_instance() -> run_netflix();
}