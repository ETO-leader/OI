	.intel_syntax noprefix
	.text
	.globl	construct_vector_int
	.type	construct_vector_int, @function
construct_vector_int:
.LFB6:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	edi, 4
	call	malloc@PLT
	mov	QWORD PTR -16[rbp], rax
	mov	DWORD PTR -8[rbp], 1
	mov	DWORD PTR -4[rbp], 0
	mov	rax, QWORD PTR -16[rbp]
	mov	rdx, QWORD PTR -8[rbp]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	construct_vector_int, .-construct_vector_int
	.globl	emplace_back
	.type	emplace_back, @function
emplace_back:
.LFB7:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR -8[rbp], rdi
	mov	DWORD PTR -12[rbp], esi
	mov	rax, QWORD PTR -8[rbp]
	mov	eax, DWORD PTR 12[rax]
	lea	edx, 1[rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	DWORD PTR 12[rax], edx
	mov	rax, QWORD PTR -8[rbp]
	mov	edx, DWORD PTR 12[rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	eax, DWORD PTR 8[rax]
	cmp	edx, eax
	jle	.L4
	mov	rax, QWORD PTR -8[rbp]
	mov	eax, DWORD PTR 8[rax]
	cdqe
	lea	rdx, 0[0+rax*8]
	mov	rax, QWORD PTR -8[rbp]
	mov	rax, QWORD PTR [rax]
	mov	rsi, rdx
	mov	rdi, rax
	call	realloc@PLT
	mov	rdx, QWORD PTR -8[rbp]
	mov	QWORD PTR [rdx], rax
	mov	rax, QWORD PTR -8[rbp]
	mov	eax, DWORD PTR 8[rax]
	lea	edx, [rax+rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	DWORD PTR 8[rax], edx
.L4:
	mov	rax, QWORD PTR -8[rbp]
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	eax, DWORD PTR 12[rax]
	cdqe
	sal	rax, 2
	sub	rax, 4
	add	rdx, rax
	mov	eax, DWORD PTR -12[rbp]
	mov	DWORD PTR [rdx], eax
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	emplace_back, .-emplace_back
	.globl	vn
	.bss
	.align 32
	.type	vn, @object
	.size	vn, 240
vn:
	.zero	240
	.text
	.globl	initVN
	.type	initVN, @function
initVN:
.LFB8:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r12
	push	rbx
	sub	rsp, 16
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	mov	DWORD PTR -20[rbp], 0
.L6:
	mov	eax, DWORD PTR -20[rbp]
	cdqe
	sal	rax, 4
	mov	r12, rax
	lea	rbx, vn[rip]
	mov	eax, 0
	call	construct_vector_int
	mov	QWORD PTR [r12+rbx], rax
	mov	QWORD PTR 8[r12+rbx], rdx
	add	DWORD PTR -20[rbp], 1
	cmp	DWORD PTR -20[rbp], 14
	jg	.L8
	jmp	.L6
.L8:
	nop
	add	rsp, 16
	pop	rbx
	pop	r12
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	initVN, .-initVN
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%d\n"
.LC2:
	.string	"%d "
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 80
	mov	DWORD PTR -68[rbp], edi
	mov	QWORD PTR -80[rbp], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	eax, 0
	call	initVN
	lea	rax, -52[rbp]
	mov	rsi, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	mov	eax, 0
	call	construct_vector_int
	mov	QWORD PTR -32[rbp], rax
	mov	QWORD PTR -24[rbp], rdx
	mov	DWORD PTR -48[rbp], 0
.L10:
	mov	eax, DWORD PTR -48[rbp]
	mov	eax, eax
	mov	rdi, rax
	call	__popcountdi2@PLT
	mov	ecx, eax
	mov	eax, DWORD PTR -52[rbp]
	add	eax, 1
	mov	edx, eax
	shr	edx, 31
	add	eax, edx
	sar	eax
	cmp	ecx, eax
	jne	.L11
	mov	edx, DWORD PTR -48[rbp]
	lea	rax, -32[rbp]
	mov	esi, edx
	mov	rdi, rax
	call	emplace_back
.L11:
	add	DWORD PTR -48[rbp], 1
	mov	eax, DWORD PTR -52[rbp]
	mov	edx, 1
	mov	ecx, eax
	sal	edx, cl
	mov	eax, edx
	cmp	DWORD PTR -48[rbp], eax
	jge	.L12
	jmp	.L10
.L12:
	mov	eax, DWORD PTR -20[rbp]
	mov	DWORD PTR -36[rbp], eax
	mov	DWORD PTR -44[rbp], 0
.L13:
	mov	DWORD PTR -40[rbp], 0
.L14:
	mov	rax, QWORD PTR -32[rbp]
	mov	edx, DWORD PTR -44[rbp]
	movsx	rdx, edx
	sal	rdx, 2
	add	rax, rdx
	mov	edx, DWORD PTR [rax]
	mov	eax, DWORD PTR -40[rbp]
	mov	ecx, eax
	sar	edx, cl
	mov	eax, edx
	and	eax, 1
	test	eax, eax
	je	.L15
	mov	eax, DWORD PTR -40[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	lea	rax, vn[rip]
	add	rdx, rax
	mov	eax, DWORD PTR -44[rbp]
	mov	esi, eax
	mov	rdi, rdx
	call	emplace_back
.L15:
	add	DWORD PTR -40[rbp], 1
	mov	eax, DWORD PTR -52[rbp]
	cmp	DWORD PTR -40[rbp], eax
	jge	.L16
	jmp	.L14
.L16:
	add	DWORD PTR -44[rbp], 1
	mov	eax, DWORD PTR -44[rbp]
	cmp	eax, DWORD PTR -36[rbp]
	jge	.L17
	jmp	.L13
.L17:
	mov	eax, DWORD PTR -36[rbp]
	mov	esi, eax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	DWORD PTR -44[rbp], 0
.L18:
	mov	eax, DWORD PTR -44[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	lea	rax, vn[rip+12]
	mov	eax, DWORD PTR [rdx+rax]
	mov	esi, eax
	lea	rax, .LC2[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	DWORD PTR -40[rbp], 0
.L19:
	mov	eax, DWORD PTR -44[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	lea	rax, vn[rip]
	mov	rax, QWORD PTR [rdx+rax]
	mov	edx, DWORD PTR -40[rbp]
	movsx	rdx, edx
	sal	rdx, 2
	add	rax, rdx
	mov	eax, DWORD PTR [rax]
	add	eax, 1
	mov	esi, eax
	lea	rax, .LC2[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	add	DWORD PTR -40[rbp], 1
	mov	eax, DWORD PTR -44[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	lea	rax, vn[rip+12]
	mov	eax, DWORD PTR [rdx+rax]
	cmp	DWORD PTR -40[rbp], eax
	jge	.L20
	jmp	.L19
.L20:
	mov	edi, 10
	call	putchar@PLT
	add	DWORD PTR -44[rbp], 1
	mov	eax, DWORD PTR -52[rbp]
	cmp	DWORD PTR -44[rbp], eax
	jge	.L21
	jmp	.L18
.L21:
	mov	DWORD PTR -44[rbp], 0
.L22:
	mov	eax, DWORD PTR -52[rbp]
	add	eax, 1
	mov	edx, eax
	shr	edx, 31
	add	eax, edx
	sar	eax
	mov	esi, eax
	lea	rax, .LC2[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	DWORD PTR -40[rbp], 0
.L23:
	mov	rax, QWORD PTR -32[rbp]
	mov	edx, DWORD PTR -44[rbp]
	movsx	rdx, edx
	sal	rdx, 2
	add	rax, rdx
	mov	edx, DWORD PTR [rax]
	mov	eax, DWORD PTR -40[rbp]
	mov	ecx, eax
	sar	edx, cl
	mov	eax, edx
	and	eax, 1
	test	eax, eax
	je	.L24
	mov	eax, DWORD PTR -40[rbp]
	add	eax, 1
	mov	esi, eax
	lea	rax, .LC2[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
.L24:
	add	DWORD PTR -40[rbp], 1
	mov	eax, DWORD PTR -52[rbp]
	cmp	DWORD PTR -40[rbp], eax
	jge	.L25
	jmp	.L23
.L25:
	mov	edi, 10
	call	putchar@PLT
	add	DWORD PTR -44[rbp], 1
	mov	eax, DWORD PTR -44[rbp]
	cmp	eax, DWORD PTR -36[rbp]
	jge	.L28
	jmp	.L22
.L28:
	nop
	mov	rax, QWORD PTR -8[rbp]
	sub	rax, QWORD PTR fs:40
	je	.L27
	call	__stack_chk_fail@PLT
.L27:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.globl	__popcountdi2
	.ident	"GCC: (Ubuntu 14.2.0-19ubuntu2) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
