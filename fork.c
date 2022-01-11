// Written by Ozan Sazak <ozan.sazak@metu.edu.tr>
//
// Tests general functionality of getsiblings syscall - edited
// version of the example test code in the homework PDF.
//
// Compile and run:
// $ gcc -o fork fork.c
// $ ./fork
//
// Program lists the sibling pid's returned from getsiblings syscall
// on command line on success, and the return value with errno on
// failure.

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

#define N_CHILDREN  20

int main(int argc, char *argv[]) {
    int i, j, ret;
    pid_t infobuf[N_CHILDREN];

    for(i = 0; i < N_CHILDREN; i++){
        if (fork() == 0) {
            // child process
            if(i == (N_CHILDREN - 1)) {
                // Nth child
                ret = getsiblings(0, infobuf , N_CHILDREN);

                if (ret < 0) {
                    printf("getsiblings() returned %d (errno = %d)\n", ret, errno);
                    return 0;
                }

                for (j = 0; j < ret; j++)
                    printf("sibling[%d] = %d\n", j, infobuf[j]);
            }

            sleep(10);
            break;
        }
    }

    sleep(10);
    return 0;
}