#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/route.h>
#include <resolv.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "network.h"


bool ping (const char *target) {
	char command[256];
#ifdef _WIN32
    snprintf(command, sizeof(command), "ping -n 1 %s > nul", target);
#else 
	snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null", target);
#endif
    // Esegui il comando ping e controlla il risultato
    int result = system(command);

    // Il risultato di system restituisce il codice di uscita del comando ping
    // 0 indica successo (ping riuscito), mentre altri valori indicano un errore
    return result == 0 ? 1 : 0;
}


void test_connection() {
	if (!ping("google.com"))
		printf("[ERROR] DNS not working\n");
	if (!ping("8.8.8.8"))
		printf("[ERROR] Internet not working\n");
	else
		printf("All test passed!\n");
}


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