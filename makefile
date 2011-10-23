all: make_kaos


make_kaos: make_kernel make_boot make_video make_io make_lib
	ld -T link.ld -o bin/kernel.bin  src/kernel/*.o src/boot/*.o src/video/*.o src/io/*.o src/lib/*.o

make_kernel: src/kernel/start.s src/kernel/sys.c src/kernel/gdt.c src/kernel/gdt.s src/kernel/idt.c src/kernel/idt.s src/kernel/isr.c src/kernel/isr.s src/kernel/irq.c src/kernel/irq.s src/kernel/timer.c
	nasm -f aout -o src/kernel/sstart.o src/kernel/start.s
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/csys.o src/kernel/sys.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/cgdt.o src/kernel/gdt.c
	nasm -f aout -o src/kernel/sgdt.o src/kernel/gdt.s
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/cidt.o src/kernel/idt.c
	nasm -f aout -o src/kernel/sidt.o src/kernel/idt.s
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/cisr.o src/kernel/isr.c
	nasm -f aout -o src/kernel/sisr.o src/kernel/isr.s
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/cirq.o src/kernel/irq.c
	nasm -f aout -o src/kernel/sirq.o src/kernel/irq.s
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/ctimer.o src/kernel/timer.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/cpanic.o src/kernel/panic.c

make_boot: src/boot/boot.c src/boot/multiboot.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/boot/cboot.o src/boot/boot.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/boot/cmultiboot.o src/boot/multiboot.c

make_video: src/video/video.c src/video/text.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/video/cvideo.o src/video/video.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/video/ctext.o src/video/text.c

make_io: src/io/io.c src/io/kb.c src/io/mouse.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/io/cio.o src/io/io.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/io/ckb.o src/io/kb.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/io/cmouse.o src/io/mouse.c

make_lib: src/lib/memory.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/lib/cmemory.o src/lib/memory.c
