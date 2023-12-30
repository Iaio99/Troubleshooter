#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/socket.h>

extern void get_network_info(void);
static bool ping(const char *target);
extern void test_connection();
static char *get_gateway(const char *ifname);
static char **get_dns();