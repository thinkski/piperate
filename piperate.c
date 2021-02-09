#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
	struct pollfd fds[] = {
		{
			.fd = STDIN_FILENO,
			.events = POLLIN
		}
	};

	unsigned char buffer[4096];
	ssize_t n_read, n_write, n_write_sum = 0;
	time_t t = time(NULL);

	// read and copy data
	while (-1 != poll(fds, sizeof(fds) / sizeof(struct pollfd), 1000)) {
		// read buffer
		if (n_read = read(STDIN_FILENO, buffer, sizeof(buffer)), -1 == n_read) {
			fprintf(stderr, "%s\n", strerror(errno));
			break;
		}

		// write buffer
		if (n_write = write(STDOUT_FILENO, buffer, n_read), -1 == n_write) {
			fprintf(stderr, "%s\n", strerror(errno));
			break;
		}

		// tally
		n_write_sum += n_write;

		// print
		if (time(NULL) != t) {
			char *units = "bytes/sec";

			if (n_write_sum > 1024) {
				n_write_sum >>= 10;
				units = "KB/sec";
			}
			if (n_write_sum > 1024) {
				n_write_sum >>= 10;
				units = "MB/sec";
			}
			if (n_write_sum > 1024) {
				n_write_sum >>= 10;
				units = "GB/sec";
			}

			fprintf(stderr, "%zd %s\n", n_write_sum, units);
			n_write_sum = 0;
			t = time(NULL);
		}
	}

	return 0;
}
