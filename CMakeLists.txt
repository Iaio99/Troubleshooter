cmake_minimum_required(VERSION 3.13)
project(troubleshooter C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(troubleshooter
        src/main.c
        src/controller/cpu.c
        src/controller/disks.c
        src/controller/commands.c
        src/controller/network.c
	    src/view/menu.c
)

include_directories(/usr/include/libcpuid)
target_link_libraries(troubleshooter cpuid)

if(MSVC)
    add_compile_options(PRIVATE /W4 /WX)
else()
    add_compile_options(PRIVATE -Wall -Wextra -Wpedantic -Werror -O2)
endif()