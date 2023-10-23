cmake_minimum_required(VERSION 3.13)
project(troubleshooter C)

set(CMAKE_C_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(troubleshooter
        src/main.c
        src/controller/commands.c
	    src/view/menu.c
)

if(MSVC)
    add_compile_options(PRIVATE /W4 /WX)
else()
    add_compile_options(PRIVATE -Wall -Wextra -Wpedantic -Werror -O2)
endif()