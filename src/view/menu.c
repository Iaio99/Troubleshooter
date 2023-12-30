#include <stdio.h>
#include <stdlib.h>

#include "../controller/network.h"
#include "../controller/disks.h"
#include "../controller/cpu.h"
#include "../utils/io.h"

extern int menu()
{
	int opt;
	clear_screen();
	colorized_printf(BLUE, "__          __  _                            _         _______              _     _           _                 _            _ ");
	colorized_printf(BLUE, "\\ \\        / / | |                          (_)       |__   __|            | |   | |         | |               | |          | |");
	colorized_printf(BLUE, " \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___   _ _ __      | |_ __ ___  _   _| |__ | | ___  ___| |__   ___   ___ | |_ ___ _ __| |");
	colorized_printf(BLUE, "  \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | | '_ \\     | | '__/ _ \\| | | | '_ \\| |/ _ \\/ __| '_ \\ / _ \\ / _ \\| __/ _ \\ '__| |");
	colorized_printf(BLUE, "   \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | | | | |    | | | | (_) | |_| | |_) | |  __/\\__ \\ | | | (_) | (_) | ||  __/ |  |_|");
	colorized_printf(BLUE, "    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___| |_|_| |_|    |_|_|  \\___/ \\__,_|_.__/|_|\\___||___/_| |_|\\___/ \\___/ \\__\\___|_|  (_)");
	colorized_printf(BLUE, "Quale programma vuoi usare?");
	
	while(1) {
		colorized_printf(BLUE, "1. Gather network informations");
		colorized_printf(BLUE, "2. Test Connection");
		colorized_printf(BLUE, "3. Gather Disks informations");
		colorized_printf(BLUE, "4. Gather CPU informations");
		colorized_printf(BLUE, "5. Generate full report");
		colorized_printf(BLUE, "6. Exit");
		
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
			case 5:
				print_error("Not implemented yet!");
				break;
			case 6:
				return EXIT_SUCCESS;
				break;
			default:
				print_error("Unrecognized option");
				break;
		}

		if (yes_or_no("Do you want to leave?", 'y', 'n', true, true))
			return EXIT_SUCCESS;
		clear_screen();
	}
}