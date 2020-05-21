#include <stdio.h>
#include <stdlib.h>

#include "error_handling.h"
#include "file_manipulations.h"
#include "transform_text.h"


int     main(int argc, char **argv) {
    char    *buffer;
    int     bytes_rewritten;

    if (argc != 3)
        return argument_error();
    buffer = read_file_contents(argv[1]);
    if (buffer == NULL)
        return (1);
    bytes_rewritten = transform_text(buffer);
    write_result_to_file(argv[2], buffer, bytes_rewritten);
    free(buffer);
    return (0);
}

