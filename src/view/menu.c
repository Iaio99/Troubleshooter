#include <stdio.h>
#include <stdlib.h>

#include "../controller/commands.h"
#include "../controller/network.h"
#include "../controller/disks.h"
#include "../controller/cpu.h"

void menu()
{
	int opt;
	
	printf("Welcome in Troubleshooter!\n");
	printf("Quale programma vuoi usare?\n");
	
	while(1) {
		printf("1. Network info\n");
		printf("2. Test Connection\n");
		printf("3. Disks info\n");
		printf("4. CPU info\n");
		
		scanf("%d", &opt);
		getchar();
		
		switch (opt) {
			case 1:
				get_network_info();
				break;
			case 2:
				test_connection();
				break;
			case 3:
				list_disks();
				break;
			case 4:
				get_cpu_info();
				break;
			default:
				printf("Unrecognized option\n");
				break;
		}
	}
}