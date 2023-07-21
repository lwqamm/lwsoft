
.DATA; 定义数据段

.CODE

initCpu PROC
mov rax, rcx
mov r8, rdx
cpuid
mov[r8], rax
mov[r8 + 4], rbx
mov[r8 + 8], rcx
mov[r8 + 0ch],rdx
ret
initCpu ENDP

myProc1 PROC

mov rax,rsp
add rax,8
mov [rcx],rax
call r8
cmp rax,1
jne L5 
xor rax, rax
ret 
L5:mov qword ptr[rsp+8],rbx
jmp rdx
myProc1 ENDP



END

__asm {
		mov t_msg, esp
		add t_msg, 4
		CALL procmsg
		cmp eax, 1
		_emit 75h
		_emit 5
		xor eax, eax
		ret 14h
		mov edi, edi
		push ebp
		mov ebp, esp
		jmp g_peek
	}