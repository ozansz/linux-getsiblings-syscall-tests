// Written by Ozan Sazak <ozan.sazak@metu.edu.tr>
//
// Tests EINVAL return from getsiblings when pidbuf or capacity are
// passed with invalid values (NULL for pidbuf and <= 0 for capacity).
//
// Compile and run:
// $ gcc -o einval einval.c
// $ ./einval
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

#define SUCC printf("Success: ret = EINVAL (errno = %d)\n", errno)
#define FAIL printf("Fail: ret = %d, errno = %d, expected EINVAL (%d)\n", ret, errno, EINVAL)

int main(int argc, char *argv[]) {
    int ret;
    pid_t infobuf[30];

    pid_t *test_bufs[] = {infobuf, NULL, NULL};
    int    test_caps[] = {0,       30,   0};

    for (int i = 0; i < sizeof(test_caps)/sizeof(int); i++) {
        ret = getsiblings(0, test_bufs[i], test_caps[i]);
        ((ret == -EINVAL) || ((ret < 0) && (errno == EINVAL))) ? SUCC : FAIL;
    }

    return 0;
}