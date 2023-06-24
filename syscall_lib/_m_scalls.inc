; syscalls macro realization (NASM)
; using -> %include "_m_scalls.inc"

; relized:
;	1) _exit - #1
;	2) read - #3
;	3) write - #4
;	4) open - #5
;	5) close - #6
;
; This is a basic (simple / naive) implementation of 
; Linux & FreeBSD syscalls like: open, close, read, write,
; and exit. Of course shouldn`t use it for app developing
; purposes only, like me, for educational purposes.
;
;  - EAX as syscall_no accumulator, if error occured EAX
;    will contain status code -1, successfull cases EAX
;    will contain bytes count or 0 (read), fd num in open.
;  - EBX as fd descriptor
;  - ECX as buffer address accumulator (read & write) and 
;    as open mode descriptor in open. If error occured, 
;    ECX will contain errcode, other case will be equal to 0.


%assign		SYSC_ERRC 0xfffff000		; syscall errcode i386
%assign		INV_FD 0xffffffff

%ifndef OS_LNX || OS_BSD
%error System not selected. Use -dOS_LNX | -dOS_BSD for OS choice.
%endif

%macro __scall_errc_scan 0			; using for errcode handling
						; we can destroy ECX (CDECL)
%ifdef OS_LNX
		mov ecx, eax			; eax contains syscall res code
		and ecx, SYSC_ERRC		; fetch errcode
		cmp ecx, SYSC_ERRC
		jne %%no_err
		mov ecx, eax			; if err, ecx`ll contain a syserrcode
		neg ecx				; inv ecx with 2 complement (as positive int)
		mov eax, ~00h			; -1 in eax
%%no_err:	xor ecx, ecx			; 0 in ecx if no err
%elifdef OS_BSD
		jc %%bsd_fail			; BSD use CF if syscall failed
		xor ecx, ecx
		jmp short %%done		; goto exit
%%bsd_fail:	mov ecx, eax			; move err code to ecx, then check it
		mov eax, ~00h			; move -1 to eax as fail status code
%%done:		
%endif
%endmacro

%macro __chk_fd_valid 1
		mov eax, %1			; we can use eax because we control it here
		cmp eax, INV_FD			; invalid fd always lower as zero
		jnz %%fd_valid
		mov eax, ~00h			; if fd invalid we put -1 into eax as st code
%%fd_valid:	xor eax, eax			; anyway eax was broken
%endmacro

%macro _scall_exit 1				; 1st param is exit-code 
%ifdef OS_LNX
		mov eax, 1			; syscall no
		mov ebx, %1			; status code for OS
		int 80h
%elifdef OS_BSD
		push dword %1			; we use status code as a param
		mov eax, 1
		push eax
		int 80h
		add esp, (%0+1)*4		; clear stack
%endif
%endmacro

%macro _scall_read 3
%ifdef OS_LNX
		mov eax, 3			; syscall no
		mov ebx, %1			; load fd for reading
		mov ecx, %2			; addr
		mov edx, %3			; len bytes
		int 80h
		test eax, eax			; check EOF
		jz %%done			;
		__scall_errc_scan		; syscall res handling
%%done:		xor ecx, ecx
%elifdef OS_BSD
		%rep %0
			%rotate -1
			push dword %1		; push args to stack reverse order
		%endrep
		mov eax, 3			; get syscall num in eax
		push eax
		int 80h
		test eax, eax			; check EOF
		jz %%bsd_done
		__scall_errc_scan		; check errors before resume stack
%%bsd_done:	add esp, (%0+1)*4		; clear stack
%endif
%endmacro

%macro _scall_write 3
%ifdef OS_LNX
		mov eax, 4			; syscall no
		mov ebx, %1
		mov ecx, %2			; addr
		mov edx, %3			; bytes cnt to write
		int 80h
		__scall_errc_scan
%elifdef OS_BSD
		%rep %0
			%rotate -1		; push args to stack reverse order
			push dword %1
		%endrep
		mov eax, 4			; mov to eax syscall num
		push eax			; mock procedure call
		int 80h
		__scall_errc_code		; check errors before resume stack
		add esp, (%0+1)*4
%endif
%endmacro

%macro _scall_open 2-3
%ifdef OS_LNX
		mov ebx, %1			; file path
		mov ecx, %2			; use mode
		mov eax, %0
		cmp eax, dword 3
		jnge %%scall
		mov edx, %3			; if we have file creation mode
%%scall:	mov eax, 5
		int 80h				; if success, fd will be in eax
		__scall_errc_scan
%elifdef OS_BSD
		%rep %0
			%rotate -1
			push dword %1		; push args to stack reverse order
		%endrep
		mov eax, 5
		push eax
		int 80h
		__scall_errc_scan
		add esp, (%0+1)*4
%endif
%endmacro

%macro _scall_close 1
%ifdef OS_LNX
		mov eax, 6
		mov ebx, %1			; fd to close
		int 80h
		__scall_errc_scan
%elifdef OS_BSD
		push dword %1
		mov eax, 6
		push eax
		int 80h
		__scall_errc_scan
		add esp, 8
%endif
%endmacro

%macro check_o_creat_f 2
		mov eax, %1			; mov oflag to regr
		and eax, %2			; it`s a O_CREAT value 
		cmp eax, %2			; set wished bits
		jz .o_creat_inst
		xor eax, eax
		jmp short .done_check
.o_creat_inst	mov eax, 1			; it`s most easy as bits shift with cl reg
.done_check	nop
%endmacro
