; test func call macro (NASM)


%macro _fcall 1-*			; 1 and more params (variadic)
					; 1st arg - fnc pnt, args we use since sec arg
	%if %0 = 1			; if we have only one arg (func addr)
		jmp %%fncl		; jmp to call
	%endif
	%rep %0 - 1			; func ptr we shouldn`t push to stack
		%rotate -1		; reverse args for put 1st arg as 1ts
		push dword %1		; we use 32bits here, and push arg to stack
	%endrep
	%rotate -1
%%fncl:	call %1				; call func
	add esp, (%0-1)*4		; turn esp back to prev
%endmacro
