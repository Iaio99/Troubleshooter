#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
#include <resolv.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

#include "network.h"
#include "../utils/io.h"
#include "../utils/validation.h"

static bool ping (const char *target) {
	char command[256];
#ifdef _WIN32
    	snprintf(command, sizeof(command), "ping -n 1 %s > nul", target);
#else 
	snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null", target);
#endif
    	int result = system(command);

    	return result == 0 ? 1 : 0;
}

static char *get_gateway(const char *ifname)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return NULL;
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);

    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
        perror("ioctl");
        close(sockfd);
        return NULL;
    }

    const struct sockaddr_in *addr = (struct sockaddr_in *)&ifr.ifr_addr;
    char *gateway = inet_ntoa(addr->sin_addr);

    close(sockfd);

    return gateway;
}

static char **get_dns()
{
	_res.options |= RES_INIT;
    	struct __res_state res;

    	if (res_ninit(&res) != 0)
    	    	return NULL;

	char **dns_list = malloc((res.nscount+1)*INET_ADDRSTRLEN);

        for (int i = 0; i < res.nscount; i++) {
             dns_list[i] = inet_ntoa(res.nsaddr_list[i].sin_addr);
	     dns_list[INET_ADDRSTRLEN] = 0;
        }

	dns_list[res.nscount] = NULL;

	return dns_list;
}

extern void test_connection() {
	if (!ping("google.com"))
		print_error("DNS not working");
	
	char ip_test[INET_ADDRSTRLEN + 1];

	while (1) {
		printf("Give me a public IPv4 (8.8.8.8 for example): ");
		fflush(stdout);
		fgets(ip_test, INET_ADDRSTRLEN, stdin);
		ip_test[strlen(ip_test) - 1] = '\0';

		if (validate_ip_address(ip_test))
			break;
		print_error("The IPv4 Address inserted is not valid");
	}

	if (!ping(ip_test))
		print_error("Internet not working");
	else
		colorized_printf(GREEN, "All test passed!");
}


extern void get_network_info()
{
#ifdef _WIN32
	get_output("ipconfig");
#else
	struct ifaddrs *ifap;
	const struct sockaddr_in *sa;
	
	if (getifaddrs(&ifap) == -1) {
		print_error("getifaddrs");
		exit(EXIT_FAILURE);
	}

	printf("Interface       IP Address      Netmask         Gateway         DNS\n");

	for (struct ifaddrs *ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_INET) {
			continue;
		}

		sa = (struct sockaddr_in *) ifa->ifa_addr;
		char ip_address[INET_ADDRSTRLEN];
		char netmask[INET_ADDRSTRLEN];
		char *gateway;
		const char *dns = "N/A";

		inet_ntop(AF_INET, &sa->sin_addr, ip_address, INET_ADDRSTRLEN);

		sa = (struct sockaddr_in *) ifa->ifa_netmask;
		inet_ntop(AF_INET, &sa->sin_addr, netmask, INET_ADDRSTRLEN);

		// Note: The gateway information might not be accurate, as it requires additional
		// system-specific code to retrieve the default gateway.

		gateway = get_gateway(ifa->ifa_name);

		if (gateway == NULL)
			gateway = "N/A";

		printf("%-16s%-16s%-16s%-16s%-16s\n", ifa->ifa_name, ip_address, netmask, gateway, dns);
	}

	freeifaddrs(ifap);
#endif
}