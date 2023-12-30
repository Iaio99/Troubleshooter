#include <stdio.h>
#include <stdlib.h>
#include <libcpuid.h>

#include "cpu.h"

extern void get_cpu_info() {
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

#ifdef __x86_64__
	get_x86_version(data.flags);
#endif
}

static void get_x86_version(uint8_t cpu_flags[])
{
	uint8_t level;
    	if (cpu_flags[CPU_FEATURE_LM] && cpu_flags[CPU_FEATURE_CMOV] &&
    	    cpu_flags[CPU_FEATURE_CX8] && cpu_flags[CPU_FEATURE_FPU] &&
    	    cpu_flags[CPU_FEATURE_FXSR] && cpu_flags[CPU_FEATURE_MMX] &&
    	    cpu_flags[CPU_FEATURE_SYSCALL] && cpu_flags[CPU_FEATURE_SSE2])
		level = 1;
	if (cpu_flags[CPU_FEATURE_CX16] && cpu_flags[CPU_FEATURE_LAHF_LM] &&
	    cpu_flags[CPU_FEATURE_POPCNT] && cpu_flags[CPU_FEATURE_SSE4_1] &&
	    cpu_flags[CPU_FEATURE_SSE4_2] && cpu_flags[CPU_FEATURE_SSSE3] &&
	    level == 1)
	    	level = 2;
	if (cpu_flags[CPU_FEATURE_AVX] && cpu_flags[CPU_FEATURE_AVX2] &&
	    cpu_flags[CPU_FEATURE_BMI1] && cpu_flags[CPU_FEATURE_BMI2] && 
	    cpu_flags[CPU_FEATURE_F16C] && cpu_flags[CPU_FEATURE_FMA3] &&
	    cpu_flags[CPU_FEATURE_ABM] && cpu_flags[CPU_FEATURE_MOVBE] &&
	    cpu_flags[CPU_FEATURE_XSAVE] && level == 2)
	    	level = 3;

	if (cpu_flags[CPU_FEATURE_AVX512F] && cpu_flags[CPU_FEATURE_AVX512BW] &&
	    cpu_flags[CPU_FEATURE_AVX512CD] && cpu_flags[CPU_FEATURE_AVX512DQ] &&
	    cpu_flags[CPU_FEATURE_AVX512VL] && level == 3)
	    	level = 4;
	
	printf("CPU supports x86-64-v%d\n", level);
}