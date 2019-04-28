
#ifndef GESTAOVENDAS_CV_H
#define GESTAOVENDAS_CV_H

#endif //GESTAOVENDAS_CV_H



#ifndef GESTAOVENDAS_SV_H
#define GESTAOVENDAS_SV_H

#endif //GESTAOVENDAS_SV_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pwd.h>


const char *PUBLIC = "/tmp/PUBLIC";
#define B_SIZE (PIPE_BUF/2)

struct message {
    char fifo_name[B_SIZE];
    char cmd_line[B_SIZE];
};
