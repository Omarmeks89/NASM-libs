#ifndef SCALLS_H_ENTRY
#define SCALLS_H_ENTRY

typedef int s_fd;

typedef enum io_streams {
	s_stdin = 0,
	s_stdout = 1,
	s_stderr = 2,
} s_io_streams;

#define SO_CREAT 0x040
#define SO_RDWR 0x002
#define SO_DEF_MODE 0x022

int s_write(s_fd fd, const void *buff, int size);

int s_exit(int st_code);

int s_read(s_fd fd, void *buff, int size);

s_fd s_open(const char *path, int oflag, int mode);

int s_close(s_fd fd);

extern int s_errno;
extern int so_creat;
#endif
