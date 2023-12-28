#include <stdio.h>
#include <stdlib.h>

#include "../controller/commands.h"
#include "../controller/network.h"

void menu()
{
	int opt;
	
	printf("Welcome in Troubleshooter!\n");
	printf("Quale programma vuoi usare?\n");
	
	while(1) {
		printf("1. Network info\n");
		
		scanf("%d", &opt);
		getchar();
		
		switch (opt) {
			case 1:
				get_network_info();
				break;
			default:
				printf("Unrecognized option\n");
				break;
		}
	}
}