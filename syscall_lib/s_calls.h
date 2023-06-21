#ifndef SCALLS_H_ENTRY
#define SCALLS_H_ENTRY

int s_write(int fd, const void *buff, int size);

int s_exit(int st_code);

int s_read(int fd, void *buff, int size);

extern int s_errno;
#endif
