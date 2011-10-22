all: make_kaos


make_kaos: make_kernel make_boot make_video make_io make_lib
	ld -T link.ld -o bin/kernel.bin  src/kernel/*.o src/boot/*.o src/video/*.o src/io/*.o src/lib/*.o

make_kernel: src/kernel/start.s src/kernel/gdt.c src/kernel/gdt.s src/kernel/idt.c src/kernel/idt.s
	nasm -f aout -o src/kernel/sstart.o src/kernel/start.s
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/cgdt.o src/kernel/gdt.c
	nasm -f aout -o src/kernel/sgdt.o src/kernel/gdt.s
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/cidt.o src/kernel/idt.c
	nasm -f aout -o src/kernel/sidt.o src/kernel/idt.s
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/cisr.o src/kernel/isr.c
	nasm -f aout -o src/kernel/sisr.o src/kernel/isr.s

make_boot: src/boot/multiboot.c src/boot/boot.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/boot/cmultiboot.o src/boot/multiboot.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/boot/cboot.o src/boot/boot.c

make_video:
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/video/cvideo.o src/video/video.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/video/ctext.o src/video/text.c

make_io:
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/io/cio.o src/io/io.c

make_lib:
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/lib/cmemory.o src/lib/memory.c
