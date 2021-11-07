sandbox: sandbox.o
	ld -m elf_i386 -o sandbox sandbox.o

sandbox.o: sandbox.asm
	nasm -f elf -g -F stabs sandbox.asm -l sandbox.lst -o sandbox.o

clean:
	rm -v sandbox.o sandbox.lst sandbox

# 64 bit:
# ld -o sandbox sandbox.o
# nasm -f elf64 -g -F stabs sandbox.asm -l sandbox.lst -o sandbox.o
