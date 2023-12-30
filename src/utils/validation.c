#include <stdbool.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#include "io.h"
#include "validation.h"

bool validate_ip_address(const char *str)
{
        char buf[sizeof(struct sockaddr_in)];
        int result = inet_pton(AF_INET, str, buf);

        return result == 1;
}