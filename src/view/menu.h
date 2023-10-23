#pragma once

#ifdef _WIN32
void windows_menu();
#else
void posix_menu();
#endif