#include "view/menu.h"
#include "utils/io.h"

int main()
{
	int res;
	res = menu();
	colorized_puts(BLUE, "Bye!");
	
	return res;
}