#include <iostream>

#include "Windows.h"

#include "core/Root.h"

int main()
{
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	Root* r = new Root();
	delete r;

	return 0;
}