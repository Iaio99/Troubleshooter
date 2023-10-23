#pragma once

#ifdef _WIN32
char *win_commands [] = {"Compmgmt.msc", "Certmgr.msc", "Devmgmt.msc","Diskmgmt.msc", "Eventvwr.msc", "Virtmgmt.ms", "Lusrmgr.msc", "Perfmon.msc", "Printmanagement.msc", "Scervices.msc", "Taskschd.msc", "tpm.msc", "Wf.msc", "regedit", "msinfo32", "start", "ping 8.8.8.8 -c 4", "systeminfo", "ipconfig"};
#endif

void get_output (char *command, FILE *debug);
