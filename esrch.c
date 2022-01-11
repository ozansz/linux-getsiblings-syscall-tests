// Written by Ozan Sazak <ozan.sazak@metu.edu.tr>
//
// Tests ESRCH return from getsiblings when the process specified
// by the pid parameter does not exist.
//
// Compile and run:
// $ gcc -o esrch esrch.c
// $ ./esrch
//
// Program writes "Success" with the return value and errno on command
// line on success, "Fail" with the return value and errno on failure.

#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define NR_GETSIBLINGS 441
#define getsiblings(p, b, c) syscall(NR_GETSIBLINGS, p, b, c)

#define SUCC printf("Success: ret = ESRCH (errno = %d)\n", errno)
#define FAIL printf("Fail: ret = %d, errno = %d, expected ESRCH (%d)\n", ret, errno, ESRCH)

int main(int argc, char *argv[]) {
    int ret;
    pid_t infobuf[30];

    pid_t test_pids[] = {32767, -1, -999};

    for (int i = 0; i < sizeof(test_pids)/sizeof(pid_t); i++) {
        ret = getsiblings(test_pids[i], infobuf, 30);
        ((ret == -ESRCH) || ((ret < 0) && (errno == ESRCH))) ? SUCC : FAIL;
    }

    return 0;
}