#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 200
#define N_VALIDCHARS 93    // Number of characters in the range of valid characters to be picked
#define FIRST_VALIDCHAR 33 // First character number in the range of valid characters to be picked

void help() {
	printf("\nusage: genpasswd SIZE\nSIZE must be an integer between 1 and %d\n", MAX);
}

int main(int argc, char* argv[]) {
	// Reading size
	if (argc <= 1) {
		printf("ERROR: no size specified\n");
		help();
		return 1;
	}
	
	int d = 1;
	if (sscanf(argv[1], "%d", &d) <= 0) {
		printf("ERROR: size read error or matching failure\n");
		help();
		return 1;
	}
	
	if (d < 1 || d > MAX) {
		printf("ERROR: invalid size\n");
		help();
	}

	// Opening /dev/urandom
	int fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1) {
		printf("ERROR: could not open /dev/urandom\n");
		return 1;
	}

	// Reading to buffer
	int buf[d];
	int rd = read(fd, buf, sizeof(buf));
	if (rd < d) {
		printf("ERROR: read error\n");
		close(fd);
		return 1;
	}

	// Printing
	for (int i = 0; i < d; ++i) {
		int rand = buf[i];
		if (rand < 0) rand *= -1;
		rand %= N_VALIDCHARS;
		putchar(rand + FIRST_VALIDCHAR);
	}

	close(fd);
	return 0;
}
