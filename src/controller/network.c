#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/route.h>
#include <resolv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "network.h"

void get_network_info()
{
#ifdef _WIN32
	get_output("ipconfig");
#else
	struct ifaddrs *ifap, *ifa;
	struct sockaddr_in *sa;
	
	if (getifaddrs(&ifap) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	printf("%-16s%-16s%-16s%-16s\n", "Interface", "IP Address", "Netmask", "Gateway", "DNS");

	for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_INET) {
			continue;
		}

		sa = (struct sockaddr_in *) ifa->ifa_addr;
		char ip_address[INET_ADDRSTRLEN];
		char netmask[INET_ADDRSTRLEN];
		char gateway[INET_ADDRSTRLEN];
		char dns[INET_ADDRSTRLEN];

		inet_ntop(AF_INET, &sa->sin_addr, ip_address, INET_ADDRSTRLEN);

		sa = (struct sockaddr_in *) ifa->ifa_netmask;
		inet_ntop(AF_INET, &sa->sin_addr, netmask, INET_ADDRSTRLEN);

		// Note: The gateway information might not be accurate, as it requires additional
		// system-specific code to retrieve the default gateway.
		strcpy(gateway, "N/A");

		res_init();
		for (int i = 0; i < _res.nscount; ++i) {
			strncpy(dns, inet_ntoa(_res.nsaddr_list[i].sin_addr), INET_ADDRSTRLEN);
			printf("%-16s%-16s%-16s%-16s%-16s\n", ifa->ifa_name, ip_address, netmask, gateway, dns);
		}
	}

	freeifaddrs(ifap);
#endif
}