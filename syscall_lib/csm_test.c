#include "s_calls.h"


int main(int argc, char *argv[])
{
	const char *path;
	s_fd fd;
	int bytes_cnt, ret;
	if (argc < 2) {
		s_write(s_stderr, "no_args\n", 8);
		return 1;
	}
	/* we`ve shift on add eax, 4 */
	path = argv[1];
	fd = s_open(path, SO_RDWR | SO_CREAT, SO_DEF_MODE);
	if (fd < 0) {
		s_write(s_stderr, "creation_failed\n", 16);
		return 2;
	}
	bytes_cnt = s_write(fd, "test_label\n", 11);
	if (bytes_cnt != 11) {
		s_write(s_stderr, "no_write\n", 9);
	}
	else {
		s_write(s_stdout, "done!\n", 6);
	}
	/* here is error in valgrind because of diff betw int and FILE struct as wished. */
	ret = s_close(fd);
	return ret;
}

