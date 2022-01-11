// Written by Ozan Sazak <ozan.sazak@metu.edu.tr>
//
// Tests if the root user can call getsiblings syscall with arbitrary
// PIDs.
//
// Compile and run:
// $ gcc -o root root.c
// $ ./root
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

#define SUCC printf("Success: ret = %d (errno = %d)\n", ret, errno)
#define FAIL printf("Fail: ret = %d, errno = %d, expected ret >= 0\n", ret, errno)

#define BUF_CAP 5
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int main(int argc, char *argv[]) {
    int ret;
    pid_t infobuf[BUF_CAP];

    if (getuid() != 0) {
        printf("!!! You need to be root to run this test !!!\n");
        return 0;
    }

    pid_t pid = 0;

    for (;;) {
        scanf("%d", &pid);
        printf("\npid = %d\n\n", pid);

        if (pid < 0)
            break;

        ret = getsiblings(pid, infobuf, BUF_CAP);

        if (ret < 0)
            FAIL;
        else {
            SUCC;

            for (int i = 0; i < MIN(ret, BUF_CAP); i++)
                printf("siblings[%d] = %d\n", i, infobuf[i]);
        }
    }

    return 0;
}