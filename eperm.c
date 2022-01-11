// Written by Ozan Sazak <ozan.sazak@metu.edu.tr>
//
// Tests EPERM return from getsiblings when the calling process's
// user has no right to get the data of the process specified with
// the pid parameter.
//
// Compile and run:
// $ gcc -o eperm eperm.c
// $ ./eperm
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

#define SUCC printf("Success: ret = EPERM (errno = %d)\n", errno)
#define FAIL printf("Fail: ret = %d, errno = %d, expected EPERM (%d)\n", ret, errno, EPERM)

int main(int argc, char *argv[]) {
    int ret;
    pid_t infobuf[30];

    if (getuid() == 0) {
        printf("!!! You can not to run this test as root !!!\n");
        return 0;
    }

    ret = getsiblings(1, infobuf, 30);

    ((ret == -EPERM) || ((ret < 0) && (errno == EPERM))) ? SUCC : FAIL;

    return 0;
}