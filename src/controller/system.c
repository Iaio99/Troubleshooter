#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

#include "../utils/commands.h"
#include "../utils/io.h"

int get_system_errors() {
#ifdef __linux__
	puts("Kernel errors");
	get_output("dmesg --level=err");
	puts("\n");
	puts("Kernel warnings");
        get_output("dmesg --level=warn");
#endif
}

bool get_host_info()
{
#ifdef __Win32__
	get_output("powershell Get-CimInstance Win32_OperatingSystem | Select-Object Caption, Version, BuildNumber, OSArchitecture");
#else
        struct utsname system_info;

        // Ottieni informazioni sul sistema
        if (uname(&system_info) != 0) {
            print_error("uname call failed");
            return 1;
        }

        // Stampa informazioni sul sistema
        printf("Operating System: %s\n", system_info.sysname);
        printf("Hostname: %s\n", system_info.nodename);
        printf("Release: %s\n", system_info.release);
#endif
}