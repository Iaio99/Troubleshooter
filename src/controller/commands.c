#include <stdio.h>
#include <stdlib.h>

#include "commands.h"

void get_output (char *command, FILE *debug)
{
        int ret;
        FILE *stream;
        char output[4096] = {0};

        stream = popen(command, "r");

        if (stream == NULL)
                exit(-1);

        fprintf(debug, "%s\n\n", command);
        fflush(debug);

        while ((ret = fread(output, sizeof(char), 4096, stream)) > 0) {
                fprintf(debug, "%s\n\n\n", output);
                fflush(debug);
        }

        pclose(stream);
}