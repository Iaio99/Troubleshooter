#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <setjmp.h>

#define BLUE 34
#define YELLOW 33
#define RED 31
#define GREEN 32
#define RESET 0

extern int colorized_printf(int color, const char *fmt, ...);
extern int print_error(const char *fmt, ...);
extern bool yes_or_no(char *question, char yes, char no, bool default_answer, bool insensitive);
extern void clear_screen(void);
extern char *get_input(char *question, int len, char *buff);
