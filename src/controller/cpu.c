#include <stdio.h>
#include <stdlib.h>
#include <libcpuid.h>

void get_cpu_info() {
    #ifdef _WIN32
    system("wmic cpu get Name,NumberOfCores,NumberOfLogicalProcessors,MaxClockSpeed");
    #else
    struct cpu_raw_data_t raw;
    struct cpu_id_t data;

    if (cpuid_get_raw_data(&raw) != 0 || cpu_identify(&raw, &data) < 0) {
        fprintf(stderr, "Errore nell'identificazione della CPU\n");
        exit(-1);
    }

    printf("Modello: %s\n", data.brand_str);
    printf("Frequenza massima: %.2f GHz\n", cpu_clock_measure(200, 4) / 1000.0);
    printf("Numero di core fisici: %d\n", data.num_cores);
    printf("Numero di core logici: %d\n", data.num_logical_cpus);
    #endif
}

