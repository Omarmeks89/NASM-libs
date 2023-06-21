; errcode will be always in ecx as declared in _m_scalls.inc
; base implementation of macro-decorators. 


%include "_m_scalls.inc"


global s_write
global s_exit
global s_read
global s_errno


section .text

s_write: 	push ebp
		mov ebp, esp
		push ebx						; we`ll destroy ebx
		_scall_write [ebp + 8], [ebp + 12], [ebp + 16]		; args will be in a frame	
		test ecx, ecx						; check errno in ecx
		jz .return
		mov [s_errno], ecx					; mov errno in s_errno
.return:	pop ebx
		mov esp, ebp
		pop ebp
		ret


s_exit:		push ebp						; base impl.
		mov ebp, esp
		_scall_exit [ebp + 8]
		mov esp, ebp
		pop ebp
		ret


s_read:		push ebp
		mov ebp, esp
		push ebx
		_scall_read [ebp + 8], [ebp + 12], [ebp + 16]
		test ecx, ecx
		jz .r_return						; later we`ll check eax and re-read
		mov [s_errno], ecx					; eax will contain readed bytes cnt or 0
.r_return:	pop ebx
		mov esp, ebp
		pop ebp
		ret


section .bss
s_errno		resd 1

