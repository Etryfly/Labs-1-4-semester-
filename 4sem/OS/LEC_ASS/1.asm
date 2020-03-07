.386
.model flat, stdcall
ExitProcess PROTO, dwExitCode : DWORD

.data 

.code
main PROC

  
    mov  ah,9
    mov  dx,10Dh
    int 3

INVOKE ExitProcess, 0
main ENDP
END main