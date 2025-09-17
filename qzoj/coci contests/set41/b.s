	.file	"b.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.p2align 4
	.type	_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEENS0_5__ops15_Iter_less_iterEEvT_S9_T0_.isra.0, @function
_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEENS0_5__ops15_Iter_less_iterEEvT_S9_T0_.isra.0:
.LFB18707:
	.cfi_startproc
	cmpq	%rsi, %rdi
	je	.L14
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	4(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	cmpq	%rbp, %rsi
	jne	.L9
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L18:
	movq	%rbp, %rdx
	subq	%r12, %rdx
	movq	%rdx, %rdi
	salq	$62, %rdi
	subq	%rdx, %rdi
	leaq	4(%rbp,%rdi), %rdi
	cmpq	$4, %rdx
	jle	.L4
	movq	%r12, %rsi
	call	memmove@PLT
.L5:
	addq	$4, %rbp
	movl	%ebx, (%r12)
	cmpq	%rbp, %r13
	je	.L1
.L9:
	movl	0(%rbp), %ebx
	movl	(%r12), %ecx
	cmpl	%ecx, %ebx
	jl	.L18
	movl	-4(%rbp), %edx
	cmpl	%edx, %ebx
	jge	.L10
	leaq	-4(%rbp), %rax
	.p2align 5
	.p2align 4
	.p2align 3
.L8:
	movl	%edx, 4(%rax)
	movq	%rax, %rsi
	movl	-4(%rax), %edx
	subq	$4, %rax
	cmpl	%edx, %ebx
	jl	.L8
	movl	%ebx, (%rsi)
.L19:
	addq	$4, %rbp
	cmpq	%rbp, %r13
	jne	.L9
.L1:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L4:
	.cfi_restore_state
	jne	.L5
	movl	%ecx, (%rdi)
	jmp	.L5
.L10:
	movq	%rbp, %rsi
	movl	%ebx, (%rsi)
	jmp	.L19
.L14:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	ret
	.cfi_endproc
.LFE18707:
	.size	_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEENS0_5__ops15_Iter_less_iterEEvT_S9_T0_.isra.0, .-_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEENS0_5__ops15_Iter_less_iterEEvT_S9_T0_.isra.0
	.p2align 4
	.type	_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEElNS0_5__ops15_Iter_less_iterEEvT_S9_T0_T1_.isra.0, @function
_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEElNS0_5__ops15_Iter_less_iterEEvT_S9_T0_T1_.isra.0:
.LFB18709:
	.cfi_startproc
	movq	%rsi, %r9
	subq	%rdi, %r9
	cmpq	$64, %r9
	jle	.L87
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%r9, %r10
	movq	%rsi, %r8
	sarq	$3, %r9
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	sarq	$2, %r10
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	testq	%r12, %r12
	je	.L88
.L22:
	movq	0(%rbp), %xmm0
	movl	-4(%r8), %edi
	subq	$1, %r12
	leaq	4(%rbp), %r14
	leaq	0(%rbp,%r9,4), %r9
	movl	(%r9), %esi
	pshufd	$0xe5, %xmm0, %xmm1
	movd	%xmm1, %edx
	movd	%xmm0, %ecx
	cmpl	%esi, %edx
	jge	.L51
	cmpl	%edi, %esi
	jl	.L56
	cmpl	%edi, %edx
	jl	.L86
.L54:
	pshufd	$225, %xmm0, %xmm2
	movq	%xmm2, 0(%rbp)
.L53:
	movq	%r8, %r10
	cmpl	%ecx, %edx
	jle	.L72
	.p2align 4
	.p2align 3
.L90:
	addq	$4, %r14
	.p2align 4
	.p2align 4
	.p2align 3
.L58:
	movq	%r14, %r11
	movl	(%r14), %ecx
	addq	$4, %r14
	cmpl	%edx, %ecx
	jl	.L58
	movl	-4(%r10), %r13d
	movq	%r11, %rbx
	cmpl	%edx, %r13d
	jle	.L59
.L91:
	leaq	-8(%r10), %rax
	.p2align 4
	.p2align 4
	.p2align 3
.L60:
	movq	%rax, %r10
	movl	(%rax), %r13d
	subq	$4, %rax
	cmpl	%edx, %r13d
	jg	.L60
	cmpq	%r10, %rbx
	jnb	.L89
.L62:
	movl	%r13d, (%rbx)
	leaq	4(%rbx), %r14
	movl	%ecx, (%r10)
	movl	0(%rbp), %edx
	movl	4(%rbx), %ecx
	cmpl	%ecx, %edx
	jg	.L90
.L72:
	movl	-4(%r10), %r13d
	movq	%r14, %rbx
	cmpl	%edx, %r13d
	jg	.L91
	.p2align 4
	.p2align 3
.L59:
	subq	$4, %r10
	cmpq	%r10, %rbx
	jb	.L62
	.p2align 4
	.p2align 3
.L89:
	movq	%r12, %rdx
	movq	%r8, %rsi
	movq	%rbx, %rdi
	call	_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEElNS0_5__ops15_Iter_less_iterEEvT_S9_T0_T1_.isra.0
	movq	%rbx, %r9
	subq	%rbp, %r9
	cmpq	$64, %r9
	jle	.L20
	movq	%r9, %r10
	movq	%rbx, %r8
	sarq	$3, %r9
	sarq	$2, %r10
	testq	%r12, %r12
	jne	.L22
.L88:
	leaq	-1(%r10), %rdi
	leaq	-1(%r9), %rcx
	sarq	%rdi
	leaq	-4(%rbp,%r9,4), %r9
	movq	%rcx, %r11
	movl	(%r9), %esi
	movq	%r9, %r12
	cmpq	%rdi, %rcx
	jge	.L23
.L94:
	movq	%rcx, %r13
	jmp	.L25
	.p2align 6
	.p2align 4,,10
	.p2align 3
.L66:
	movq	%rax, %r13
.L25:
	leaq	1(%r13), %rbx
	leaq	(%rbx,%rbx), %rax
	leaq	0(%rbp,%rbx,8), %r12
	leaq	-1(%rax), %r14
	movl	(%r12), %edx
	leaq	0(%rbp,%r14,4), %r15
	movl	(%r15), %ebx
	cmpl	%edx, %ebx
	cmovle	%edx, %ebx
	cmovg	%r14, %rax
	cmovg	%r15, %r12
	movl	%ebx, 0(%rbp,%r13,4)
	cmpq	%rax, %rdi
	jg	.L66
	testb	$1, %r10b
	jne	.L82
	cmpq	%rax, %r11
	je	.L28
.L82:
	leaq	-1(%rax), %rbx
.L27:
	sarq	%rbx
	cmpq	%rax, %rcx
	jl	.L31
	jmp	.L29
	.p2align 6
	.p2align 4,,10
	.p2align 3
.L93:
	leaq	-1(%rbx), %rax
	movl	%r15d, (%r14)
	shrq	$63, %rax
	leaq	-1(%rax,%rbx), %rdx
	movq	%rbx, %rax
	cmpq	%rbx, %rcx
	jge	.L92
	movq	%rdx, %rbx
	sarq	%rbx
.L31:
	leaq	0(%rbp,%rbx,4), %r12
	leaq	0(%rbp,%rax,4), %r14
	movl	(%r12), %r15d
	cmpl	%r15d, %esi
	jg	.L93
	movl	%esi, (%r14)
	testq	%rcx, %rcx
	je	.L33
.L32:
	subq	$4, %r9
	subq	$1, %rcx
	movl	(%r9), %esi
	movq	%r9, %r12
	cmpq	%rdi, %rcx
	jl	.L94
.L23:
	testb	$1, %r10b
	jne	.L29
	cmpq	%r11, %rcx
	je	.L95
.L29:
	movl	%esi, (%r12)
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L51:
	cmpl	%edi, %edx
	jl	.L54
	cmpl	%edi, %esi
	jge	.L56
.L86:
	movl	%edi, 0(%rbp)
	movl	%ecx, -4(%r8)
	movl	4(%rbp), %ecx
	movl	0(%rbp), %edx
	jmp	.L53
.L56:
	movl	%esi, 0(%rbp)
	movl	%ecx, (%r9)
	movl	4(%rbp), %ecx
	movl	0(%rbp), %edx
	jmp	.L53
.L20:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L92:
	.cfi_restore_state
	movq	%r12, %r14
	movl	%esi, (%r14)
	testq	%rcx, %rcx
	jne	.L32
.L33:
	movq	%r8, %rsi
	leaq	-4(%r8), %rdi
	subq	%rbp, %rsi
	cmpq	$4, %rsi
	jle	.L20
	.p2align 4
	.p2align 3
.L50:
	movl	0(%rbp), %r8d
	movl	(%rdi), %esi
	movl	%r8d, (%rdi)
	movq	%rdi, %r8
	subq	%rbp, %r8
	movq	%r8, %r12
	sarq	$2, %r12
	cmpq	$8, %r8
	jle	.L37
	leaq	-1(%r12), %rbx
	xorl	%r11d, %r11d
	sarq	%rbx
	jmp	.L39
	.p2align 6
	.p2align 4,,10
	.p2align 3
.L69:
	movq	%rax, %r11
.L39:
	leaq	1(%r11), %r9
	leaq	(%r9,%r9), %rcx
	leaq	0(%rbp,%r9,8), %r15
	leaq	-1(%rcx), %rax
	movl	(%r15), %r13d
	leaq	0(%rbp,%rax,4), %r10
	movl	(%r10), %edx
	cmpl	%r13d, %edx
	cmovle	%r13d, %edx
	cmovle	%rcx, %rax
	cmovle	%r15, %r10
	movl	%edx, 0(%rbp,%r11,4)
	cmpq	%rax, %rbx
	jg	.L69
	andl	$1, %r12d
	jne	.L84
	movq	%r8, %r11
	sarq	$3, %r11
	subq	$1, %r11
	cmpq	%rax, %r11
	je	.L45
.L84:
	leaq	-1(%rax), %rbx
	shrq	$63, %rbx
	leaq	-1(%rax,%rbx), %r13
	sarq	%r13
	testq	%rax, %rax
	jne	.L48
	jmp	.L96
	.p2align 6
	.p2align 4,,10
	.p2align 3
.L98:
	leaq	-1(%r13), %rax
	movl	%r9d, (%r15)
	shrq	$63, %rax
	leaq	-1(%rax,%r13), %rcx
	movq	%r13, %rax
	testq	%r13, %r13
	je	.L97
	sarq	%rcx
	movq	%rcx, %r13
.L48:
	leaq	0(%rbp,%r13,4), %r10
	leaq	0(%rbp,%rax,4), %r15
	movl	(%r10), %r9d
	cmpl	%r9d, %esi
	jg	.L98
.L42:
	movl	%esi, (%r15)
	cmpq	$4, %r8
	jle	.L20
.L83:
	subq	$4, %rdi
	jmp	.L50
.L97:
	movq	%r10, %r15
	jmp	.L42
.L37:
	andl	$1, %r12d
	jne	.L85
	cmpq	$8, %r8
	jne	.L85
	movq	%rbp, %r10
	xorl	%eax, %eax
.L45:
	leaq	1(%rax,%rax), %r12
	movq	%rax, %r13
	movl	0(%rbp,%r12,4), %r14d
	movq	%r12, %rax
	movl	%r14d, (%r10)
	jmp	.L48
.L85:
	movq	%rbp, %r15
	jmp	.L42
.L95:
	movq	%rcx, %rax
.L28:
	leaq	(%rax,%rax), %rbx
	leaq	1(%rbx), %rax
	leaq	0(%rbp,%rax,4), %r14
	movl	(%r14), %r13d
	movl	%r13d, (%r12)
	movq	%r14, %r12
	jmp	.L27
.L87:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	ret
.L96:
	.cfi_def_cfa_offset 64
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movl	%esi, (%r10)
	jmp	.L83
	.cfi_endproc
.LFE18709:
	.size	_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEElNS0_5__ops15_Iter_less_iterEEvT_S9_T0_T1_.isra.0, .-_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEElNS0_5__ops15_Iter_less_iterEEvT_S9_T0_T1_.isra.0
	.section	.rodata._ZNSt6vectorIiSaIiEEC2EmRKS0_.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"cannot create std::vector larger than max_size()"
	.section	.text._ZNSt6vectorIiSaIiEEC2EmRKS0_,"axG",@progbits,_ZNSt6vectorIiSaIiEEC5EmRKS0_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIiSaIiEEC2EmRKS0_
	.type	_ZNSt6vectorIiSaIiEEC2EmRKS0_, @function
_ZNSt6vectorIiSaIiEEC2EmRKS0_:
.LFB15930:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rsi, %rax
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	shrq	$61, %rax
	jne	.L107
	movq	%rdi, %rbx
	testq	%rsi, %rsi
	je	.L108
	leaq	0(,%rsi,4), %rdx
	movq	%rsi, 8(%rsp)
	movq	%rdx, %rdi
	movq	%rdx, (%rsp)
	call	_Znwm@PLT
	movq	(%rsp), %rdx
	movq	%rax, (%rbx)
	leaq	4(%rax), %rdi
	leaq	(%rax,%rdx), %r9
	andl	$0, (%rax)
	movq	%r9, 16(%rbx)
	cmpq	$1, 8(%rsp)
	je	.L102
	subq	$4, %rdx
	xorl	%esi, %esi
	movq	%rax, (%rsp)
	movq	%r9, 8(%rsp)
	call	memset@PLT
	movq	8(%rsp), %rcx
	leaq	-4(%rcx,%rax), %rdi
	subq	(%rsp), %rdi
.L102:
	movq	%rdi, 8(%rbx)
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L108:
	.cfi_restore_state
	movq	$0, (%rdi)
	movq	$0, 16(%rdi)
	xorl	%edi, %edi
	movq	%rdi, 8(%rbx)
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L107:
	.cfi_restore_state
	leaq	.LC0(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE15930:
	.size	_ZNSt6vectorIiSaIiEEC2EmRKS0_, .-_ZNSt6vectorIiSaIiEEC2EmRKS0_
	.weak	_ZNSt6vectorIiSaIiEEC1EmRKS0_
	.set	_ZNSt6vectorIiSaIiEEC1EmRKS0_,_ZNSt6vectorIiSaIiEEC2EmRKS0_
	.section	.text._ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED2Ev,"axG",@progbits,_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED2Ev
	.type	_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED2Ev, @function
_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED2Ev:
.LFB15957:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	8(%rdi), %rbp
	movq	(%rdi), %rbx
	cmpq	%rbx, %rbp
	je	.L110
	.p2align 4
	.p2align 3
.L114:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L111
	movq	16(%rbx), %rsi
	addq	$24, %rbx
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
	cmpq	%rbx, %rbp
	jne	.L114
.L113:
	movq	(%r12), %rbx
.L110:
	testq	%rbx, %rbx
	je	.L109
	movq	16(%r12), %rsi
	movq	%rbx, %rdi
	subq	%rbx, %rsi
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L111:
	.cfi_restore_state
	addq	$24, %rbx
	cmpq	%rbx, %rbp
	jne	.L114
	jmp	.L113
	.p2align 4,,10
	.p2align 3
.L109:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE15957:
	.size	_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED2Ev, .-_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED2Ev
	.weak	_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED1Ev
	.set	_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED1Ev,_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED2Ev
	.section	.text._ZN3dsu7findsetIiEEiT_,"axG",@progbits,_ZN3dsu7findsetIiEEiT_,comdat
	.align 2
	.p2align 4
	.weak	_ZN3dsu7findsetIiEEiT_
	.type	_ZN3dsu7findsetIiEEiT_, @function
_ZN3dsu7findsetIiEEiT_:
.LFB15972:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rcx
	movslq	%esi, %rdx
	movq	%rdx, %rax
	leaq	(%rcx,%rdx,4), %r8
	movl	(%r8), %esi
	cmpl	%edx, %esi
	jne	.L129
	ret
	.p2align 4,,10
	.p2align 3
.L129:
	movslq	%esi, %rax
	leaq	(%rcx,%rax,4), %r9
	movl	(%r9), %eax
	cmpl	%eax, %esi
	je	.L124
	movslq	%eax, %r10
	leaq	(%rcx,%r10,4), %r11
	movl	(%r11), %edx
	cmpl	%edx, %eax
	jne	.L130
.L125:
	movl	%edx, (%r9)
	movl	%edx, %eax
.L124:
	movl	%eax, (%r8)
	ret
	.p2align 4,,10
	.p2align 3
.L130:
	movslq	%edx, %rsi
	leaq	(%rcx,%rsi,4), %rcx
	movl	(%rcx), %esi
	cmpl	%esi, %edx
	je	.L126
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%r9, 8(%rsp)
	movq	%r8, (%rsp)
	movq	%r11, 16(%rsp)
	movq	%rcx, 24(%rsp)
	call	_ZN3dsu7findsetIiEEiT_
	movq	24(%rsp), %rdi
	movq	8(%rsp), %r9
	movl	%eax, %edx
	movq	(%rsp), %r8
	movl	%eax, (%rdi)
	movq	16(%rsp), %rax
	movl	%edx, (%rax)
	movl	%edx, %eax
	movl	%edx, (%r9)
	movl	%edx, (%r8)
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L126:
	movl	%esi, (%r11)
	movl	%esi, %edx
	jmp	.L125
	.cfi_endproc
.LFE15972:
	.size	_ZN3dsu7findsetIiEEiT_, .-_ZN3dsu7findsetIiEEiT_
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"vector::_M_realloc_append"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB5:
	.section	.text.startup,"ax",@progbits
.LHOTB5:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB14955:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA14955
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$264, %rsp
	.cfi_def_cfa_offset 320
	movq	%fs:40, %rdi
	movq	%rdi, 248(%rsp)
	xorl	%edi, %edi
.LEHB0:
	call	_ZNSt8ios_base15sync_with_stdioEb@PLT
	leaq	156(%rsp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	movq	$0, 232+_ZSt3cin(%rip)
	call	_ZNSirsERi@PLT
	movslq	156(%rsp), %rsi
	leaq	224(%rsp), %rdx
	leaq	160(%rsp), %rdi
	movq	$0, 168(%rsp)
	movq	$0, 176(%rsp)
	movq	%rdx, 104(%rsp)
	call	_ZNSt6vectorIiSaIiEEC1EmRKS0_
.LEHE0:
	movq	176(%rsp), %rax
	movq	160(%rsp), %rsi
	movq	168(%rsp), %rbx
	movq	%rax, 112(%rsp)
	movq	%rsi, 8(%rsp)
	cmpq	%rsi, %rbx
	je	.L250
	movq	%rbx, %rcx
	movq	%rsi, %rbp
	subq	%rsi, %rcx
	leaq	-4(%rcx), %rdi
	shrq	$2, %rdi
	addq	$1, %rdi
	andl	$7, %edi
	je	.L133
	cmpq	$1, %rdi
	je	.L454
	cmpq	$2, %rdi
	je	.L455
	cmpq	$3, %rdi
	je	.L456
	cmpq	$4, %rdi
	je	.L457
	cmpq	$5, %rdi
	je	.L458
	cmpq	$6, %rdi
	jne	.L599
.L459:
	movq	%rbp, %rsi
	leaq	_ZSt3cin(%rip), %rdi
.LEHB1:
	call	_ZNSirsERi@PLT
	addq	$4, %rbp
.L458:
	movq	%rbp, %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	addq	$4, %rbp
.L457:
	movq	%rbp, %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	addq	$4, %rbp
.L456:
	movq	%rbp, %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	addq	$4, %rbp
.L455:
	movq	%rbp, %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	addq	$4, %rbp
.L454:
	movq	%rbp, %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	addq	$4, %rbp
	cmpq	%rbp, %rbx
	je	.L577
.L133:
	movq	%rbp, %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	addq	$4, %rbp
	leaq	_ZSt3cin(%rip), %rdi
	movq	%rbp, %rsi
	call	_ZNSirsERi@PLT
	leaq	4(%rbp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	leaq	8(%rbp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	leaq	12(%rbp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	leaq	16(%rbp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	leaq	20(%rbp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	leaq	24(%rbp), %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
	addq	$28, %rbp
	cmpq	%rbp, %rbx
	jne	.L133
.L577:
	movq	8(%rsp), %r13
	movq	%rbx, %r12
	movl	$64, %r10d
	movq	%rbx, %rsi
	movl	$63, %r11d
	subq	%r13, %r12
	movq	%r13, %rdi
	movq	%r12, %r8
	sarq	$2, %r8
	bsrq	%r8, %r9
	xorq	$63, %r9
	testq	%r8, %r8
	cmovne	%r9d, %r10d
	subl	%r10d, %r11d
	movslq	%r11d, %rdx
	addq	%rdx, %rdx
	call	_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEElNS0_5__ops15_Iter_less_iterEEvT_S9_T0_T1_.isra.0
	cmpq	$64, %r12
	jg	.L600
	movq	8(%rsp), %rdi
	movq	%rbx, %rsi
	call	_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEENS0_5__ops15_Iter_less_iterEEvT_S9_T0_.isra.0
.L137:
	movq	8(%rsp), %r14
	movq	%rbx, %rbp
	subq	%r14, %rbp
	movq	%r14, %r12
	subq	$4, %rbp
	shrq	$2, %rbp
	andl	$7, %ebp
	je	.L141
	movl	4(%r14), %edi
	movq	%r14, %r9
	leaq	4(%r14), %r12
	cmpl	%edi, (%r14)
	je	.L142
	cmpq	$1, %rbp
	je	.L141
	cmpq	$2, %rbp
	je	.L490
	cmpq	$3, %rbp
	je	.L491
	cmpq	$4, %rbp
	je	.L492
	cmpq	$5, %rbp
	je	.L493
	cmpq	$6, %rbp
	je	.L494
	movq	%r12, %r9
	leaq	8(%r14), %r12
	movl	8(%r14), %r13d
	cmpl	%r13d, -4(%r12)
	je	.L142
.L494:
	movl	4(%r12), %r8d
	movq	%r12, %r9
	addq	$4, %r12
	cmpl	%r8d, -4(%r12)
	je	.L142
.L493:
	movl	4(%r12), %r10d
	movq	%r12, %r9
	addq	$4, %r12
	cmpl	%r10d, -4(%r12)
	je	.L142
.L492:
	movl	4(%r12), %r11d
	movq	%r12, %r9
	addq	$4, %r12
	cmpl	%r11d, -4(%r12)
	je	.L142
.L491:
	movl	4(%r12), %r15d
	movq	%r12, %r9
	addq	$4, %r12
	cmpl	%r15d, -4(%r12)
	je	.L142
.L490:
	movq	%r12, %r9
	addq	$4, %r12
	movl	(%r12), %ecx
	cmpl	%ecx, -4(%r12)
	je	.L142
.L141:
	leaq	4(%r12), %rsi
	movq	%r12, %r9
	cmpq	%rsi, %rbx
	je	.L601
	movl	4(%r12), %eax
	cmpl	%eax, -4(%rsi)
	je	.L142
	movl	8(%r12), %edx
	movq	%rsi, %r9
	cmpl	%edx, 4(%r12)
	je	.L142
	movl	12(%r12), %r14d
	leaq	8(%r12), %r9
	cmpl	%r14d, 8(%r12)
	je	.L142
	movl	16(%r12), %ebp
	leaq	12(%r12), %r9
	cmpl	%ebp, 12(%r12)
	je	.L142
	movl	20(%r12), %edi
	leaq	16(%r12), %r9
	cmpl	%edi, 16(%r12)
	je	.L142
	movl	24(%r12), %r13d
	leaq	20(%r12), %r9
	cmpl	%r13d, 20(%r12)
	je	.L142
	movl	28(%r12), %r8d
	leaq	24(%r12), %r9
	cmpl	%r8d, 24(%r12)
	je	.L142
	leaq	28(%r12), %r9
	addq	$32, %r12
	movl	(%r12), %r10d
	cmpl	%r10d, -4(%r12)
	jne	.L141
.L142:
	cmpq	%r9, %rbx
	je	.L151
	leaq	8(%r9), %r12
	cmpq	%r12, %rbx
	je	.L147
	movl	(%r9), %edx
.L150:
	movl	(%r12), %r11d
	cmpl	%edx, %r11d
	je	.L148
.L602:
	addq	$4, %r12
	movl	%r11d, 4(%r9)
	addq	$4, %r9
	cmpq	%r12, %rbx
	je	.L147
	movl	%r11d, %edx
	movl	(%r12), %r11d
	cmpl	%edx, %r11d
	jne	.L602
.L148:
	addq	$4, %r12
	cmpq	%r12, %rbx
	jne	.L150
.L147:
	addq	$4, %r9
.L151:
	movq	8(%rsp), %rbx
	movq	%rbx, %r14
	cmpq	%r9, %rbx
	je	.L132
	leaq	4(%rbx), %rax
	cmpq	%rax, %r9
	je	.L132
	movq	%r9, %r15
	movl	(%rbx), %edx
	subq	%rax, %r15
	subq	$4, %r15
	shrq	$2, %r15
	addq	$1, %r15
	andl	$7, %r15d
	je	.L153
	cmpq	$1, %r15
	je	.L460
	cmpq	$2, %r15
	je	.L461
	cmpq	$3, %r15
	je	.L462
	cmpq	$4, %r15
	je	.L463
	cmpq	$5, %r15
	je	.L464
	cmpq	$6, %r15
	je	.L465
	movl	(%rax), %ecx
	movq	8(%rsp), %rsi
	cmpl	%edx, %ecx
	cmovle	%rsi, %rax
	cmovg	%ecx, %edx
	movq	%rax, %r14
	leaq	8(%rsi), %rax
.L465:
	movl	(%rax), %ebp
	cmpl	%edx, %ebp
	cmovg	%ebp, %edx
	cmovg	%rax, %r14
	addq	$4, %rax
.L464:
	movl	(%rax), %edi
	cmpl	%edx, %edi
	cmovg	%edi, %edx
	cmovg	%rax, %r14
	addq	$4, %rax
.L463:
	movl	(%rax), %r13d
	cmpl	%edx, %r13d
	cmovg	%r13d, %edx
	cmovg	%rax, %r14
	addq	$4, %rax
.L462:
	movl	(%rax), %r8d
	cmpl	%edx, %r8d
	cmovg	%r8d, %edx
	cmovg	%rax, %r14
	addq	$4, %rax
.L461:
	movl	(%rax), %r10d
	cmpl	%edx, %r10d
	cmovg	%r10d, %edx
	cmovg	%rax, %r14
	addq	$4, %rax
.L460:
	movl	(%rax), %r12d
	cmpl	%edx, %r12d
	cmovg	%r12d, %edx
	cmovg	%rax, %r14
	addq	$4, %rax
	cmpq	%r9, %rax
	je	.L132
.L153:
	movl	(%rax), %r11d
	movl	8(%rax), %ecx
	leaq	4(%rax), %rbx
	leaq	12(%rax), %rsi
	movl	12(%rax), %ebp
	movl	16(%rax), %r13d
	leaq	16(%rax), %rdi
	leaq	20(%rax), %r8
	cmpl	%edx, %r11d
	movl	20(%rax), %r10d
	cmovle	%edx, %r11d
	movl	4(%rax), %edx
	cmovg	%rax, %r14
	cmpl	%r11d, %edx
	cmovle	%r11d, %edx
	cmovg	%rbx, %r14
	movl	24(%rax), %ebx
	leaq	24(%rax), %r11
	cmpl	%edx, %ecx
	movq	%r14, %r15
	leaq	8(%rax), %r14
	cmovle	%edx, %ecx
	cmovle	%r15, %r14
	movl	28(%rax), %edx
	cmpl	%ecx, %ebp
	cmovle	%ecx, %ebp
	cmovle	%r14, %rsi
	leaq	28(%rax), %r14
	cmpl	%ebp, %r13d
	cmovle	%ebp, %r13d
	cmovle	%rsi, %rdi
	cmpl	%r13d, %r10d
	movq	%rdi, %r12
	cmovle	%r13d, %r10d
	cmovg	%r8, %r12
	cmpl	%r10d, %ebx
	cmovle	%r10d, %ebx
	cmovle	%r12, %r11
	cmpl	%ebx, %edx
	cmovle	%ebx, %edx
	cmovle	%r11, %r14
	addq	$32, %rax
	cmpq	%r9, %rax
	jne	.L153
.L132:
	movl	(%r14), %ecx
	leal	2(%rcx), %eax
	cltq
	movq	%rax, 96(%rsp)
	shrq	$61, %rax
	jne	.L560
	movq	96(%rsp), %r15
	testq	%r15, %r15
	je	.L156
	leaq	0(,%r15,4), %rbp
	movq	%r9, 24(%rsp)
	movq	%rbp, %rdi
	movl	%ecx, 16(%rsp)
	movq	%rbp, 96(%rsp)
	call	_Znwm@PLT
.LEHE1:
	movq	%rbp, %rdx
	movl	$255, %esi
	movq	%rax, %rdi
	movq	%rax, %r13
	call	memset@PLT
	movq	24(%rsp), %r9
	movl	16(%rsp), %ecx
	movq	%r9, %r14
	subq	8(%rsp), %r14
	sarq	$2, %r14
	testl	%r14d, %r14d
	movl	%r14d, 120(%rsp)
	jle	.L603
.L157:
	leal	-1(%r14), %r12d
	movq	8(%rsp), %r14
	xorl	%r8d, %r8d
	movl	$-1, %r11d
	.p2align 4
	.p2align 3
.L161:
	movslq	(%r14,%r8,4), %rdi
	leal	1(%r11), %eax
	cltq
	leaq	4(,%rdi,4), %r10
	salq	$2, %rax
	movq	%rdi, %r11
	cmpq	%rax, %r10
	je	.L166
	movq	%r10, %r15
	movl	%r8d, %ebx
	leaq	0(%r13,%rax), %rdi
	subq	%rax, %r15
	subq	$4, %r15
	cmpq	$8, %r15
	jbe	.L163
	shrq	$2, %r15
	movd	%r8d, %xmm2
	movq	%rdi, %rsi
	addq	$1, %r15
	pshufd	$0, %xmm2, %xmm0
	movq	%r15, %rdx
	shrq	$2, %rdx
	salq	$4, %rdx
	leaq	(%rdx,%rdi), %rbp
	subq	$16, %rdx
	shrq	$4, %rdx
	addq	$1, %rdx
	andl	$7, %edx
	je	.L164
	cmpq	$1, %rdx
	je	.L466
	cmpq	$2, %rdx
	je	.L467
	cmpq	$3, %rdx
	je	.L468
	cmpq	$4, %rdx
	je	.L469
	cmpq	$5, %rdx
	je	.L470
	cmpq	$6, %rdx
	je	.L471
	movups	%xmm0, (%rdi)
	leaq	16(%rdi), %rsi
.L471:
	movups	%xmm0, (%rsi)
	addq	$16, %rsi
.L470:
	movups	%xmm0, (%rsi)
	addq	$16, %rsi
.L469:
	movups	%xmm0, (%rsi)
	addq	$16, %rsi
.L468:
	movups	%xmm0, (%rsi)
	addq	$16, %rsi
.L467:
	movups	%xmm0, (%rsi)
	addq	$16, %rsi
.L466:
	movups	%xmm0, (%rsi)
	addq	$16, %rsi
	cmpq	%rbp, %rsi
	je	.L576
.L164:
	movups	%xmm0, (%rsi)
	subq	$-128, %rsi
	movups	%xmm0, -112(%rsi)
	movups	%xmm0, -96(%rsi)
	movups	%xmm0, -80(%rsi)
	movups	%xmm0, -64(%rsi)
	movups	%xmm0, -48(%rsi)
	movups	%xmm0, -32(%rsi)
	movups	%xmm0, -16(%rsi)
	cmpq	%rbp, %rsi
	jne	.L164
.L576:
	testb	$3, %r15b
	je	.L166
	andq	$-4, %r15
	leaq	(%rdi,%r15,4), %rdi
.L163:
	addq	%r13, %r10
	leaq	4(%rdi), %rax
	movl	%ebx, (%rdi)
	cmpq	%rax, %r10
	je	.L166
	leaq	8(%rdi), %r15
	movl	%ebx, 4(%rdi)
	cmpq	%r15, %r10
	je	.L166
	movl	%ebx, 8(%rdi)
.L166:
	cmpq	%r12, %r8
	je	.L162
	addq	$1, %r8
	jmp	.L161
.L600:
	leaq	64(%r13), %r15
	movq	%r13, %rdi
	movq	%r15, %rsi
	call	_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEENS0_5__ops15_Iter_less_iterEEvT_S9_T0_.isra.0
	cmpq	%r15, %rbx
	je	.L137
	movl	(%r15), %ecx
	movl	-4(%r15), %edx
	cmpl	%edx, %ecx
	jge	.L252
	.p2align 4
	.p2align 3
.L604:
	leaq	-4(%r15), %rax
	.p2align 5
	.p2align 4
	.p2align 3
.L139:
	movl	%edx, 4(%rax)
	movq	%rax, %rsi
	movl	-4(%rax), %edx
	subq	$4, %rax
	cmpl	%edx, %ecx
	jl	.L139
.L138:
	addq	$4, %r15
	movl	%ecx, (%rsi)
	cmpq	%r15, %rbx
	je	.L137
	movl	(%r15), %ecx
	movl	-4(%r15), %edx
	cmpl	%edx, %ecx
	jl	.L604
.L252:
	movq	%r15, %rsi
	jmp	.L138
.L156:
	movq	%r9, %r14
	subq	8(%rsp), %r14
	xorl	%r13d, %r13d
	sarq	$2, %r14
	movl	%r14d, 120(%rsp)
	testl	%r14d, %r14d
	jg	.L157
	.p2align 4
	.p2align 3
.L162:
	movabsq	$384307168202282325, %r14
	leal	1(%rcx), %r8d
	movslq	%r8d, %r12
	cmpq	%r12, %r14
	jb	.L605
.L158:
	testq	%r12, %r12
	je	.L606
	imulq	$24, %r12, %rbx
	movq	%r9, 32(%rsp)
	movl	%ecx, 24(%rsp)
	movq	%rbx, %rdi
.LEHB2:
	call	_Znwm@PLT
.LEHE2:
	movl	24(%rsp), %ecx
	leaq	(%rax,%rbx), %rdx
	movq	%rax, 16(%rsp)
	movq	%rax, %r10
	movq	%rax, 192(%rsp)
	movq	32(%rsp), %r9
	testl	%ecx, %ecx
	movq	%rdx, 208(%rsp)
	je	.L259
	movq	%r12, %rsi
	pxor	%xmm1, %xmm1
	movabsq	$768614336404564651, %r15
	shrq	%rsi
	imulq	$48, %rsi, %rdi
	addq	%rdi, %r10
	subq	$48, %rdi
	shrq	$4, %rdi
	imulq	%r15, %rdi
	addq	$1, %rdi
	andl	$7, %edi
	je	.L172
	cmpq	$1, %rdi
	je	.L472
	cmpq	$2, %rdi
	je	.L473
	cmpq	$3, %rdi
	je	.L474
	cmpq	$4, %rdi
	je	.L475
	cmpq	$5, %rdi
	je	.L476
	cmpq	$6, %rdi
	je	.L477
	movq	16(%rsp), %rax
	movups	%xmm1, (%rax)
	addq	$48, %rax
	movups	%xmm1, -32(%rax)
	movups	%xmm1, -16(%rax)
.L477:
	movups	%xmm1, (%rax)
	addq	$48, %rax
	movups	%xmm1, -32(%rax)
	movups	%xmm1, -16(%rax)
.L476:
	movups	%xmm1, (%rax)
	addq	$48, %rax
	movups	%xmm1, -32(%rax)
	movups	%xmm1, -16(%rax)
.L475:
	movups	%xmm1, (%rax)
	addq	$48, %rax
	movups	%xmm1, -32(%rax)
	movups	%xmm1, -16(%rax)
.L474:
	movups	%xmm1, (%rax)
	addq	$48, %rax
	movups	%xmm1, -32(%rax)
	movups	%xmm1, -16(%rax)
.L473:
	movups	%xmm1, (%rax)
	addq	$48, %rax
	movups	%xmm1, -32(%rax)
	movups	%xmm1, -16(%rax)
.L472:
	movups	%xmm1, (%rax)
	addq	$48, %rax
	movups	%xmm1, -32(%rax)
	movups	%xmm1, -16(%rax)
	cmpq	%r10, %rax
	je	.L575
.L172:
	movups	%xmm1, (%rax)
	addq	$384, %rax
	movups	%xmm1, -368(%rax)
	movups	%xmm1, -352(%rax)
	movups	%xmm1, -336(%rax)
	movups	%xmm1, -320(%rax)
	movups	%xmm1, -304(%rax)
	movups	%xmm1, -288(%rax)
	movups	%xmm1, -272(%rax)
	movups	%xmm1, -256(%rax)
	movups	%xmm1, -240(%rax)
	movups	%xmm1, -224(%rax)
	movups	%xmm1, -208(%rax)
	movups	%xmm1, -192(%rax)
	movups	%xmm1, -176(%rax)
	movups	%xmm1, -160(%rax)
	movups	%xmm1, -144(%rax)
	movups	%xmm1, -128(%rax)
	movups	%xmm1, -112(%rax)
	movups	%xmm1, -96(%rax)
	movups	%xmm1, -80(%rax)
	movups	%xmm1, -64(%rax)
	movups	%xmm1, -48(%rax)
	movups	%xmm1, -32(%rax)
	movups	%xmm1, -16(%rax)
	cmpq	%r10, %rax
	jne	.L172
.L575:
	testb	$1, %r12b
	je	.L170
	andq	$-2, %r12
	imulq	$24, %r12, %rbp
	addq	16(%rsp), %rbp
.L171:
	xorl	%r8d, %r8d
	pxor	%xmm3, %xmm3
	movq	%r8, 16(%rbp)
	movups	%xmm3, 0(%rbp)
.L170:
	movq	8(%rsp), %r12
	movq	%rdx, 200(%rsp)
	movq	%r12, %r8
	cmpq	%r9, %r12
	je	.L178
	.p2align 4
	.p2align 3
.L177:
	movl	(%r8), %ebp
	movl	%ebp, %ebx
	cmpl	%ebp, %ecx
	jge	.L176
	jmp	.L186
	.p2align 5
	.p2align 4,,10
	.p2align 3
.L179:
	addl	%ebp, %ebx
	cmpl	%ebx, %ecx
	jl	.L186
.L176:
	xorl	%eax, %eax
	cmpl	%ebx, %ebp
	sete	%al
	addl	%ebx, %eax
	cltq
	movl	0(%r13,%rax,4), %r12d
	testl	%r12d, %r12d
	js	.L179
	movq	8(%rsp), %r11
	movslq	%r12d, %r14
	movl	(%r11,%r14,4), %eax
	subl	%ebx, %eax
	cmpl	%ebp, %eax
	jge	.L179
	movq	16(%rsp), %rdx
	cltq
	movslq	%ebp, %rsi
	leaq	(%rax,%rax,2), %r10
	leaq	(%rdx,%r10,8), %rdx
	leaq	0(%r13,%rsi,4), %r10
	movq	8(%rdx), %r14
	movq	16(%rdx), %rsi
	cmpq	%rsi, %r14
	je	.L180
	movl	(%r10), %r11d
	movl	%r12d, 4(%r14)
	addq	$8, %r14
	movl	%r11d, -8(%r14)
	movl	(%r8), %ebp
	movq	%r14, 8(%rdx)
	addl	%ebp, %ebx
	cmpl	%ebx, %ecx
	jge	.L176
	.p2align 4
	.p2align 3
.L186:
	addq	$4, %r8
	cmpq	%r8, %r9
	jne	.L177
.L178:
	movslq	120(%rsp), %rsi
	movq	104(%rsp), %rdi
	leaq	154(%rsp), %rdx
	movl	%ecx, 24(%rsp)
.LEHB3:
	call	_ZNSt6vectorIiSaIiEEC1EmRKS0_
	movq	232(%rsp), %r15
	movq	224(%rsp), %rbp
	movslq	24(%rsp), %r9
	cmpq	%rbp, %r15
	je	.L193
	leaq	-4(%r15), %r12
	movq	%rbp, %rax
	subq	%rbp, %r12
	cmpq	$8, %r12
	jbe	.L262
	shrq	$2, %r12
	movl	$4, %r8d
	movdqa	.LC1(%rip), %xmm4
	addq	$1, %r12
	movd	%r8d, %xmm5
	movq	%r12, %r10
	pshufd	$0, %xmm5, %xmm6
	shrq	$2, %r10
	salq	$4, %r10
	leaq	(%r10,%rbp), %rdi
	subq	$16, %r10
	shrq	$4, %r10
	addq	$1, %r10
	andl	$7, %r10d
	je	.L191
	cmpq	$1, %r10
	je	.L484
	cmpq	$2, %r10
	je	.L485
	cmpq	$3, %r10
	je	.L486
	cmpq	$4, %r10
	je	.L487
	cmpq	$5, %r10
	je	.L488
	cmpq	$6, %r10
	jne	.L607
.L489:
	movups	%xmm4, (%rax)
	paddd	%xmm6, %xmm4
	addq	$16, %rax
.L488:
	movups	%xmm4, (%rax)
	paddd	%xmm6, %xmm4
	addq	$16, %rax
.L487:
	movups	%xmm4, (%rax)
	paddd	%xmm6, %xmm4
	addq	$16, %rax
.L486:
	movups	%xmm4, (%rax)
	paddd	%xmm6, %xmm4
	addq	$16, %rax
.L485:
	movups	%xmm4, (%rax)
	paddd	%xmm6, %xmm4
	addq	$16, %rax
.L484:
	movups	%xmm4, (%rax)
	addq	$16, %rax
	paddd	%xmm6, %xmm4
	cmpq	%rdi, %rax
	je	.L573
.L191:
	movups	%xmm4, (%rax)
	paddd	%xmm6, %xmm4
	subq	$-128, %rax
	movups	%xmm4, -112(%rax)
	paddd	%xmm6, %xmm4
	movups	%xmm4, -96(%rax)
	paddd	%xmm6, %xmm4
	movups	%xmm4, -80(%rax)
	paddd	%xmm6, %xmm4
	movups	%xmm4, -64(%rax)
	paddd	%xmm6, %xmm4
	movups	%xmm4, -48(%rax)
	paddd	%xmm6, %xmm4
	movups	%xmm4, -32(%rax)
	paddd	%xmm6, %xmm4
	movups	%xmm4, -16(%rax)
	paddd	%xmm6, %xmm4
	cmpq	%rdi, %rax
	jne	.L191
.L573:
	testb	$3, %r12b
	je	.L193
	andq	$-4, %r12
	leaq	0(%rbp,%r12,4), %rbx
.L190:
	leaq	4(%rbx), %rdx
	movl	%r12d, (%rbx)
	cmpq	%rdx, %r15
	je	.L193
	leal	1(%r12), %ecx
	leaq	8(%rbx), %r14
	movl	%ecx, 4(%rbx)
	cmpq	%r14, %r15
	je	.L193
	addl	$2, %r12d
	movl	%r12d, 8(%rbx)
.L193:
	xorl	%r11d, %r11d
	cmpl	$-1, %r9d
	je	.L189
	movq	16(%rsp), %rsi
	movq	%r13, 40(%rsp)
	xorl	%r11d, %r11d
	movq	%r9, 16(%rsp)
	movq	%r11, %r10
	movq	%rsi, %r8
	.p2align 4
	.p2align 3
.L233:
	movq	(%r8), %rbx
	movq	8(%r8), %r9
	cmpq	%rbx, %r9
	je	.L195
	.p2align 4
	.p2align 3
.L232:
	movslq	(%rbx), %r13
	movq	%r13, %r15
	leaq	0(%rbp,%r13,4), %r13
	movl	0(%r13), %r12d
	cmpl	%r12d, %r15d
	je	.L196
	movslq	%r12d, %rdi
	leaq	0(%rbp,%rdi,4), %r14
	movl	(%r14), %edx
	cmpl	%edx, %r12d
	je	.L197
	movslq	%edx, %r12
	leaq	0(%rbp,%r12,4), %r12
	movl	(%r12), %edi
	cmpl	%edi, %edx
	je	.L198
	movslq	%edi, %rax
	leaq	0(%rbp,%rax,4), %r15
	movl	(%r15), %eax
	cmpl	%eax, %edi
	je	.L199
	movslq	%eax, %rdx
	leaq	0(%rbp,%rdx,4), %rdx
	movl	(%rdx), %esi
	cmpl	%esi, %eax
	je	.L200
	movslq	%esi, %rcx
	leaq	0(%rbp,%rcx,4), %rcx
	movl	(%rcx), %eax
	cmpl	%eax, %esi
	je	.L201
	movslq	%eax, %rsi
	leaq	0(%rbp,%rsi,4), %rdi
	movl	(%rdi), %esi
	movq	%rdi, 24(%rsp)
	cmpl	%esi, %eax
	je	.L202
	movq	104(%rsp), %rdi
	movq	%r8, 80(%rsp)
	movq	%r10, 72(%rsp)
	movq	%r9, 64(%rsp)
	movq	%r11, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	%rdx, 32(%rsp)
	call	_ZN3dsu7findsetIiEEiT_
	movq	24(%rsp), %r11
	movq	80(%rsp), %r8
	movq	72(%rsp), %r10
	movq	64(%rsp), %r9
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx
	movl	%eax, (%r11)
	movq	56(%rsp), %r11
.L202:
	movl	%eax, (%rcx)
.L201:
	movl	%eax, (%rdx)
	movl	%eax, %esi
.L200:
	movl	%esi, (%r15)
	movl	%esi, %eax
.L199:
	movl	%eax, (%r12)
	movl	%eax, %edi
.L198:
	movl	%edi, (%r14)
	movl	%edi, %edx
.L197:
	movl	%edx, 0(%r13)
	movl	%edx, %r12d
.L196:
	movslq	4(%rbx), %r13
	movq	%r13, %r14
	leaq	0(%rbp,%r13,4), %r13
	movl	0(%r13), %r15d
	cmpl	%r15d, %r14d
	je	.L203
	movslq	%r15d, %rcx
	leaq	0(%rbp,%rcx,4), %r14
	movl	(%r14), %ecx
	cmpl	%ecx, %r15d
	je	.L204
	movslq	%ecx, %rsi
	leaq	0(%rbp,%rsi,4), %r15
	movl	(%r15), %edi
	cmpl	%edi, %ecx
	je	.L205
	movslq	%edi, %rax
	leaq	0(%rbp,%rax,4), %rdx
	movl	(%rdx), %eax
	cmpl	%eax, %edi
	je	.L206
	movslq	%eax, %rdi
	leaq	0(%rbp,%rdi,4), %rcx
	movl	(%rcx), %esi
	cmpl	%esi, %eax
	je	.L207
	movslq	%esi, %rax
	leaq	0(%rbp,%rax,4), %rdi
	movl	(%rdi), %eax
	movq	%rdi, 24(%rsp)
	cmpl	%eax, %esi
	je	.L208
	movslq	%eax, %rsi
	leaq	0(%rbp,%rsi,4), %rdi
	movl	(%rdi), %esi
	movq	%rdi, 32(%rsp)
	cmpl	%esi, %eax
	je	.L209
	movq	104(%rsp), %rdi
	movq	%r8, 88(%rsp)
	movq	%r10, 80(%rsp)
	movq	%r9, 72(%rsp)
	movq	%r11, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%rdx, 48(%rsp)
	call	_ZN3dsu7findsetIiEEiT_
	movq	32(%rsp), %rdx
	movq	88(%rsp), %r8
	movq	80(%rsp), %r10
	movq	72(%rsp), %r9
	movq	64(%rsp), %r11
	movq	56(%rsp), %rcx
	movl	%eax, (%rdx)
	movq	48(%rsp), %rdx
.L209:
	movq	24(%rsp), %rsi
	movl	%eax, (%rsi)
.L208:
	movl	%eax, (%rcx)
	movl	%eax, %esi
.L207:
	movl	%esi, (%rdx)
	movl	%esi, %eax
.L206:
	movl	%eax, (%r15)
	movl	%eax, %edi
.L205:
	movl	%edi, (%r14)
	movl	%edi, %ecx
.L204:
	movl	%ecx, 0(%r13)
	cmpl	%ecx, %r12d
	je	.L211
	movslq	4(%rbx), %r13
	movl	(%rbx), %r12d
	movq	%r13, %r15
	leaq	0(%rbp,%r13,4), %r13
	movl	0(%r13), %esi
	cmpl	%esi, %r15d
	je	.L212
	movslq	%esi, %r14
	leaq	0(%rbp,%r14,4), %r14
	movl	(%r14), %r15d
	cmpl	%r15d, %esi
	je	.L213
	movslq	%r15d, %rdx
	leaq	0(%rbp,%rdx,4), %rdx
	movl	(%rdx), %esi
	cmpl	%esi, %r15d
	je	.L214
	movslq	%esi, %r15
	leaq	0(%rbp,%r15,4), %r15
	movl	(%r15), %edi
	cmpl	%edi, %esi
	je	.L215
	movslq	%edi, %rax
	leaq	0(%rbp,%rax,4), %rcx
	movl	(%rcx), %eax
	cmpl	%eax, %edi
	je	.L216
	movslq	%eax, %rdi
	leaq	0(%rbp,%rdi,4), %rsi
	movl	(%rsi), %edi
	movq	%rsi, 24(%rsp)
	cmpl	%edi, %eax
	je	.L217
	movslq	%edi, %rax
	leaq	0(%rbp,%rax,4), %rsi
	movl	(%rsi), %eax
	movq	%rsi, 32(%rsp)
	cmpl	%eax, %edi
	je	.L218
	movslq	%eax, %rdi
	leaq	0(%rbp,%rdi,4), %rsi
	movq	%rsi, 48(%rsp)
	movl	(%rsi), %esi
	cmpl	%esi, %eax
	jne	.L608
.L219:
	movq	32(%rsp), %rdi
	movl	%esi, %eax
	movl	%esi, (%rdi)
.L218:
	movq	24(%rsp), %rsi
	movl	%eax, (%rsi)
.L217:
	movl	%eax, (%rcx)
.L216:
	movl	%eax, (%r15)
	movl	%eax, %edi
.L215:
	movl	%edi, (%rdx)
	movl	%edi, %esi
.L214:
	movl	%esi, (%r14)
	movl	%esi, %r15d
.L213:
	movl	%r15d, 0(%r13)
.L212:
	movslq	%r12d, %r13
	leaq	0(%rbp,%r13,4), %r13
	movslq	0(%r13), %r14
	cmpl	%r14d, %r12d
	je	.L222
	movslq	%r14d, %r12
	leaq	0(%rbp,%r12,4), %r12
	movl	(%r12), %edx
	cmpl	%edx, %r14d
	je	.L223
	movslq	%edx, %r14
	leaq	0(%rbp,%r14,4), %r14
	movl	(%r14), %esi
	cmpl	%esi, %edx
	je	.L224
	movslq	%esi, %rcx
	leaq	0(%rbp,%rcx,4), %rdx
	movl	(%rdx), %edi
	cmpl	%edi, %esi
	je	.L225
	movslq	%edi, %rax
	leaq	0(%rbp,%rax,4), %rcx
	movl	(%rcx), %eax
	cmpl	%eax, %edi
	je	.L226
	movslq	%eax, %rdi
	leaq	0(%rbp,%rdi,4), %rsi
	movl	(%rsi), %edi
	movq	%rsi, 24(%rsp)
	cmpl	%edi, %eax
	je	.L227
	movslq	%edi, %rax
	leaq	0(%rbp,%rax,4), %rsi
	movl	(%rsi), %eax
	movq	%rsi, 32(%rsp)
	cmpl	%eax, %edi
	je	.L228
	movslq	%eax, %rdi
	leaq	0(%rbp,%rdi,4), %rsi
	movq	%rsi, 48(%rsp)
	movl	(%rsi), %esi
	cmpl	%esi, %eax
	jne	.L609
.L229:
	movq	32(%rsp), %rdi
	movl	%esi, %eax
	movl	%esi, (%rdi)
.L228:
	movq	24(%rsp), %rsi
	movl	%eax, (%rsi)
.L227:
	movl	%eax, (%rcx)
.L226:
	movl	%eax, (%rdx)
	movl	%eax, %edi
.L225:
	movl	%edi, (%r14)
	movl	%edi, %esi
.L224:
	movl	%esi, (%r12)
	movl	%esi, %edx
.L223:
	movl	%edx, 0(%r13)
	movslq	%edx, %r14
.L222:
	movl	%r15d, 0(%rbp,%r14,4)
	addq	%r10, %r11
.L211:
	addq	$8, %rbx
	cmpq	%rbx, %r9
	jne	.L232
.L195:
	addq	$24, %r8
	cmpq	16(%rsp), %r10
	je	.L610
	addq	$1, %r10
	jmp	.L233
	.p2align 4,,10
	.p2align 3
.L203:
	cmpl	%r12d, %r15d
	je	.L211
	movl	(%rbx), %r12d
	jmp	.L212
	.p2align 4,,10
	.p2align 3
.L180:
	movabsq	$1152921504606846975, %rax
	movq	(%rdx), %r11
	movq	%r14, %r15
	subq	%r11, %r15
	movq	%r15, %rdi
	sarq	$3, %rdi
	cmpq	%rax, %rdi
	je	.L561
	testq	%rdi, %rdi
	movq	%r9, 64(%rsp)
	movl	$1, %r9d
	cmovne	%rdi, %r9
	movl	%ecx, 40(%rsp)
	movabsq	$1152921504606846975, %rcx
	movq	%r8, 88(%rsp)
	addq	%rdi, %r9
	movq	%r11, 80(%rsp)
	cmpq	%rcx, %r9
	movq	%rsi, 72(%rsp)
	cmova	%rcx, %r9
	movq	%rdx, 56(%rsp)
	movq	%r10, 48(%rsp)
	salq	$3, %r9
	movq	%r9, %rdi
	movq	%r9, 32(%rsp)
	call	_Znwm@PLT
.LEHE3:
	movq	48(%rsp), %r8
	movq	80(%rsp), %r11
	movq	%rax, 24(%rsp)
	movl	40(%rsp), %ecx
	movq	64(%rsp), %r9
	movl	%r12d, 4(%rax,%r15)
	movl	(%r8), %edx
	cmpq	%r11, %r14
	movq	72(%rsp), %rsi
	movq	88(%rsp), %r8
	movl	%edx, (%rax,%r15)
	movq	56(%rsp), %rdx
	je	.L261
	movq	%r14, %r10
	movq	%rax, %rdi
	movq	%r11, %rax
	subq	%r11, %r10
	subq	$8, %r10
	shrq	$3, %r10
	addq	$1, %r10
	andl	$7, %r10d
	je	.L184
	cmpq	$1, %r10
	je	.L478
	cmpq	$2, %r10
	je	.L479
	cmpq	$3, %r10
	je	.L480
	cmpq	$4, %r10
	je	.L481
	cmpq	$5, %r10
	je	.L482
	cmpq	$6, %r10
	je	.L483
	movq	24(%rsp), %rdi
	movq	(%r11), %r15
	leaq	8(%r11), %rax
	movq	%r15, (%rdi)
	addq	$8, %rdi
.L483:
	movq	(%rax), %r12
	addq	$8, %rdi
	addq	$8, %rax
	movq	%r12, -8(%rdi)
.L482:
	movq	(%rax), %r10
	addq	$8, %rdi
	addq	$8, %rax
	movq	%r10, -8(%rdi)
.L481:
	movq	(%rax), %r15
	addq	$8, %rdi
	addq	$8, %rax
	movq	%r15, -8(%rdi)
.L480:
	movq	(%rax), %r12
	addq	$8, %rdi
	addq	$8, %rax
	movq	%r12, -8(%rdi)
.L479:
	movq	(%rax), %r10
	addq	$8, %rdi
	addq	$8, %rax
	movq	%r10, -8(%rdi)
.L478:
	movq	(%rax), %r15
	addq	$8, %rax
	addq	$8, %rdi
	movq	%r15, -8(%rdi)
	cmpq	%rax, %r14
	je	.L574
.L184:
	movq	(%rax), %r12
	addq	$64, %rax
	addq	$64, %rdi
	movq	%r12, -64(%rdi)
	movq	-56(%rax), %r10
	movq	%r10, -56(%rdi)
	movq	-48(%rax), %r15
	movq	%r15, -48(%rdi)
	movq	-40(%rax), %r12
	movq	%r12, -40(%rdi)
	movq	-32(%rax), %r10
	movq	%r10, -32(%rdi)
	movq	-24(%rax), %r15
	movq	%r15, -24(%rdi)
	movq	-16(%rax), %r12
	movq	%r12, -16(%rdi)
	movq	-8(%rax), %r10
	movq	%r10, -8(%rdi)
	cmpq	%rax, %r14
	jne	.L184
.L574:
	movq	24(%rsp), %rdi
	subq	%r11, %r14
	leaq	(%rdi,%r14), %r12
.L183:
	addq	$8, %r12
	testq	%r11, %r11
	je	.L185
	subq	%r11, %rsi
	movq	%r11, %rdi
	movq	%r8, 64(%rsp)
	movq	%r9, 56(%rsp)
	movq	%rdx, 48(%rsp)
	movl	%ecx, 40(%rsp)
	call	_ZdlPvm@PLT
	movq	64(%rsp), %r8
	movq	56(%rsp), %r9
	movq	48(%rsp), %rdx
	movl	40(%rsp), %ecx
	movl	(%r8), %ebp
.L185:
	movq	24(%rsp), %r14
	movq	32(%rsp), %rsi
	movq	%r12, 8(%rdx)
	addq	%r14, %rsi
	movq	%r14, (%rdx)
	movq	%rsi, 16(%rdx)
	jmp	.L179
	.p2align 4,,10
	.p2align 3
.L610:
	movq	40(%rsp), %r13
.L189:
	movq	%r11, %rsi
	leaq	_ZSt4cout(%rip), %rdi
.LEHB4:
	call	_ZNSo9_M_insertIxEERSoT_@PLT
	movq	(%rax), %rbx
	movb	$10, 155(%rsp)
	movq	-24(%rbx), %rbp
	cmpq	$0, 16(%rax,%rbp)
	je	.L234
	leaq	155(%rsp), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
.L235:
	movq	224(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L236
	movq	240(%rsp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L236:
	leaq	192(%rsp), %rdi
	call	_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED1Ev
	testq	%r13, %r13
	je	.L237
	movq	96(%rsp), %rsi
	movq	%r13, %rdi
	call	_ZdlPvm@PLT
.L237:
	movq	8(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L238
	movq	112(%rsp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L238:
	movq	248(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L611
	addq	$264, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L234:
	.cfi_restore_state
	movl	$10, %esi
	movq	%rax, %rdi
	call	_ZNSo3putEc@PLT
.LEHE4:
	jmp	.L235
.L606:
	xorl	%r11d, %r11d
	xorl	%edx, %edx
	movq	%r11, 192(%rsp)
	movq	%r11, 208(%rsp)
	movq	%r11, 16(%rsp)
	jmp	.L170
.L601:
	movq	%rbx, %r9
	jmp	.L151
.L261:
	movq	24(%rsp), %r12
	jmp	.L183
.L599:
	movq	8(%rsp), %r14
	leaq	_ZSt3cin(%rip), %rdi
	movq	%r14, %rsi
.LEHB5:
	call	_ZNSirsERi@PLT
.LEHE5:
	leaq	4(%r14), %rbp
	jmp	.L459
.L609:
	movslq	%esi, %rax
	leaq	0(%rbp,%rax,4), %rdi
	movl	(%rdi), %eax
	movq	%rdi, 64(%rsp)
	cmpl	%eax, %esi
	je	.L230
	movslq	%eax, %rsi
	leaq	0(%rbp,%rsi,4), %rdi
	movl	(%rdi), %esi
	movq	%rdi, 56(%rsp)
	cmpl	%esi, %eax
	jne	.L612
.L231:
	movq	64(%rsp), %rax
	movl	%esi, (%rax)
	movl	%esi, %eax
.L230:
	movq	48(%rsp), %rsi
	movl	%eax, (%rsi)
	movl	%eax, %esi
	jmp	.L229
.L608:
	movslq	%esi, %rax
	leaq	0(%rbp,%rax,4), %rdi
	movl	(%rdi), %eax
	movq	%rdi, 64(%rsp)
	cmpl	%eax, %esi
	je	.L220
	movslq	%eax, %rsi
	leaq	0(%rbp,%rsi,4), %rdi
	movl	(%rdi), %esi
	movq	%rdi, 56(%rsp)
	cmpl	%esi, %eax
	jne	.L613
.L221:
	movq	64(%rsp), %rax
	movl	%esi, (%rax)
	movl	%esi, %eax
.L220:
	movq	48(%rsp), %rsi
	movl	%eax, (%rsi)
	movl	%eax, %esi
	jmp	.L219
.L607:
	movups	%xmm4, 0(%rbp)
	leaq	16(%rbp), %rax
	paddd	%xmm6, %xmm4
	jmp	.L489
.L250:
	movq	8(%rsp), %r14
	movq	%r14, %r9
	jmp	.L132
.L603:
	leal	1(%rcx), %esi
	movslq	%esi, %r12
	jmp	.L158
.L262:
	movq	%rbp, %rbx
	xorl	%r12d, %r12d
	jmp	.L190
.L259:
	movq	16(%rsp), %rbp
	jmp	.L171
.L613:
	movq	104(%rsp), %rdi
	movq	%r8, 136(%rsp)
	movq	%r10, 128(%rsp)
	movq	%r9, 120(%rsp)
	movq	%r11, 88(%rsp)
	movq	%rcx, 80(%rsp)
	movq	%rdx, 72(%rsp)
	call	_ZN3dsu7findsetIiEEiT_
	movq	56(%rsp), %r8
	movq	120(%rsp), %r9
	movq	128(%rsp), %r10
	movq	88(%rsp), %r11
	movl	%eax, %esi
	movq	80(%rsp), %rcx
	movq	72(%rsp), %rdx
	movl	%eax, (%r8)
	movq	136(%rsp), %r8
	jmp	.L221
.L612:
	movq	104(%rsp), %rdi
	movq	%r8, 136(%rsp)
	movq	%r10, 128(%rsp)
	movq	%r9, 120(%rsp)
	movq	%r11, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	call	_ZN3dsu7findsetIiEEiT_
	movq	56(%rsp), %r9
	movq	88(%rsp), %r11
	movq	136(%rsp), %r8
	movq	128(%rsp), %r10
	movl	%eax, %esi
	movq	80(%rsp), %rdx
	movq	72(%rsp), %rcx
	movl	%eax, (%r9)
	movq	120(%rsp), %r9
	jmp	.L231
.L605:
	jmp	.L159
.L611:
	call	__stack_chk_fail@PLT
.L554:
	endbr64
	jmp	.L555
.L556:
	endbr64
	jmp	.L557
.L558:
	endbr64
	jmp	.L559
.L271:
	endbr64
	movq	%rax, %r15
	jmp	.L239
	.section	.gcc_except_table,"a",@progbits
.LLSDA14955:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE14955-.LLSDACSB14955
.LLSDACSB14955:
	.uleb128 .LEHB0-.LFB14955
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB14955
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L554-.LFB14955
	.uleb128 0
	.uleb128 .LEHB2-.LFB14955
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L558-.LFB14955
	.uleb128 0
	.uleb128 .LEHB3-.LFB14955
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L556-.LFB14955
	.uleb128 0
	.uleb128 .LEHB4-.LFB14955
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L271-.LFB14955
	.uleb128 0
	.uleb128 .LEHB5-.LFB14955
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L554-.LFB14955
	.uleb128 0
.LLSDACSE14955:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC14955
	.type	main.cold, @function
main.cold:
.LFSB14955:
.L159:
	.cfi_def_cfa_offset 320
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	248(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L614
	leaq	.LC0(%rip), %rdi
.LEHB6:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE6:
.L269:
	endbr64
.L555:
	movq	%rax, %r15
.L244:
	cmpq	$0, 8(%rsp)
	je	.L245
	movq	112(%rsp), %rsi
	movq	8(%rsp), %rdi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L245:
	movq	248(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L615
	movq	%r15, %rdi
.LEHB7:
	call	_Unwind_Resume@PLT
.LEHE7:
.L270:
	endbr64
.L557:
	movq	%rax, %r15
.L241:
	leaq	192(%rsp), %rdi
	call	_ZNSt6vectorIS_ISt4pairIiiESaIS1_EESaIS3_EED1Ev
.L242:
	testq	%r13, %r13
	je	.L244
	movq	96(%rsp), %rsi
	movq	%r13, %rdi
	call	_ZdlPvm@PLT
	jmp	.L244
.L560:
	movq	248(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L616
	leaq	.LC0(%rip), %rdi
.LEHB8:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE8:
.L561:
	movq	248(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L617
	leaq	.LC2(%rip), %rdi
.LEHB9:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE9:
.L616:
	call	__stack_chk_fail@PLT
.L617:
	call	__stack_chk_fail@PLT
.L614:
	call	__stack_chk_fail@PLT
.L272:
	endbr64
.L559:
	movq	%rax, %r15
	jmp	.L242
.L615:
	call	__stack_chk_fail@PLT
.L239:
	movq	224(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L241
	movq	240(%rsp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
	jmp	.L241
	.cfi_endproc
.LFE14955:
	.section	.gcc_except_table
.LLSDAC14955:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC14955-.LLSDACSBC14955
.LLSDACSBC14955:
	.uleb128 .LEHB6-.LCOLDB5
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L272-.LCOLDB5
	.uleb128 0
	.uleb128 .LEHB7-.LCOLDB5
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LCOLDB5
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L269-.LCOLDB5
	.uleb128 0
	.uleb128 .LEHB9-.LCOLDB5
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L270-.LCOLDB5
	.uleb128 0
.LLSDACSEC14955:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE5:
	.section	.text.startup
.LHOTE5:
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.long	0
	.long	1
	.long	2
	.long	3
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.globl	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 15-20250404-0ubuntu1) 15.0.1 20250404 (experimental) [master r15-9193-g08e803aa9be]"
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
