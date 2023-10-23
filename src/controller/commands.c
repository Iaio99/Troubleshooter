#include <stdio.h>
#include <stdlib.h>

#include "commands.h"

void get_output (char *command)
{
        int ret;
        FILE *stream;
        char output[4096] = {0};

        stream = popen(command, "r");

        if (stream == NULL)
                exit(-1);

        while ((ret = fread(output, sizeof(char), 4096, stream)) > 0) {
                printf("%s\n", output);
        }

        pclose(stream);
}