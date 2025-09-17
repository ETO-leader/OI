section .data
    msg db "Hello, world!", 0xa  ; 字符串，最后是换行符
    len equ $ - msg

section .text
    global _start

_start:
    ; write(1, msg, len)
    mov rax, 1          ; sys_write 系统调用号
    mov rdi, 1          ; 文件描述符：stdout
    mov rsi, msg        ; 缓冲区地址
    mov rdx, len        ; 缓冲区长度
    syscall

    ; exit(0)
    mov rax, 60         ; sys_exit 系统调用号
    xor rdi, rdi        ; 返回码 0
    syscall
