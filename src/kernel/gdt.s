global gdt_load
extern gdt_pointer


gdt_load:

;Load the GDT
	lgdt [gdt_pointer]

;Load the data segment
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

;Load the code segment (using far jump)
	jmp 0x08:gdt_load2


gdt_load2: ;Far jump leads here (but now with code segment loaded)
	ret
		
