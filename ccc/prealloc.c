
#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if(argc != 4) {
        printf("usage: %s path count per_file_size\n", argv[0]);
        return -1;
    }

    char* path = argv[1];
    uint32_t count = atoi(argv[2]);
    uint64_t size = atoll(argv[3]);
    char filename[1024] = {0};

    for(int i=0; i<count; i++) {
        sprintf(filename, "%s/%llu_%06d", path, size, i);
        int fd = open(filename, O_RDWR|O_CREAT|O_LARGEFILE);
        fallocate(fd, 0, 0, size);
        //        posix_fallocate(fd, 0, size);
        close(fd);
        //        printf("%s\n", filename);
        memset(filename, 0, sizeof(filename));
    }

    return 0;
}


