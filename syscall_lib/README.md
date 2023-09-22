## Compiling

If you will compile for Linux:

```bash
nasm -f elf -g -dOS_LNX csm_main.asm
nasm -f elf -g -dOS_LNX m_scalls.asm
```
If you will compile for BSD:

```bash
nasm -f elf -g -dOS_BSD csm_main.asm
nasm -f elf -g -dOS_BSD m_scalls.asm
```
final operations for both systems:

```bash
gcc -m32 -Wall -g -c csm_test.c
ld -m elf_i386 csm_main.o m_scalls.o csm_test.o -o test_prog
```

### Vagrind output

Valgrind command:

```bash
valgrind -s --track-origins=yes
```

I`ll fix next problem with unitialized bytes:

```bash
==19466== Memcheck, a memory error detector
==19466== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==19466== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==19466== Command: ./test_prog new_ff3
==19466== 
done!
==19466== Syscall param close(fd) contains uninitialised byte(s)
==19466==    at 0x8049162: ??? (m_scalls.asm:40)
==19466==    by 0x804900E: ??? (csm_main.asm:15)
==19466==  Uninitialised value was created by a stack allocation
==19466==    at 0x804918F: main (csm_test.c:5)
==19466== 
==19466== 
==19466== HEAP SUMMARY:
==19466==     in use at exit: 0 bytes in 0 blocks
==19466==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==19466== 
==19466== All heap blocks were freed -- no leaks are possible
==19466== 
==19466== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
==19466== 
==19466== 1 errors in context 1 of 1:
==19466== Syscall param close(fd) contains uninitialised byte(s)
==19466==    at 0x8049162: ??? (m_scalls.asm:40)
==19466==    by 0x804900E: ??? (csm_main.asm:15)
==19466==  Uninitialised value was created by a stack allocation
==19466==    at 0x804918F: main (csm_test.c:5)
==19466== 
==19466== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
