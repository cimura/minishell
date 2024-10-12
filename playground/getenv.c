#include <stdio.h>
#include <stdlib.h>

int main() {
	char *path = getenv("PATH");
	printf("PATH -> %s\n", path);	
}
