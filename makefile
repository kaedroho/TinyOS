all: make_kaos


make_kaos: make_kernel make_boot make_video make_io make_lib
	ld -T link.ld -o bin/kernel.bin  src/kernel/*.o src/boot/*.o src/video/*.o src/io/*.o src/lib/*.o

make_kernel: src/kernel/main.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/kernel/main.o src/kernel/main.c
	nasm -f aout -o src/kernel/start.o src/kernel/start.s

make_boot: src/boot/multiboot.c src/boot/boot.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/boot/multiboot.o src/boot/multiboot.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/boot/boot.o src/boot/boot.c

make_video:
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/video/video.o src/video/video.c
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/video/text.o src/video/text.c

make_io:
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/io/io.o src/io/io.c

make_lib:
	gcc -m32 -Wall -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iinclude -c -o src/lib/memory.o src/lib/memory.c
