#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

void parentProcess(int * fd);
void childProcess();

int main(void) {
    int fd;
    ssize_t bytes_output;
    pid_t fork_id;

    fd = open("test.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    printf("\n%d\n", fd);
    if (fd == -1) {
      printf("Error while opening test.log for writing (initial)\n");
      return -1;
    }
    write(fd, "PROGRAM STARTED...\n",
    strlen("PROGRAM STARTED...\n"));

    // daemoning
    fork_id = fork();
    if (fork_id < 0) {
        write(fd, "Error occured while trying to fork()\n",
        strlen("Error occured while trying to fork()\n"));
        close(fd);
    }
    else if (fork_id == 0) {
        childProcess();
    }
    else {
        // fork_id > 0 - it's child's ID
        parentProcess(&fd);
    }

    return 0;
}

void parentProcess(int * fd) {
    printf("in parent process!\n");
    write((* fd), "The child has been created, exiting now...\n",
    strlen("The child has been created, exiting now...\n"));
    exit(EXIT_SUCCESS);
}

void childProcess() {
    pid_t newSid;
    char buff[100];
    int buff_length;
    int pid;
    int i;
    int fd;

    // setsid()
    newSid = setsid();
    if (newSid < 0) {
        printf("Error while calling setsid()\n");
    }
    // newSid contains current sid of the process, can be used if necessary
    // change directory
    if(chdir("/") == -1) {
        printf("Error while calling setsid()\n");
    }

    // closes all fds from parent (including stdin - 0, stdout - 1, stderr - 2)
    for(i = 255; i >= 3; i--) {
        printf("%d\n", i);
        close(i);
    }

    open("/dev/null",O_RDWR); // open /dev/null for stdin
    dup(0); // open /dev/null for stdout
    dup(0); // open /dev/null for stderr

    // Open test.log and write there child's parameters
    buff_length = sprintf(buff, "PID: %d, GID: %d, SID: %d\n", getpid(), getgid(), newSid);
   
 
    fd = open("/home/augustus_tertius/code/labs/6_term/system_programming/lab2/test.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
      printf("Error while opening test.log for writing (from daemon)\n");
      return;
    }
    write(fd, &buff, buff_length);
    close(fd);
    
    // infinite cycle
    while(1) {
        time_t cur = time(NULL);
        char * stime = ctime(&cur);
        // buff_length = sprintf(buff, "PID: %d, Current time is: %s", getpid(), stime);
        // write(fd, buff, buff_length); // uncomment
        printf("PID: %d, Current time is: %s", getpid(), stime);
    }
    // close(fd); // uncomment
}
