; test small prog without std C library

global _start:

%include "_m_scalls.inc"

extern main
section .text

_start:		mov ecx, [esp]			; mov argc	
		mov eax, esp			; free esp
		add eax, 4			; move to 1st arg in argv after prog_name
		push eax			; mov argv
		push ecx			; mov argc
		call main
		add esp, 8
		mov ecx, eax			; mov ret_code to regr
		_scall_exit ecx		
