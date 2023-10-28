"DOC"
import cpuinfo

def get_cpu_info():
    "DOC"
    info = cpuinfo.get_cpu_info()
    model = info["brand_raw"]
    arch = info["arch"]

    if arch == "X86_64":
        level = get_x86_64_version(set(info["cpu_flags"]))
        print(level)

    return f"Modello CPU: {model}\nArchitettura CPU: {arch}"

def get_x86_64_version(cpu_flags: set):
    "DOC"
    if set(("lm", "cmov", "cx8", "fpu", "fxsr", "mmx", "syscall", "sse2")).issubset(cpu_flags):
        level = 1
        if set(("cx16", "popcnt", "sse4_1", "sse4_2", "ssse3")).issubset(cpu_flags) and "lahf" in cpu_flags or "lahf_lm" in cpu_flags:
            level = 2
            if set(("avx", "avx2", "bmi1", "bmi2", "f16c", "fma", "abm", "movbe", "xsave")).issubset(cpu_flags):
                level = 3
                if set(("avx512f", "avx512bw", "avx512cd", "avx512dq", "avx512vl")).issubset(cpu_flags):
                    level = 4

    return level
