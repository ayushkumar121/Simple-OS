compile:
	nasm -g -f elf boot/bootloader_2.asm -o bin/bootloader_2.o
	gcc -m32 -c kernel/kernel.c -o bin/kernel.o -w -ffreestanding -fno-pie -fno-stack-check -fno-stack-protector -mno-stack-arg-probe
	ld -m elf_i386 -T linker/linker.ld -o bin/kernel.bin bin/bootloader_2.o bin/kernel.o
	cp bin/kernel.bin bin/build/boot/kernel.bin -f
	tar -czvf  bin/build/boot/data.tar data
	grub-mkrescue -o bin/kernel.iso bin/build
	rm bin/kernel.bin
	rm bin/bootloader_2.o
	rm bin/kernel.o
test:
	nasm -f elf -o test/test.o test/test.asm
	ld -m elf_i386 -T linker/linker.ld -o bin/build/boot/test.bin test/test.o
	grub-mkrescue -o bin/test.iso bin/build