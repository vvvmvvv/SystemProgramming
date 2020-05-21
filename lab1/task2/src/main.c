#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <poll.h>


int    listen_to_stdin() {
    struct pollfd = {1, POLLIN};
    struct timeval  timeout = {5, 0};

    return poll(&pollfd, 1, &timeout);
}

int     wait_for_input(void) {
    int     result;

    result = 0;
    while (result == 0) {
        result = listen_to_stdin();
        if (result == -1) {
            dprintf(2, "An error occured: %s\n", strerror(errno));
            return (0);
        } else if(result == 0) {
            dprintf(2, "Nothing happened in past 5 seconds.\n");
            dprintf(2, "Trying again.\n\n");
        }
    }
    return (1);
}

char    *get_input(void) {
    char    *result;
    int     read_amount;

    result = (char *)malloc(1024 * sizeof(char));
    read_amount = read(1, result, 1024);
    result[read_amount] = '\0';
    return (result);
}

int     main(void) {
    char    *input;

    if (wait_for_input()) {
        input = get_input();
        printf("got input from fd 1:\n");
        printf("%s\n", input);
        free(input);
    }
    return (0);
}