#include <stdio.h>
#include <errno.h>
#include <string.h>


int     argument_error(void) {
    printf("Please, provide two filenames as arguments.\n");
    printf("./a.out filename1.txt filename2.txt\n");
    return (1);
}

char    *file_opening_error(char *filename) {
    printf("An error occured while opening file\n");
    printf("%s: %s\n", filename, strerror(errno));
    return (NULL);
}
