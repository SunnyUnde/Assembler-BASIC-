section .data
	message db "Hitherehowareu",10,0
;	arr db "101","sff"
	f dd 4
	x dw 1
section .bss
	total resd 2
	y resb 1
	z resw 2
	w resd 3
section .text
	mov ebx,ecx
	global main
ab:	add ecx,dword[eax+ebx*4]
main:	xor ebx,ebx ;;index
	xor ecx,ecx;total
	inc ebx
	jmp ab
	cmp ebx,4
	mov dword[message],65535	
	mov dword[message+ebx*5],15
	mov eax,dword[bx]
	mov ecx,ebx
	mov dword[total],eax
	push dword[total]
	push message
	jmp  message
	add ebx,8
