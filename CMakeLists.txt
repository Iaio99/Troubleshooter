cmake_minimum_required(VERSION 3.13)
project(troubleshooter C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(troubleshooter
        src/main.c
        src/controller/cpu.c
        src/controller/disks.c
        src/controller/network.c
        src/controller/system.c
        src/utils/commands.c
        src/utils/io.c
        src/utils/validation.c
	    src/view/menu.c
)

include_directories(/usr/include/libcpuid)
target_link_libraries(troubleshooter cpuid blkid udev)

if(MSVC)
    add_compile_options(PRIVATE /W4 /WX)
else()
    add_compile_options(PRIVATE -Wall -Wextra -Wpedantic -Werror -O2)
endif()