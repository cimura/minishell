#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        struct stat buf;
        int ret = stat(argv[1], &buf);
        
        if (ret == 0) {
            printf("File size: %lld bytes\n", (long long)buf.st_size);
            printf("File mode: %o\n", (unsigned int)buf.st_mode);
            printf("Last modified: %ld\n", buf.st_mtime);
        } else {
            perror("stat");
        }
    } else {
        printf("Usage: %s <file_path>\n", argv[0]);
    }
    return 0;
}

