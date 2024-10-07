#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 2048

int main(int argc, char *argv[]){

	char savedText[10][100];
	int fd;
	size_f nread;
	long total = 0;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		perror(argv[1];
	
	while((nread = read(fd, buffer, BUFSIZE) > 0)

	close(fd);
				


	char buf;
	Read(fd, &buf, 1);
	saveText[0][0] = buf;
	Read(fd, &buf, 1);
	saveText[0][1] = buf;
}
