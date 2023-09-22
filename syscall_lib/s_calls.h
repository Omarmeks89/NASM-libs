#ifndef SCALLS_H_ENTRY
#define SCALLS_H_ENTRY

typedef int s_fd;

typedef struct m_iobuf {
	char *ptr;
	int cnt;
	char *base;
	int flag;
	int file;
	int charbuf;
	int bufsize;
	char *tmpfname;
} S_FILE;

typedef enum io_streams {
	s_stdin = 0,
	s_stdout = 1,
	s_stderr = 2,
} s_io_streams;

#define SO_CREAT 0x040
#define SO_RDWR 0x002
#define SO_DEF_MODE 0x1B6

int s_write(int fd, const void *buff, int size);

int s_exit(int st_code);

int s_read(int fd, void *buff, int size);

int s_open(const char *path, int oflag, int mode);

int s_close(int fd);

extern int s_errno;
extern int so_creat;
#endif
