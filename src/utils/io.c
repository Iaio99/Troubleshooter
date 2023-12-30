#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "io.h"

int colorized_puts(int color, char *fmt, ...)
{
        va_list argList;
        va_start(argList, fmt);

        char new_fmt[strlen(fmt)+15];
        sprintf(new_fmt, "\033[0;%dm%s\033[0;%dm\n", color, fmt, RESET);

        int res =  vprintf(new_fmt, argList);

        va_end(argList);

        return res;}

int print_error(char *fmt, ...)
{
        va_list argList;
        va_start(argList, fmt);

        char new_fmt[23+strlen(fmt)];
        sprintf(new_fmt, "\033[0;%dm[ERROR] %s\033[0;%dm\n", RED, fmt, RESET);

        int res =  vfprintf(stderr, new_fmt, argList);

        va_end(argList);

        return res;
}

void clear_screen(void)
{
        printf("\033[2J\033[H");
}