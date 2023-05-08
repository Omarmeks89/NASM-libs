; syscalls macro realization (NASM)
; using -> %include "_m_scalls.inc"

; relized:
;	1) _exit - #1
;	2) read - #3
;	3) write - #4
;	4) open - #5
;	5) close - #6


%assign		SYSC_ERRC 0xfffff000h		; syscall errcode i386
%assign		INV_FD 0xffffffffh		; eq to -1

%macro __scall_errc_scan 0			; using for errcode handling
						; we can destroy ECX (CDECL)
		mov ecx, eax			; eax contains syscall res code
		and ecx, SYSC_ERRC		; fetch errcode
		cmp ecx, SYSC_ERRC
		jne %%no_err
		mov ecx, eax			; if err, ecx`ll contain a syserrcode
		neg ecx				; inv ecx with 2 complement
		mov eax, ~00h			; -1 in eax
		%ifdef DEBUG
		%error syscall crash		; TODO refactor here...
		%endif
%%no_err:	xor ecx, ecx			; 0 in ecx if no err
%endmacro

%macro __chk_fd_valid 1
		mov eax, %1			; we can use eax because we control it here
		cmp eax, INV_FD
		jnz %%fd_valid
		mov eax, ~00h
		%ifdef DEBUG
		%error Invalid or closed fd for <read>
		%endif
%%fd_valid:	
%endmacro

%macro _scall_exit 1				; 1st param is exit-code 
		mov eax, 1			; syscall no
		mov ebx, %1			; status code for OS
		int 80h
%endmacro

%macro _scall_read 3
		mov eax, 3			; syscall no
		mov ebx, %1			; load fd for reading
		mov ecx, %2			; addr
		mov edx, %3			; len bytes
		int 80h
		test eax, eax			; check EOF
		jz %%done			;
		__scall_errc_scan		; syscall res handling
%%done:		
%endmacro

%macro _scall_write 3
		mov eax, 4			; syscall no
		mov ebx, %1
		mov ecx, %2			; addr
		mov edx, %3			; bytes cnt to write
		int 80h
		__scall_errc_scan
%endmacro

%macro _scall_open 3
%endmacro

%macro _scall_close 1
%endmacro
