#include <stdio.h>
#include <string.h>

#define BLUE 34
#define YELLOW 33
#define RED 31
#define GREEN 32
#define RESET 0

int colorized_puts(int color, char *fmt, ...);
int print_error(char *fmt, ...);