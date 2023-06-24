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
