#include "view/menu.h"

int main()
{
	#ifdef _WIN32
	windows_menu();
	#else
	posix_menu();
	
	return 0;
}