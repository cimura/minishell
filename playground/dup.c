#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char *buf = malloc(500);
	int fd = open("tmp.txt", O_WRONLY);	

	ssize_t bytes = read(0, buf, 500);
	dup2(fd, 1);

	printf("from printf\n");
//	printf("buf =>\n%s", buf);
	//write(fd, buf, bytes); 
}
