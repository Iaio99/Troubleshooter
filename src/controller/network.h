#pragma once

#include <stdbool.h>
#include <stddef.h>

void get_network_info(void);
bool ping(const char *target);
void test_connection();