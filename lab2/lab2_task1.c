#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ITER 150

void print_ids(void);
void parentProcess(void);
void childProcess(void);


int main(void) {
  pid_t pid, gid, sid, fork_id;
  pid = getpid(); // always succeeds
  gid = getgid(); // always succeeds
  sid = getsid(pid);

  if (sid == -1) {
    printf("Error occured while trying to get sid of process");
  }
  printf("INITIAL: PID: %d, GID: %d, SID: %d\n", pid, gid, sid);

  fork_id = fork();
  if (fork_id < 0) {
    printf("Error occured while trying to fork()");
  }
  else if (fork_id == 0) {
    childProcess();
    printf("\nCHILD PROCESS ENDED, exiting the program...\n");
  }
  else {
    // fork_id > 0 - it's child's ID
    parentProcess();
    printf("\nPARENT PROCESS ENDED, exiting the program...\n");
  }

  return 0;
}

void print_ids(void) {
  int i;
  for (i = 0; i < ITER; i++) {
    pid_t pid, gid, sid;
    pid = getpid();
    gid = getgid();
    sid = getsid(pid);
    printf("ITERATION: %d; PID: %d, GID: %d, SID: %d\n", i, pid, gid, sid);
  }
}

void parentProcess(void) {
  int waitResultInfo;
  print_ids();
  wait(&waitResultInfo);
  // analyze waitResultInfo if necessary
}

void childProcess(void) {
  print_ids();
}
