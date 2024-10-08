#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char *buf = malloc(500);
	int fd1 = open("tmp.txt", O_WRONLY);
	int fd2 = open("ls.c", O_RDONLY);
	
	ssize_t bytes = read(fd2, buf, 500);
//	printf("buf =>\n%s", buf);
	write(fd1, buf, bytes); 
}
