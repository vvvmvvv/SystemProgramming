#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "error_handling.h"

char    *read_file_contents(char *filename) {
    int         fd;
    int         really_read;
    char        *buf;
    const int   chunck_size = 16;
    int         current_buf_size;
    int         shift;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return file_opening_error(filename);
    shift = 0;
    current_buf_size = chunck_size * 2;
    buf = (char *)malloc(current_buf_size * sizeof(char));
    really_read = chunck_size;
    while (chunck_size == really_read) {
        if (shift + chunck_size >= current_buf_size) {
            current_buf_size *= 2;
            buf = realloc(buf, current_buf_size);
        }
        really_read = read(fd, buf + shift, chunck_size);
        shift += really_read;
        buf[shift] = '\0';
    }
    close(fd);
    return (buf);
}

void    write_result_to_file(char *filename, char *buf, int rewritten) {
    int     fd;
    char    result_str[80];

    fd = open(filename, (O_WRONLY | O_CREAT), 0644);
    if (fd < 0) {
        file_opening_error(filename);
        return;
    }
    write(fd, buf, strlen(buf));
    sprintf(result_str, "\nTotal bytes modified: %i\n", rewritten);
    write(fd, result_str, strlen(result_str));
    close(fd);
}
