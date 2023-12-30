#include <stdio.h>
#include <stdlib.h>

#include "../controller/commands.h"
#include "../controller/network.h"
#include "../controller/disks.h"
#include "../controller/cpu.h"
#include "../utils/io.h"

int menu()
{
	int opt;
	
colorized_puts(BLUE, "__          __  _                            _         _______              _     _           _                 _            _ ");
colorized_puts(BLUE, "\\ \\        / / | |                          (_)       |__   __|            | |   | |         | |               | |          | |");
colorized_puts(BLUE, " \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___   _ _ __      | |_ __ ___  _   _| |__ | | ___  ___| |__   ___   ___ | |_ ___ _ __| |");
colorized_puts(BLUE, "  \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | | '_ \\     | | '__/ _ \\| | | | '_ \\| |/ _ \\/ __| '_ \\ / _ \\ / _ \\| __/ _ \\ '__| |");
colorized_puts(BLUE, "   \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | | | | |    | | | | (_) | |_| | |_) | |  __/\\__ \\ | | | (_) | (_) | ||  __/ |  |_|");
colorized_puts(BLUE, "    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___| |_|_| |_|    |_|_|  \\___/ \\__,_|_.__/|_|\\___||___/_| |_|\\___/ \\___/ \\__\\___|_|  (_)");
	colorized_puts(BLUE, "Quale programma vuoi usare?");
	
	while(1) {
		colorized_puts(BLUE, "1. Gather network informations");
		colorized_puts(BLUE, "2. Test Connection");
		colorized_puts(BLUE, "3. Gather Disks informations");
		colorized_puts(BLUE, "4. Gather CPU informations");
		colorized_puts(BLUE, "5. Exit");
		
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
				colorized_puts(BLUE, "Bye!");
				return EXIT_SUCCESS;
				break;
			default:
				print_error("Unrecognized option");
				break;
		}
	}
}