## Compiling

```bash
nasm -f elf csm_main.asm
nasm -f elf m_scalls.asm
gcc -m32 -Wall -g -c csm_test.c
ld -m elf_i386 csm_main.o m_scalls.o csm_test.o -o test_prog
