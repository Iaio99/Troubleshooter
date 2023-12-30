#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "io.h"

jmp_buf leave_buff;
bool io_initialized;

static void leave(void)
{
	if(io_initialized)
		longjmp(leave_buff, 1);
	else
		exit(EXIT_SUCCESS);
}

int colorized_puts(int color, char *fmt, ...)
{
        va_list argList;
        va_start(argList, fmt);

        char new_fmt[strlen(fmt)+15];
        sprintf(new_fmt, "\033[0;%dm%s\033[0;%dm\n", color, fmt, RESET);

        int res =  vprintf(new_fmt, argList);

        va_end(argList);

        return res;
}

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

bool yes_or_no(char *question, char yes, char no, bool default_answer, bool insensitive)
{
	int extra;

	// yes and no characters should be lowercase by default
	yes = (char)tolower(yes);
	no = (char)tolower(no);

	// Which of the two is the default?
	char s, n;
	if(default_answer) {
		s = (char)toupper(yes);
		n = no;
	} else {
		s = yes;
		n = (char)toupper(no);
	}

	while(true) {
		printf("%s [%c/%c]: ", question, s, n);
		extra = 0;

		char c = (char)getchar();
		char ch = 0;
		if(c != '\n') {
			while(((ch = (char)getchar()) != EOF) && (ch != '\n'))
				extra++;
		}
		if(c == EOF || ch == EOF) {
			printf("EOF received, leaving...\n");
			fflush(stdout);
			leave();
		}
		if(extra > 0)
			continue;

		// Check the answer
		if(c == '\n') {
			return default_answer;
		} else if(c == yes) {
			return true;
		} else if(c == no) {
			return false;
		} else if(c == toupper(yes)) {
			if(default_answer || insensitive) return true;
		} else if(c == toupper(no)) {
			if(!default_answer || insensitive) return false;
		}
	}
}