global _start
_start:
    mov rax,25
    push rax
    push rax
    mov rax,25
    push rax
    push rax
    mov rax,60
    pop rdi
    syscall
