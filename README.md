# Description


## Syscall strace
```bash
[00007f33270eb0fb] execve("./test_prog", ["./test_prog", "new_file2"], 0x7ffcc6222660 /* 47 vars */) = 0
[0804912b] [ Process PID=18728 runs in 32 bit mode. ]
[0804912b] open("new_file2", O_RDWR|O_CREAT, 0666) = 3
[08049034] write(3, "test_label\n", 11) = 11
[08049034] write(1, "done!\n", 6done!
)       = 6
[08049162] close(0)                     = 0
[0804901d] exit(0)                      = ?
[????????] +++ exited with 0 +++
```
