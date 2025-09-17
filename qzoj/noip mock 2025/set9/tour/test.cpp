asm(R"(
.file	"tour.cpp"
	.intel_syntax noprefix
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.p2align 4
	.type	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c.isra.0, @function
_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c.isra.0:
.LFB19126:
	.cfi_startproc
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	mov	rax, QWORD PTR [rdi]
	mov	BYTE PTR 12[rsp], sil
	mov	rax, QWORD PTR -24[rax]
	cmp	QWORD PTR 16[rdi+rax], 0
	je	.L2
	lea	rsi, 12[rsp]
	mov	edx, 1
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
.L1:
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L2:
	.cfi_restore_state
	movsx	esi, BYTE PTR 12[rsp]
	call	_ZNSo3putEc@PLT
	jmp	.L1
	.cfi_endproc
.LFE19126:
	.size	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c.isra.0, .-_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c.isra.0
	.align 2
	.p2align 4
	.type	_ZNSt6vectorIxSaIxEEaSERKS1_.isra.0, @function
_ZNSt6vectorIxSaIxEEaSERKS1_.isra.0:
.LFB19127:
	.cfi_startproc
	cmp	rsi, rdi
	je	.L23
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rcx, rsi
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	mov	rbx, rdi
	sub	rsp, 40
	.cfi_def_cfa_offset 64
	mov	rax, QWORD PTR 8[rsi]
	mov	r9, QWORD PTR [rdi]
	mov	rsi, QWORD PTR [rsi]
	mov	r8, QWORD PTR 16[rdi]
	mov	rbp, rax
	sub	rbp, rsi
	sub	r8, r9
	cmp	r8, rbp
	jb	.L27
	mov	rdi, QWORD PTR 8[rdi]
	mov	rdx, rdi
	sub	rdx, r9
	cmp	rdx, rbp
	jb	.L11
	cmp	rbp, 8
	jle	.L12
	mov	rdx, rbp
	mov	rdi, r9
	call	memmove@PLT
	mov	rax, QWORD PTR [rbx]
	add	rax, rbp
.L10:
	mov	QWORD PTR 8[rbx], rax
	add	rsp, 40
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L27:
	.cfi_restore_state
	mov	rdi, rbp
	mov	QWORD PTR 8[rsp], r9
	mov	QWORD PTR 16[rsp], rsi
	mov	QWORD PTR 24[rsp], r8
	call	_Znwm@PLT
	mov	rsi, QWORD PTR 16[rsp]
	mov	rdx, rbp
	mov	rdi, rax
	call	memcpy@PLT
	mov	r9, QWORD PTR 8[rsp]
	mov	rcx, rax
	test	r9, r9
	je	.L9
	mov	rsi, QWORD PTR 24[rsp]
	mov	rdi, r9
	mov	QWORD PTR 8[rsp], rax
	call	_ZdlPvm@PLT
	mov	rcx, QWORD PTR 8[rsp]
.L9:
	lea	rax, [rcx+rbp]
	mov	QWORD PTR [rbx], rcx
	mov	QWORD PTR 16[rbx], rax
	mov	QWORD PTR 8[rbx], rax
	add	rsp, 40
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L23:
	.cfi_restore 3
	.cfi_restore 6
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	.cfi_def_cfa_offset 64
	.cfi_offset 3, -24
	.cfi_offset 6, -16
	cmp	rdx, 8
	jle	.L15
	mov	rdi, r9
	mov	QWORD PTR 8[rsp], rcx
	call	memmove@PLT
	mov	rcx, QWORD PTR 8[rsp]
	mov	rdi, QWORD PTR 8[rbx]
	mov	rax, QWORD PTR 8[rcx]
	mov	rsi, QWORD PTR [rcx]
	mov	rdx, rdi
	sub	rdx, QWORD PTR [rbx]
.L16:
	add	rsi, rdx
	sub	rax, rsi
	mov	rdx, rax
	test	rax, rax
	jle	.L26
	call	memcpy@PLT
.L26:
	mov	rax, QWORD PTR [rbx]
	add	rax, rbp
	mov	QWORD PTR 8[rbx], rax
	add	rsp, 40
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L12:
	.cfi_restore_state
	lea	rax, [r9+rbp]
	jne	.L10
	mov	rdx, QWORD PTR [rsi]
	mov	QWORD PTR [r9], rdx
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L15:
	jne	.L16
	mov	rcx, QWORD PTR [rsi]
	mov	QWORD PTR [r9], rcx
	jmp	.L16
	.cfi_endproc
.LFE19127:
	.size	_ZNSt6vectorIxSaIxEEaSERKS1_.isra.0, .-_ZNSt6vectorIxSaIxEEaSERKS1_.isra.0
	.section	.text._ZN8mathbaseD2Ev,"axG",@progbits,_ZN8mathbaseD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8mathbaseD2Ev
	.type	_ZN8mathbaseD2Ev, @function
_ZN8mathbaseD2Ev:
.LFB18271:
	.cfi_startproc
	endbr64
	mov	rax, rdi
	mov	rdi, QWORD PTR 24[rdi]
	test	rdi, rdi
	je	.L35
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	mov	rsi, QWORD PTR 40[rax]
	mov	QWORD PTR 8[rsp], rax
	sub	rsi, rdi
	call	_ZdlPvm@PLT
	mov	rax, QWORD PTR 8[rsp]
	mov	rdi, QWORD PTR [rax]
	test	rdi, rdi
	je	.L28
	mov	rsi, QWORD PTR 16[rax]
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	sub	rsi, rdi
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L28:
	.cfi_restore_state
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L35:
	mov	rdi, QWORD PTR [rax]
	test	rdi, rdi
	je	.L37
	mov	rsi, QWORD PTR 16[rax]
	sub	rsi, rdi
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L37:
	ret
	.cfi_endproc
.LFE18271:
	.size	_ZN8mathbaseD2Ev, .-_ZN8mathbaseD2Ev
	.weak	_ZN8mathbaseD1Ev
	.set	_ZN8mathbaseD1Ev,_ZN8mathbaseD2Ev
	.text
	.p2align 4
	.type	_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEENS0_5__ops15_Iter_less_iterEEvT_SB_T0_.isra.0, @function
_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEENS0_5__ops15_Iter_less_iterEEvT_SB_T0_.isra.0:
.LFB19131:
	.cfi_startproc
	cmp	rdi, rsi
	je	.L63
	mov	r9, rdi
	lea	rdi, 8[rdi]
	mov	r11, rsi
	cmp	rsi, rdi
	je	.L63
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	lea	r10, 16[r9]
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbx, -8
	sub	rbx, r9
	.p2align 4
	.p2align 3
.L55:
	mov	esi, DWORD PTR [rdi]
	cmp	esi, DWORD PTR [r9]
	je	.L66
	jge	.L61
	mov	r12d, DWORD PTR 4[rdi]
.L46:
	mov	rbp, r10
	cmp	r9, rdi
	je	.L50
	lea	r8, [rbx+rdi]
	mov	rax, rdi
	xor	edx, edx
	shr	r8, 3
	add	r8, 1
	.p2align 5
	.p2align 4
	.p2align 3
.L49:
	mov	rcx, QWORD PTR -8[rax]
	add	rdx, 1
	sub	rax, 8
	mov	QWORD PTR 8[rax], rcx
	cmp	rdx, r8
	jb	.L49
.L50:
	mov	DWORD PTR [r9], esi
	mov	DWORD PTR 4[r9], r12d
.L48:
	add	rdi, 8
	add	r10, 8
	cmp	r11, rbp
	jne	.L55
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L66:
	.cfi_restore_state
	mov	r12d, DWORD PTR 4[rdi]
	mov	r8d, DWORD PTR 4[r9]
	cmp	r12d, r8d
	je	.L45
	jl	.L46
	mov	r8d, r12d
.L45:
	mov	rax, rdi
	.p2align 4
	.p2align 3
.L51:
	mov	edx, DWORD PTR -8[rax]
	cmp	esi, edx
	je	.L52
	jl	.L67
.L54:
	mov	DWORD PTR [rax], esi
	mov	rbp, r10
	mov	DWORD PTR 4[rax], r8d
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L52:
	mov	ecx, DWORD PTR -4[rax]
	cmp	ecx, r8d
	je	.L54
	jle	.L54
.L53:
	mov	DWORD PTR [rax], edx
	sub	rax, 8
	mov	DWORD PTR 12[rax], ecx
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L67:
	mov	ecx, DWORD PTR -4[rax]
	jmp	.L53
	.p2align 4,,10
	.p2align 3
.L61:
	mov	r8d, DWORD PTR 4[rdi]
	jmp	.L45
.L63:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	ret
	.cfi_endproc
.LFE19131:
	.size	_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEENS0_5__ops15_Iter_less_iterEEvT_SB_T0_.isra.0, .-_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEENS0_5__ops15_Iter_less_iterEEvT_SB_T0_.isra.0
	.p2align 4
	.type	_ZSt13__adjust_heapIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElS3_NS0_5__ops15_Iter_less_iterEEvT_T0_SC_T1_T2_.isra.0, @function
_ZSt13__adjust_heapIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElS3_NS0_5__ops15_Iter_less_iterEEvT_T0_SC_T1_T2_.isra.0:
.LFB19133:
	.cfi_startproc
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	lea	r12, -1[rdx]
	mov	r8, rsi
	movq	xmm0, rcx
	shr	r12, 63
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	mov	rbp, rdx
	lea	r12, -1[rdx+r12]
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	sar	r12
	cmp	rsi, r12
	jge	.L69
	mov	r10, rsi
	jmp	.L74
	.p2align 4,,10
	.p2align 3
.L70:
	jl	.L91
	mov	r9d, DWORD PTR 4[rax]
.L72:
	mov	DWORD PTR [rdi+r10*8], esi
	mov	DWORD PTR 4[rdi+r10*8], r9d
	cmp	rdx, r12
	jge	.L92
.L83:
	mov	r10, rdx
.L74:
	lea	rax, 1[r10]
	lea	rdx, [rax+rax]
	sal	rax, 4
	lea	r11, -1[rdx]
	add	rax, rdi
	lea	rcx, [rdi+r11*8]
	mov	esi, DWORD PTR [rax]
	mov	ebx, DWORD PTR [rcx]
	cmp	esi, ebx
	jne	.L70
	mov	ebx, DWORD PTR 4[rax]
	mov	r9d, DWORD PTR 4[rcx]
	cmp	ebx, r9d
	je	.L72
	cmovge	r9d, ebx
	cmovl	rdx, r11
	mov	DWORD PTR [rdi+r10*8], esi
	cmovl	rax, rcx
	mov	DWORD PTR 4[rdi+r10*8], r9d
	cmp	rdx, r12
	jl	.L83
.L92:
	test	bpl, 1
	je	.L93
.L75:
	lea	rcx, -1[rdx]
	pshufd	xmm1, xmm0, 0xe5
	movd	r9d, xmm0
	movd	r10d, xmm1
	shr	rcx, 63
	lea	rcx, -1[rdx+rcx]
	sar	rcx
	cmp	rdx, r8
	jle	.L76
	.p2align 4
	.p2align 3
.L80:
	lea	rax, [rdi+rcx*8]
	mov	esi, DWORD PTR [rax]
	cmp	esi, r9d
	je	.L77
	jl	.L78
.L88:
	lea	rax, [rdi+rdx*8]
.L76:
	movq	QWORD PTR [rax], xmm0
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L91:
	.cfi_restore_state
	mov	r9d, DWORD PTR 4[rcx]
	mov	esi, ebx
	mov	rax, rcx
	mov	rdx, r11
	jmp	.L72
	.p2align 4,,10
	.p2align 3
.L77:
	cmp	DWORD PTR 4[rax], r10d
	je	.L88
	jge	.L88
.L78:
	mov	DWORD PTR [rdi+rdx*8], esi
	mov	esi, DWORD PTR 4[rax]
	mov	DWORD PTR 4[rdi+rdx*8], esi
	lea	rdx, -1[rcx]
	shr	rdx, 63
	lea	rsi, -1[rdx+rcx]
	mov	rdx, rcx
	cmp	r8, rcx
	jge	.L76
	mov	rcx, rsi
	sar	rcx
	jmp	.L80
	.p2align 4,,10
	.p2align 3
.L93:
	sub	rbp, 2
	sar	rbp
	cmp	rdx, rbp
	jne	.L75
.L81:
	lea	rdx, 1[rdx+rdx]
	lea	rcx, [rdi+rdx*8]
	mov	rsi, QWORD PTR [rcx]
	mov	QWORD PTR [rax], rsi
	mov	rax, rcx
	jmp	.L75
	.p2align 4,,10
	.p2align 3
.L69:
	lea	rax, [rdi+rsi*8]
	test	dl, 1
	jne	.L76
	sub	rbp, 2
	sar	rbp
	cmp	rsi, rbp
	jne	.L76
	mov	rdx, r8
	jmp	.L81
	.cfi_endproc
.LFE19133:
	.size	_ZSt13__adjust_heapIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElS3_NS0_5__ops15_Iter_less_iterEEvT_T0_SC_T1_T2_.isra.0, .-_ZSt13__adjust_heapIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElS3_NS0_5__ops15_Iter_less_iterEEvT_T0_SC_T1_T2_.isra.0
	.p2align 4
	.type	_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElNS0_5__ops15_Iter_less_iterEEvT_SB_T0_T1_.isra.0, @function
_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElNS0_5__ops15_Iter_less_iterEEvT_SB_T0_T1_.isra.0:
.LFB19135:
	.cfi_startproc
	mov	rax, rsi
	sub	rax, rdi
	cmp	rax, 128
	jle	.L147
	push	r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	mov	r14, rax
	sar	rax, 4
	push	r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	mov	r13, rdx
	sar	r14, 3
	push	r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	mov	r12, rsi
	push	rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	mov	rbp, rdi
	push	rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	test	r13, r13
	je	.L148
.L96:
	lea	rax, 0[rbp+rax*8]
	mov	edx, DWORD PTR 8[rbp]
	sub	r13, 1
	lea	rbx, 8[rbp]
	mov	ecx, DWORD PTR [rax]
	cmp	edx, ecx
	je	.L149
	jge	.L105
	mov	edi, DWORD PTR -8[r12]
	cmp	edi, ecx
	je	.L150
.L106:
	cmp	ecx, edi
	jl	.L123
.L111:
	cmp	edx, edi
	je	.L113
	cmp	edx, edi
	jl	.L114
.L139:
	mov	r8d, DWORD PTR 12[rbp]
.L116:
	mov	eax, DWORD PTR 0[rbp]
	mov	DWORD PTR 0[rbp], edx
	mov	DWORD PTR 8[rbp], eax
	mov	eax, DWORD PTR 4[rbp]
	mov	DWORD PTR 4[rbp], r8d
	mov	DWORD PTR 12[rbp], eax
.L112:
	mov	rdi, r12
	.p2align 4
	.p2align 3
.L124:
	mov	ecx, DWORD PTR [rbx]
	cmp	ecx, edx
	je	.L125
.L146:
	jl	.L126
.L127:
	lea	rax, -8[rdi]
	.p2align 4
	.p2align 3
.L128:
	mov	esi, DWORD PTR [rax]
	mov	rdi, rax
	cmp	esi, edx
	je	.L129
	jg	.L130
.L131:
	cmp	rbx, rax
	jnb	.L151
	mov	DWORD PTR [rbx], esi
	add	rbx, 8
	mov	DWORD PTR [rax], ecx
	mov	ecx, DWORD PTR 4[rax]
	mov	edx, DWORD PTR -4[rbx]
	mov	DWORD PTR -4[rbx], ecx
	mov	DWORD PTR 4[rax], edx
	mov	edx, DWORD PTR 0[rbp]
	mov	ecx, DWORD PTR [rbx]
	cmp	ecx, edx
	jne	.L146
	.p2align 4
	.p2align 3
.L125:
	mov	eax, DWORD PTR 4[rbp]
	cmp	DWORD PTR 4[rbx], eax
	je	.L127
	jge	.L127
.L126:
	add	rbx, 8
	jmp	.L124
	.p2align 4,,10
	.p2align 3
.L129:
	mov	r9d, DWORD PTR 4[rax]
	cmp	DWORD PTR 4[rbp], r9d
	je	.L131
	jge	.L131
.L130:
	sub	rax, 8
	jmp	.L128
	.p2align 4,,10
	.p2align 3
.L151:
	mov	rdx, r13
	mov	rsi, r12
	mov	rdi, rbx
	call	_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElNS0_5__ops15_Iter_less_iterEEvT_SB_T0_T1_.isra.0
	mov	rax, rbx
	sub	rax, rbp
	cmp	rax, 128
	jle	.L94
	mov	r14, rax
	mov	r12, rbx
	sar	rax, 4
	sar	r14, 3
	test	r13, r13
	jne	.L96
.L148:
	lea	rbx, -1[rax]
	jmp	.L100
.L97:
	sub	rbx, 1
.L100:
	mov	rcx, QWORD PTR 0[rbp+rbx*8]
	mov	rdx, r14
	mov	rsi, rbx
	mov	rdi, rbp
	call	_ZSt13__adjust_heapIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElS3_NS0_5__ops15_Iter_less_iterEEvT_T0_SC_T1_T2_.isra.0
	test	rbx, rbx
	jne	.L97
	mov	rax, r12
	sub	r12, 8
	sub	rax, rbp
	cmp	rax, 8
	jle	.L94
	.p2align 4
	.p2align 3
.L101:
	mov	rax, QWORD PTR 0[rbp]
	mov	rbx, r12
	mov	rcx, QWORD PTR [r12]
	xor	esi, esi
	sub	rbx, rbp
	mov	rdi, rbp
	sub	r12, 8
	mov	QWORD PTR 8[r12], rax
	mov	rdx, rbx
	sar	rdx, 3
	call	_ZSt13__adjust_heapIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElS3_NS0_5__ops15_Iter_less_iterEEvT_T0_SC_T1_T2_.isra.0
	cmp	rbx, 8
	jg	.L101
.L94:
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	pop	rbp
	.cfi_def_cfa_offset 32
	pop	r12
	.cfi_def_cfa_offset 24
	pop	r13
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_def_cfa_offset 8
	ret
.L105:
	.cfi_restore_state
	mov	esi, DWORD PTR -8[r12]
	cmp	edx, esi
	je	.L117
	jl	.L139
.L118:
	cmp	ecx, esi
	je	.L121
.L144:
	jge	.L123
	mov	eax, DWORD PTR 0[rbp]
	mov	DWORD PTR 0[rbp], esi
.L145:
	mov	DWORD PTR -8[r12], eax
	mov	edx, DWORD PTR -4[r12]
	mov	eax, DWORD PTR 4[rbp]
	mov	DWORD PTR 4[rbp], edx
	mov	DWORD PTR -4[r12], eax
	mov	edx, DWORD PTR 0[rbp]
	jmp	.L112
.L121:
	mov	edi, DWORD PTR -4[r12]
	cmp	DWORD PTR 4[rax], edi
	jne	.L144
.L123:
	mov	edx, DWORD PTR 0[rbp]
	mov	DWORD PTR 0[rbp], ecx
	mov	ecx, DWORD PTR 4[rax]
	mov	DWORD PTR [rax], edx
	mov	edx, DWORD PTR 4[rbp]
	mov	DWORD PTR 4[rbp], ecx
	mov	DWORD PTR 4[rax], edx
	mov	edx, DWORD PTR 0[rbp]
	jmp	.L112
.L149:
	mov	esi, DWORD PTR 4[rax]
	cmp	DWORD PTR 12[rbp], esi
	je	.L105
	jge	.L105
	mov	edi, DWORD PTR -8[r12]
	cmp	edx, edi
	jne	.L106
	mov	r8d, DWORD PTR -4[r12]
	cmp	esi, r8d
	je	.L111
.L107:
	cmp	r8d, esi
	jle	.L111
	jmp	.L123
.L117:
	mov	r8d, DWORD PTR 12[rbp]
	cmp	r8d, DWORD PTR -4[r12]
	je	.L118
	jge	.L118
	jmp	.L116
.L113:
	mov	r8d, DWORD PTR 12[rbp]
	cmp	r8d, DWORD PTR -4[r12]
	je	.L116
	jge	.L116
.L114:
	mov	eax, DWORD PTR 0[rbp]
	mov	DWORD PTR 0[rbp], edi
	jmp	.L145
.L150:
	mov	esi, DWORD PTR 4[rax]
	mov	r8d, DWORD PTR -4[r12]
	cmp	r8d, esi
	jne	.L107
	cmp	edx, edi
	jl	.L114
	jmp	.L139
.L147:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	ret
	.cfi_endproc
.LFE19135:
	.size	_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElNS0_5__ops15_Iter_less_iterEEvT_SB_T0_T1_.isra.0, .-_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElNS0_5__ops15_Iter_less_iterEEvT_SB_T0_T1_.isra.0
	.section	.text._ZNSt12_Vector_baseIxSaIxEED2Ev,"axG",@progbits,_ZNSt12_Vector_baseIxSaIxEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt12_Vector_baseIxSaIxEED2Ev
	.type	_ZNSt12_Vector_baseIxSaIxEED2Ev, @function
_ZNSt12_Vector_baseIxSaIxEED2Ev:
.LFB16005:
	.cfi_startproc
	endbr64
	mov	rax, rdi
	mov	rdi, QWORD PTR [rdi]
	test	rdi, rdi
	je	.L152
	mov	rsi, QWORD PTR 16[rax]
	sub	rsi, rdi
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L152:
	ret
	.cfi_endproc
.LFE16005:
	.size	_ZNSt12_Vector_baseIxSaIxEED2Ev, .-_ZNSt12_Vector_baseIxSaIxEED2Ev
	.weak	_ZNSt12_Vector_baseIxSaIxEED1Ev
	.set	_ZNSt12_Vector_baseIxSaIxEED1Ev,_ZNSt12_Vector_baseIxSaIxEED2Ev
	.section	.rodata._ZNSt6vectorIxSaIxEEC2EmRKS0_.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"cannot create std::vector larger than max_size()"
	.section	.text._ZNSt6vectorIxSaIxEEC2EmRKS0_,"axG",@progbits,_ZNSt6vectorIxSaIxEEC5EmRKS0_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIxSaIxEEC2EmRKS0_
	.type	_ZNSt6vectorIxSaIxEEC2EmRKS0_, @function
_ZNSt6vectorIxSaIxEEC2EmRKS0_:
.LFB16028:
	.cfi_startproc
	endbr64
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	rax, rsi
	sub	rsp, 16
	.cfi_def_cfa_offset 32
	shr	rax, 60
	jne	.L162
	mov	rbx, rdi
	test	rsi, rsi
	je	.L163
	lea	rdx, 0[0+rsi*8]
	mov	QWORD PTR 8[rsp], rsi
	mov	rdi, rdx
	mov	QWORD PTR [rsp], rdx
	call	_Znwm@PLT
	mov	rdx, QWORD PTR [rsp]
	mov	QWORD PTR [rbx], rax
	lea	rcx, 8[rax]
	lea	r9, [rax+rdx]
	and	QWORD PTR [rax], 0
	mov	QWORD PTR 16[rbx], r9
	cmp	QWORD PTR 8[rsp], 1
	je	.L157
	mov	rdi, rcx
	sub	rdx, 8
	xor	esi, esi
	mov	QWORD PTR 8[rsp], r9
	mov	QWORD PTR [rsp], rax
	call	memset@PLT
	mov	r9, QWORD PTR 8[rsp]
	lea	rcx, -8[r9+rax]
	sub	rcx, QWORD PTR [rsp]
.L157:
	mov	QWORD PTR 8[rbx], rcx
	add	rsp, 16
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L163:
	.cfi_restore_state
	xor	ecx, ecx
	mov	QWORD PTR [rdi], 0
	mov	QWORD PTR 16[rdi], 0
	mov	QWORD PTR 8[rbx], rcx
	add	rsp, 16
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.L162:
	.cfi_restore_state
	lea	rdi, .LC0[rip]
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE16028:
	.size	_ZNSt6vectorIxSaIxEEC2EmRKS0_, .-_ZNSt6vectorIxSaIxEEC2EmRKS0_
	.weak	_ZNSt6vectorIxSaIxEEC1EmRKS0_
	.set	_ZNSt6vectorIxSaIxEEC1EmRKS0_,_ZNSt6vectorIxSaIxEEC2EmRKS0_
	.section	.text._ZNSt6vectorIS_IxSaIxEESaIS1_EED2Ev,"axG",@progbits,_ZNSt6vectorIS_IxSaIxEESaIS1_EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IxSaIxEESaIS1_EED2Ev
	.type	_ZNSt6vectorIS_IxSaIxEESaIS1_EED2Ev, @function
_ZNSt6vectorIS_IxSaIxEESaIS1_EED2Ev:
.LFB16039:
	.cfi_startproc
	endbr64
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	mov	r12, rdi
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbp, QWORD PTR 8[rdi]
	mov	rbx, QWORD PTR [rdi]
	cmp	rbp, rbx
	je	.L165
	.p2align 4
	.p2align 3
.L167:
	mov	rdi, QWORD PTR [rbx]
	test	rdi, rdi
	je	.L166
	mov	rsi, QWORD PTR 16[rbx]
	sub	rsi, rdi
	call	_ZdlPvm@PLT
.L166:
	add	rbx, 24
	cmp	rbp, rbx
	jne	.L167
	mov	rbx, QWORD PTR [r12]
.L165:
	test	rbx, rbx
	je	.L164
	mov	rsi, QWORD PTR 16[r12]
	mov	rdi, rbx
	sub	rsi, rbx
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L164:
	.cfi_restore_state
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE16039:
	.size	_ZNSt6vectorIS_IxSaIxEESaIS1_EED2Ev, .-_ZNSt6vectorIS_IxSaIxEESaIS1_EED2Ev
	.weak	_ZNSt6vectorIS_IxSaIxEESaIS1_EED1Ev
	.set	_ZNSt6vectorIS_IxSaIxEESaIS1_EED1Ev,_ZNSt6vectorIS_IxSaIxEESaIS1_EED2Ev
	.section	.text._ZNSt6vectorIS_IiSaIiEESaIS1_EED2Ev,"axG",@progbits,_ZNSt6vectorIS_IiSaIiEESaIS1_EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IiSaIiEESaIS1_EED2Ev
	.type	_ZNSt6vectorIS_IiSaIiEESaIS1_EED2Ev, @function
_ZNSt6vectorIS_IiSaIiEESaIS1_EED2Ev:
.LFB16051:
	.cfi_startproc
	endbr64
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	mov	r12, rdi
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbp, QWORD PTR 8[rdi]
	mov	rbx, QWORD PTR [rdi]
	cmp	rbp, rbx
	je	.L175
	.p2align 4
	.p2align 3
.L177:
	mov	rdi, QWORD PTR [rbx]
	test	rdi, rdi
	je	.L176
	mov	rsi, QWORD PTR 16[rbx]
	sub	rsi, rdi
	call	_ZdlPvm@PLT
.L176:
	add	rbx, 24
	cmp	rbp, rbx
	jne	.L177
	mov	rbx, QWORD PTR [r12]
.L175:
	test	rbx, rbx
	je	.L174
	mov	rsi, QWORD PTR 16[r12]
	mov	rdi, rbx
	sub	rsi, rbx
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L174:
	.cfi_restore_state
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE16051:
	.size	_ZNSt6vectorIS_IiSaIiEESaIS1_EED2Ev, .-_ZNSt6vectorIS_IiSaIiEESaIS1_EED2Ev
	.weak	_ZNSt6vectorIS_IiSaIiEESaIS1_EED1Ev
	.set	_ZNSt6vectorIS_IiSaIiEESaIS1_EED1Ev,_ZNSt6vectorIS_IiSaIiEESaIS1_EED2Ev
	.section	.rodata._ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx.str1.1,"aMS",@progbits,1
.LC1:
	.string	"vector::_M_fill_insert"
	.section	.text._ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx,"axG",@progbits,_ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx
	.type	_ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx, @function
_ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx:
.LFB16756:
	.cfi_startproc
	endbr64
	test	rdx, rdx
	je	.L245
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	mov	r8, rsi
	mov	r10, rsi
	mov	r9, rdi
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	mov	r14, rcx
	push	rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	push	rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	mov	rbx, rcx
	mov	rcx, rdx
	sub	rsp, 56
	.cfi_def_cfa_offset 96
	mov	rax, QWORD PTR 16[rdi]
	mov	rsi, QWORD PTR 8[rdi]
	mov	r15, rax
	sub	rax, rsi
	sar	rax, 3
	cmp	rax, rdx
	jb	.L187
	mov	rdi, rsi
	mov	r11, QWORD PTR [rbx]
	sub	rdi, r8
	mov	rdx, rdi
	sar	rdx, 3
	cmp	rcx, rdx
	jb	.L248
	mov	rax, rcx
	sub	rax, rdx
	je	.L209
	lea	rcx, -1[rax]
	xor	edx, edx
	test	al, 1
	je	.L197
	mov	QWORD PTR [rsi], r11
	mov	edx, 1
	cmp	rax, 1
	je	.L242
	.p2align 5
	.p2align 4
	.p2align 3
.L197:
	mov	QWORD PTR [rsi+rdx*8], r11
	mov	QWORD PTR 8[rsi+rdx*8], r11
	add	rdx, 2
	cmp	rax, rdx
	jne	.L197
.L242:
	lea	rcx, 8[rsi+rcx*8]
.L196:
	lea	rdx, [rcx+rdi]
	cmp	rsi, r8
	je	.L198
	mov	rdi, rsi
	xor	eax, eax
	sub	rdi, r8
	.p2align 5
	.p2align 4
	.p2align 3
.L199:
	mov	rbx, QWORD PTR [r8+rax]
	mov	QWORD PTR [rcx+rax], rbx
	add	rax, 8
	cmp	rdi, rax
	jne	.L199
	mov	rax, rsi
	mov	QWORD PTR 8[r9], rdx
	sub	rax, r8
	test	al, 8
	je	.L200
	lea	r10, 8[r8]
	mov	QWORD PTR [r8], r11
	cmp	rsi, r10
	je	.L184
	.p2align 4
	.p2align 4
	.p2align 3
.L200:
	mov	QWORD PTR [r10], r11
	add	r10, 16
	mov	QWORD PTR -8[r10], r11
	cmp	rsi, r10
	jne	.L200
	jmp	.L184
	.p2align 4,,10
	.p2align 3
.L245:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 14
	.cfi_restore 15
	ret
	.p2align 4,,10
	.p2align 3
.L248:
	.cfi_def_cfa_offset 96
	.cfi_offset 3, -40
	.cfi_offset 6, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	sal	rcx, 3
	mov	rdx, rsi
	xor	eax, eax
	sub	rdx, rcx
	cmp	rsi, rdx
	je	.L192
	.p2align 5
	.p2align 4
	.p2align 3
.L189:
	mov	rdi, QWORD PTR [rdx+rax]
	mov	QWORD PTR [rsi+rax], rdi
	add	rax, 8
	cmp	rcx, rax
	jne	.L189
.L192:
	sub	rdx, r8
	lea	rax, [rsi+rcx]
	mov	rdi, rdx
	mov	QWORD PTR 8[r9], rax
	sal	rdi, 61
	sub	rdi, rdx
	add	rdi, rsi
	cmp	rdx, 8
	jle	.L249
	mov	rsi, r8
	mov	QWORD PTR 32[rsp], r11
	mov	QWORD PTR 24[rsp], r10
	mov	QWORD PTR 16[rsp], rcx
	mov	QWORD PTR 8[rsp], r8
	call	memmove@PLT
	mov	r8, QWORD PTR 8[rsp]
	mov	rcx, QWORD PTR 16[rsp]
	mov	r10, QWORD PTR 24[rsp]
	mov	r11, QWORD PTR 32[rsp]
.L193:
	add	rcx, r8
	cmp	rcx, r8
	je	.L184
	mov	rax, rcx
	sub	rax, r8
	test	al, 8
	je	.L195
	lea	r10, 8[r8]
	mov	QWORD PTR [r8], r11
	cmp	rcx, r10
	je	.L184
	.p2align 4
	.p2align 4
	.p2align 3
.L195:
	mov	QWORD PTR [r10], r11
	add	r10, 16
	mov	QWORD PTR -8[r10], r11
	cmp	rcx, r10
	jne	.L195
	jmp	.L184
	.p2align 4,,10
	.p2align 3
.L187:
	movabs	rax, 1152921504606846975
	mov	r11, QWORD PTR [rdi]
	mov	rdx, rsi
	sub	rdx, r11
	sar	rdx, 3
	sub	rax, rdx
	cmp	rax, rcx
	jb	.L250
	mov	rbx, r8
	mov	rax, rdx
	mov	QWORD PTR 40[rsp], rdi
	sub	rbx, r11
	cmp	rcx, rdx
	mov	QWORD PTR 32[rsp], rsi
	cmovnb	rax, rcx
	mov	QWORD PTR 24[rsp], r8
	mov	QWORD PTR 16[rsp], r11
	add	rax, rdx
	mov	QWORD PTR 8[rsp], rcx
	movabs	rdx, 1152921504606846975
	cmp	rax, rdx
	cmova	rax, rdx
	lea	rdi, 0[0+rax*8]
	lea	rbp, 0[0+rax*8]
	call	_Znwm@PLT
	mov	rcx, QWORD PTR 8[rsp]
	mov	r11, QWORD PTR 16[rsp]
	lea	rdx, [rax+rbx]
	mov	r10, rax
	mov	r8, QWORD PTR 24[rsp]
	mov	rax, QWORD PTR [r14]
	sal	rcx, 3
	mov	rsi, QWORD PTR 32[rsp]
	mov	r9, QWORD PTR 40[rsp]
	test	cl, 8
	lea	rdi, [rdx+rcx]
	je	.L202
	mov	QWORD PTR [rdx], rax
	add	rdx, 8
	cmp	rdx, rdi
	je	.L243
	.p2align 4
	.p2align 4
	.p2align 3
.L202:
	mov	QWORD PTR [rdx], rax
	add	rdx, 16
	mov	QWORD PTR -8[rdx], rax
	cmp	rdx, rdi
	jne	.L202
.L243:
	cmp	r11, r8
	je	.L203
	mov	rdi, r8
	xor	eax, eax
	sub	rdi, r11
	.p2align 5
	.p2align 4
	.p2align 3
.L204:
	mov	rdx, QWORD PTR [r11+rax]
	mov	QWORD PTR [r10+rax], rdx
	add	rax, 8
	cmp	rax, rdi
	jne	.L204
	add	rax, r10
	add	rcx, rax
	cmp	rsi, r8
	je	.L205
	sub	rsi, r8
	mov	rdi, rcx
	mov	QWORD PTR 32[rsp], r9
	mov	rdx, rsi
	mov	QWORD PTR 8[rsp], rsi
	mov	rsi, r8
	mov	QWORD PTR 24[rsp], r10
	mov	QWORD PTR 16[rsp], r11
	call	memcpy@PLT
	mov	rdx, QWORD PTR 8[rsp]
	mov	r11, QWORD PTR 16[rsp]
	mov	r10, QWORD PTR 24[rsp]
	mov	r9, QWORD PTR 32[rsp]
	lea	rcx, [rax+rdx]
.L205:
	mov	rsi, r15
	mov	rdi, r11
	mov	QWORD PTR 24[rsp], r9
	sub	rsi, r11
	mov	QWORD PTR 16[rsp], r10
	mov	QWORD PTR 8[rsp], rcx
	call	_ZdlPvm@PLT
	mov	r9, QWORD PTR 24[rsp]
	mov	r10, QWORD PTR 16[rsp]
	mov	rcx, QWORD PTR 8[rsp]
.L207:
	mov	QWORD PTR [r9], r10
	add	r10, rbp
	mov	QWORD PTR 8[r9], rcx
	mov	QWORD PTR 16[r9], r10
.L184:
	add	rsp, 56
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	pop	rbx
	.cfi_def_cfa_offset 32
	pop	rbp
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L209:
	.cfi_restore_state
	mov	rcx, rsi
	jmp	.L196
	.p2align 4,,10
	.p2align 3
.L198:
	mov	QWORD PTR 8[r9], rdx
	jmp	.L184
	.p2align 4,,10
	.p2align 3
.L203:
	add	rcx, r10
	cmp	rsi, r11
	je	.L206
	sub	rsi, r11
	mov	rdi, rcx
	mov	QWORD PTR 32[rsp], r9
	mov	rdx, rsi
	mov	QWORD PTR 16[rsp], rsi
	mov	rsi, r11
	mov	QWORD PTR 24[rsp], r10
	mov	QWORD PTR 8[rsp], r11
	call	memcpy@PLT
	mov	rdx, QWORD PTR 16[rsp]
	mov	r9, QWORD PTR 32[rsp]
	mov	r10, QWORD PTR 24[rsp]
	mov	r11, QWORD PTR 8[rsp]
	lea	rcx, [rax+rdx]
.L206:
	test	r11, r11
	je	.L207
	jmp	.L205
	.p2align 4,,10
	.p2align 3
.L249:
	jne	.L193
	mov	rax, QWORD PTR [r8]
	mov	QWORD PTR [rdi], rax
	jmp	.L193
.L250:
	lea	rdi, .LC1[rip]
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE16756:
	.size	_ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx, .-_ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx
	.section	.text._ZN8mathbase4initIiEEDaT_,"axG",@progbits,_ZN8mathbase4initIiEEDaT_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8mathbase4initIiEEDaT_
	.type	_ZN8mathbase4initIiEEDaT_, @function
_ZN8mathbase4initIiEEDaT_:
.LFB14982:
	.cfi_startproc
	endbr64
	push	r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	push	r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	mov	r12, rdi
	push	rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	push	rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movsx	rbx, esi
	sub	rsp, 24
	.cfi_def_cfa_offset 64
	mov	rsi, QWORD PTR 8[rdi]
	mov	rdx, QWORD PTR [rdi]
	mov	rbp, QWORD PTR fs:40
	mov	QWORD PTR 8[rsp], rbp
	mov	rbp, rbx
	mov	QWORD PTR [rsp], 1
	mov	rax, rsi
	sub	rax, rdx
	sar	rax, 3
	cmp	rax, rbx
	jb	.L271
	cmp	rbx, rax
	jb	.L272
.L253:
	cmp	ebp, 1
	jle	.L254
	mov	rdi, QWORD PTR [r12]
	mov	r9d, ebp
	mov	ecx, 1
	movabs	r8, 155014655926305585
	mov	rdx, QWORD PTR [rdi]
	.p2align 6
	.p2align 4
	.p2align 3
.L255:
	mov	rsi, rdx
	imul	rsi, rcx
	mov	rax, rsi
	imul	r8
	mov	rax, rsi
	sar	rax, 63
	sar	rdx, 23
	sub	rdx, rax
	imul	rax, rdx, 998244353
	sub	rsi, rax
	mov	QWORD PTR [rdi+rcx*8], rsi
	add	rcx, 1
	mov	rdx, rsi
	cmp	rcx, r9
	jne	.L255
.L254:
	lea	rdi, 24[r12]
	mov	rsi, r12
	lea	r13d, -1[rbp]
	call	_ZNSt6vectorIxSaIxEEaSERKS1_.isra.0
	mov	rax, QWORD PTR [r12]
	movsx	r13, r13d
	mov	r9d, 30
	mov	edi, 1
	mov	r8d, 998244351
	movabs	r11, 155014655926305585
	movabs	r10, -8525806094425994177
	mov	rcx, QWORD PTR [rax+r13*8]
	.p2align 4
	.p2align 3
.L257:
	test	r8b, 1
	je	.L256
	imul	rdi, rcx
	mov	rax, rdi
	mov	rsi, rdi
	imul	r11
	mov	rax, rdi
	sar	rax, 63
	sar	rdx, 23
	mov	rdi, rdx
	sub	rdi, rax
	imul	rax, rdi, 998244353
	mov	rdi, rsi
	sub	rdi, rax
.L256:
	imul	rcx, rcx
	sar	r8d
	mov	rax, rcx
	mov	rsi, rcx
	mul	r10
	mov	rcx, rdx
	shr	rcx, 29
	imul	rax, rcx, 998244353
	mov	rcx, rsi
	sub	rcx, rax
	sub	r9d, 1
	jne	.L257
	mov	r8, QWORD PTR 24[r12]
	mov	QWORD PTR [r8+r13*8], rdi
	cmp	ebp, 1
	je	.L251
	lea	rcx, -1[rbx]
	lea	eax, -2[rbp]
	sub	rbx, 2
	movabs	rdi, 155014655926305585
	mov	rdx, QWORD PTR [r8+rcx*8]
	sub	rbx, rax
	.p2align 6
	.p2align 4
	.p2align 3
.L259:
	mov	rsi, rdx
	imul	rsi, rcx
	mov	rax, rsi
	imul	rdi
	mov	rax, rsi
	sar	rax, 63
	sar	rdx, 23
	sub	rdx, rax
	imul	rax, rdx, 998244353
	sub	rsi, rax
	mov	QWORD PTR -8[r8+rcx*8], rsi
	sub	rcx, 1
	mov	rdx, rsi
	cmp	rcx, rbx
	jne	.L259
.L251:
	mov	rax, QWORD PTR 8[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L273
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	pop	rbx
	.cfi_def_cfa_offset 32
	pop	rbp
	.cfi_def_cfa_offset 24
	pop	r12
	.cfi_def_cfa_offset 16
	pop	r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L272:
	.cfi_restore_state
	lea	rax, [rdx+rbx*8]
	cmp	rsi, rax
	je	.L253
	mov	QWORD PTR 8[rdi], rax
	jmp	.L253
	.p2align 4,,10
	.p2align 3
.L271:
	mov	rdx, rbx
	mov	rcx, rsp
	sub	rdx, rax
	call	_ZNSt6vectorIxSaIxEE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPxS1_EEmRKx
	jmp	.L253
.L273:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE14982:
	.size	_ZN8mathbase4initIiEEDaT_, .-_ZN8mathbase4initIiEEDaT_
	.section	.text._ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev,"axG",@progbits,_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev
	.type	_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev, @function
_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev:
.LFB16787:
	.cfi_startproc
	endbr64
	mov	rax, rdi
	mov	rdi, QWORD PTR [rdi]
	test	rdi, rdi
	je	.L274
	mov	rsi, QWORD PTR 16[rax]
	sub	rsi, rdi
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L274:
	ret
	.cfi_endproc
.LFE16787:
	.size	_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev, .-_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev
	.weak	_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED1Ev
	.set	_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED1Ev,_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev
	.section	.text._ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED2Ev,"axG",@progbits,_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED2Ev
	.type	_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED2Ev, @function
_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED2Ev:
.LFB17412:
	.cfi_startproc
	endbr64
	mov	rax, QWORD PTR 8[rdi]
	test	rax, rax
	jne	.L291
	ret
	.p2align 4,,10
	.p2align 3
.L291:
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	sub	rsp, 16
	.cfi_def_cfa_offset 32
	mov	rcx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rdi]
	mov	rbx, rcx
	cmp	rcx, rax
	je	.L276
	.p2align 4
	.p2align 3
.L279:
	mov	rdi, QWORD PTR [rax]
	test	rdi, rdi
	je	.L278
	mov	rsi, QWORD PTR 16[rax]
	mov	QWORD PTR 8[rsp], rax
	sub	rsi, rdi
	call	_ZdlPvm@PLT
	mov	rax, QWORD PTR 8[rsp]
.L278:
	add	rax, 24
	cmp	rbx, rax
	jne	.L279
.L276:
	add	rsp, 16
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE17412:
	.size	_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED2Ev, .-_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED2Ev
	.weak	_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED1Ev
	.set	_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED1Ev,_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED2Ev
	.section	.text._ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_,"axG",@progbits,_ZNSt6vectorIS_IxSaIxEESaIS1_EEC5EmRKS1_RKS2_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_
	.type	_ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_, @function
_ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_:
.LFB16036:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA16036
	endbr64
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 56
	.cfi_def_cfa_offset 112
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 40[rsp], rax
	movabs	rax, 384307168202282325
	cmp	rax, rsi
	jb	.L313
	mov	r13, rdi
	test	rsi, rsi
	je	.L295
	lea	r12, [rsi+rsi*2]
	mov	r15, rdx
	lea	rdi, 0[0+r12*8]
.LEHB0:
	call	_Znwm@PLT
.LEHE0:
	mov	r14, QWORD PTR [r15]
	movq	xmm0, rax
	lea	r12, [rax+r12*8]
	mov	QWORD PTR 8[rsp], rax
	mov	rbx, rax
	mov	QWORD PTR 16[rsp], rax
	punpcklqdq	xmm0, xmm0
	lea	rax, 8[rsp]
	mov	QWORD PTR 16[r13], r12
	mov	QWORD PTR 24[rsp], rax
	movups	XMMWORD PTR 0[r13], xmm0
	jmp	.L298
	.p2align 4,,10
	.p2align 3
.L314:
	mov	rdi, rbp
.LEHB1:
	call	_Znwm@PLT
.LEHE1:
	mov	rcx, rax
.L296:
	movq	xmm0, rcx
	add	rbp, rcx
	punpcklqdq	xmm0, xmm0
	mov	QWORD PTR 16[rbx], rbp
	movups	XMMWORD PTR [rbx], xmm0
	mov	r14, QWORD PTR [r15]
	mov	rbp, QWORD PTR 8[r15]
	sub	rbp, r14
	test	rbp, rbp
	jle	.L297
	mov	rdi, rcx
	mov	rdx, rbp
	mov	rsi, r14
	call	memcpy@PLT
	lea	rcx, [rax+rbp]
.L297:
	mov	QWORD PTR 8[rbx], rcx
	add	rbx, 24
	mov	QWORD PTR 8[rsp], rbx
	cmp	rbx, r12
	je	.L302
.L298:
	pxor	xmm1, xmm1
	mov	QWORD PTR 16[rbx], 0
	movups	XMMWORD PTR [rbx], xmm1
	mov	rbp, QWORD PTR 8[r15]
	sub	rbp, r14
	jne	.L314
	xor	ecx, ecx
	jmp	.L296
	.p2align 4,,10
	.p2align 3
.L295:
	mov	QWORD PTR [rdi], 0
	xor	r12d, r12d
	mov	QWORD PTR 16[rdi], 0
	.p2align 4
	.p2align 3
.L302:
	mov	QWORD PTR 8[r13], r12
	mov	rax, QWORD PTR 40[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L310
	add	rsp, 56
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
.L299:
	.cfi_restore_state
	lea	rdi, 16[rsp]
	call	_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED1Ev
	mov	rdi, QWORD PTR 0[r13]
	test	rdi, rdi
	je	.L300
	mov	rsi, QWORD PTR 16[r13]
	sub	rsi, rdi
	call	_ZdlPvm@PLT
.L300:
	mov	rax, QWORD PTR 40[rsp]
	sub	rax, QWORD PTR fs:40
	je	.L301
.L310:
	call	__stack_chk_fail@PLT
.L313:
	mov	rax, QWORD PTR 40[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L310
	lea	rdi, .LC0[rip]
.LEHB2:
	call	_ZSt20__throw_length_errorPKc@PLT
.L305:
	endbr64
	mov	rbx, rax
	jmp	.L299
.L301:
	mov	rdi, rbx
	call	_Unwind_Resume@PLT
.LEHE2:
	.cfi_endproc
.LFE16036:
	.section	.gcc_except_table._ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_,"aG",@progbits,_ZNSt6vectorIS_IxSaIxEESaIS1_EEC5EmRKS1_RKS2_,comdat
.LLSDA16036:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE16036-.LLSDACSB16036
.LLSDACSB16036:
	.uleb128 .LEHB0-.LFB16036
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB16036
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L305-.LFB16036
	.uleb128 0
	.uleb128 .LEHB2-.LFB16036
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE16036:
	.section	.text._ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_,"axG",@progbits,_ZNSt6vectorIS_IxSaIxEESaIS1_EEC5EmRKS1_RKS2_,comdat
	.size	_ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_, .-_ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_
	.weak	_ZNSt6vectorIS_IxSaIxEESaIS1_EEC1EmRKS1_RKS2_
	.set	_ZNSt6vectorIS_IxSaIxEESaIS1_EEC1EmRKS1_RKS2_,_ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"vector::_M_realloc_append"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB6:
	.section	.text.startup,"ax",@progbits
.LHOTB6:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB14981:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA14981
	endbr64
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 328
	.cfi_def_cfa_offset 384
	mov	rdi, QWORD PTR fs:40
	mov	QWORD PTR 312[rsp], rdi
	xor	edi, edi
.LEHB3:
	call	_ZNSt8ios_base15sync_with_stdioEb@PLT
	lea	rsi, 192[rsp]
	lea	rdi, _ZSt3cin[rip]
	mov	QWORD PTR _ZSt3cin[rip+232], 0
	call	_ZNSirsERi@PLT
	lea	rsi, 196[rsp]
	lea	rdi, _ZSt3cin[rip]
	call	_ZNSirsERi@PLT
	lea	rsi, 200[rsp]
	mov	rdi, rax
	call	_ZNSirsERi@PLT
	lea	rsi, 204[rsp]
	mov	rdi, rax
	call	_ZNSirsERi@PLT
	mov	esi, DWORD PTR 200[rsp]
	add	esi, DWORD PTR 196[rsp]
	lea	rdi, math[rip]
	add	esi, 7
	call	_ZN8mathbase4initIiEEDaT_
	movsx	r12, DWORD PTR 204[rsp]
	mov	rax, r12
	shr	rax, 60
	jne	.L526
	test	r12, r12
	je	.L440
	sal	r12, 3
	mov	rdi, r12
	call	_Znwm@PLT
.LEHE3:
	lea	rbx, [rax+r12]
	mov	QWORD PTR 8[rsp], rax
	mov	rdx, rbx
	mov	QWORD PTR 64[rsp], rbx
	sub	rdx, rax
	and	dl, 8
	je	.L319
	mov	rax, QWORD PTR 8[rsp]
	xor	edx, edx
	mov	QWORD PTR [rax], rdx
	add	rax, 8
	cmp	rax, rbx
	je	.L537
.L319:
	mov	QWORD PTR [rax], 0
	add	rax, 16
	mov	QWORD PTR -8[rax], 0
	cmp	rax, rbx
	jne	.L319
.L537:
	mov	rax, QWORD PTR 8[rsp]
	mov	rbp, rbx
	mov	r14, rax
	cmp	rax, rbx
	je	.L318
.L321:
	mov	rsi, r14
	lea	rdi, _ZSt3cin[rip]
.LEHB4:
	call	_ZNSirsERi@PLT
	lea	rsi, 4[r14]
	mov	rdi, rax
	call	_ZNSirsERi@PLT
	add	r14, 8
	cmp	rbx, r14
	jne	.L321
	mov	rdx, r12
	mov	r14, r12
	sar	rdx, 3
.L437:
	test	rdx, rdx
	mov	eax, 1
	cmovne	rax, rdx
	add	rax, rdx
	movabs	rdx, 1152921504606846975
	cmp	rax, rdx
	cmova	rax, rdx
	lea	rbx, 0[0+rax*8]
	mov	rdi, rbx
	call	_Znwm@PLT
	mov	r13, rax
	mov	rsi, QWORD PTR 8[rsp]
	mov	rax, QWORD PTR .LC2[rip]
	mov	QWORD PTR 0[r13+r14], rax
	cmp	rbp, rsi
	je	.L441
	sub	rbp, rsi
	mov	rdi, r13
	mov	rdx, rbp
	add	rbp, r13
	call	memcpy@PLT
.L324:
	mov	rax, QWORD PTR 8[rsp]
	add	rbp, 8
	test	rax, rax
	je	.L325
	mov	rsi, r12
	mov	rdi, rax
	call	_ZdlPvm@PLT
.L325:
	lea	rax, 0[r13+rbx]
	mov	QWORD PTR 8[rsp], r13
	mov	QWORD PTR 64[rsp], rax
	cmp	rax, rbp
	je	.L326
	movd	xmm0, DWORD PTR 196[rsp]
	add	rbp, 8
	movd	xmm2, DWORD PTR 200[rsp]
	punpckldq	xmm0, xmm2
	movq	QWORD PTR -8[rbp], xmm0
.L327:
	cmp	QWORD PTR 8[rsp], rbp
	je	.L349
	mov	r14, QWORD PTR 8[rsp]
	mov	rbx, rbp
	mov	rsi, rbp
	sub	rbx, r14
	mov	rdi, r14
	mov	rax, rbx
	sar	rax, 3
	bsr	rdx, rax
	xor	rdx, 63
	test	rax, rax
	mov	eax, 64
	cmovne	eax, edx
	mov	edx, 63
	sub	edx, eax
	movsx	rdx, edx
	add	rdx, rdx
	call	_ZSt16__introsort_loopIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEElNS0_5__ops15_Iter_less_iterEEvT_SB_T0_T1_.isra.0
	cmp	rbx, 128
	jle	.L336
	lea	rbx, 128[r14]
	mov	rdi, r14
	mov	rsi, rbx
	call	_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEENS0_5__ops15_Iter_less_iterEEvT_SB_T0_.isra.0
	mov	rax, rbx
	cmp	rbx, rbp
	jne	.L344
	jmp	.L338
	.p2align 4,,10
	.p2align 3
.L340:
	jg	.L546
.L342:
	add	rax, 8
	movq	QWORD PTR [rdx], xmm0
	cmp	rax, rbp
	je	.L338
.L344:
	movq	xmm0, QWORD PTR [rax]
	mov	rdx, rax
	pshufd	xmm4, xmm0, 0xe5
	movd	edi, xmm0
	movd	r8d, xmm4
.L339:
	mov	esi, DWORD PTR -8[rdx]
	cmp	esi, edi
	jne	.L340
	mov	ecx, DWORD PTR -4[rdx]
	cmp	ecx, r8d
	je	.L342
	jle	.L342
.L343:
	mov	DWORD PTR [rdx], esi
	sub	rdx, 8
	mov	DWORD PTR 12[rdx], ecx
	jmp	.L339
.L440:
	xor	ecx, ecx
	xor	ebp, ebp
	mov	QWORD PTR 64[rsp], rcx
.L318:
	mov	QWORD PTR 8[rsp], rbp
	xor	r14d, r14d
	xor	edx, edx
	jmp	.L437
	.p2align 4,,10
	.p2align 3
.L546:
	mov	ecx, DWORD PTR -4[rdx]
	jmp	.L343
.L336:
	mov	rdi, QWORD PTR 8[rsp]
	mov	rsi, rbp
	call	_ZSt16__insertion_sortIN9__gnu_cxx17__normal_iteratorIPSt4pairIiiESt6vectorIS3_SaIS3_EEEENS0_5__ops15_Iter_less_iterEEvT_SB_T0_.isra.0
.L338:
	mov	rbx, QWORD PTR 8[rsp]
	mov	rax, rbp
	sub	rax, rbx
	mov	rcx, rbx
	cmp	rax, 8
	je	.L443
	sub	rax, 8
	pcmpeqd	xmm1, xmm1
	shr	rax, 3
	add	rax, 1
	mov	rdx, rax
	shr	rdx
	sal	rdx, 4
	add	rdx, rbx
.L347:
	movdqu	xmm0, XMMWORD PTR [rcx]
	add	rcx, 16
	paddd	xmm0, xmm1
	movups	XMMWORD PTR -16[rcx], xmm0
	cmp	rdx, rcx
	jne	.L347
	test	al, 1
	je	.L349
	mov	rbx, QWORD PTR 8[rsp]
	and	rax, -2
	lea	rax, [rbx+rax*8]
.L346:
	movq	xmm1, QWORD PTR .LC4[rip]
	movq	xmm0, QWORD PTR [rax]
	paddd	xmm0, xmm1
	movq	QWORD PTR [rax], xmm0
.L349:
	mov	eax, DWORD PTR 192[rsp]
	test	al, 1
	jne	.L547
.L334:
	test	al, 2
	jne	.L531
	lea	rax, 256[rsp]
	mov	QWORD PTR 40[rsp], rax
.L357:
	mov	rax, QWORD PTR 8[rsp]
	mov	rdi, QWORD PTR 40[rsp]
	mov	QWORD PTR 264[rsp], rbp
	mov	QWORD PTR 256[rsp], rax
	mov	rax, QWORD PTR 64[rsp]
	mov	QWORD PTR 272[rsp], rax
	call	_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev
	mov	rax, QWORD PTR 312[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L548
	add	rsp, 328
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xor	eax, eax
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
.L443:
	.cfi_restore_state
	mov	rax, QWORD PTR 8[rsp]
	jmp	.L346
.L326:
	movabs	rax, 1152921504606846975
	mov	r13, QWORD PTR 64[rsp]
	sub	r13, QWORD PTR 8[rsp]
	mov	rdx, r13
	sar	rdx, 3
	cmp	rdx, rax
	je	.L527
	test	rdx, rdx
	mov	eax, 1
	cmovne	rax, rdx
	add	rax, rdx
	movabs	rdx, 1152921504606846975
	cmp	rax, rdx
	cmova	rax, rdx
	lea	rbx, 0[0+rax*8]
	mov	rdi, rbx
	call	_Znwm@PLT
	movd	xmm0, DWORD PTR 196[rsp]
	mov	r12, rax
	movd	xmm3, DWORD PTR 200[rsp]
	punpckldq	xmm0, xmm3
	movq	QWORD PTR [rax+r13], xmm0
	cmp	QWORD PTR 8[rsp], rbp
	je	.L549
	mov	rsi, QWORD PTR 8[rsp]
	mov	rdi, rax
	sub	rbp, rsi
	mov	rdx, rbp
	lea	rbp, 8[r12+rbp]
	call	memcpy@PLT
.L331:
	mov	rsi, QWORD PTR 64[rsp]
	mov	rdi, QWORD PTR 8[rsp]
	sub	rsi, rdi
	call	_ZdlPvm@PLT
	lea	rax, [r12+rbx]
	mov	QWORD PTR 8[rsp], r12
	mov	QWORD PTR 64[rsp], rax
	jmp	.L327
.L531:
	movsx	rax, DWORD PTR 200[rsp]
	movabs	rdx, 384307168202282325
	cmp	rdx, rax
	jb	.L528
	test	rax, rax
	je	.L360
	imul	r12, rax, 24
	mov	rdi, r12
	call	_Znwm@PLT
.LEHE4:
	mov	rbx, rax
	mov	QWORD PTR 224[rsp], rax
	lea	rax, [rax+r12]
	pxor	xmm0, xmm0
	mov	QWORD PTR 240[rsp], rax
	mov	rdx, rbx
.L361:
	mov	QWORD PTR 16[rdx], 0
	add	rdx, 24
	movups	XMMWORD PTR -24[rdx], xmm0
	cmp	rax, rdx
	jne	.L361
.L436:
	mov	QWORD PTR 232[rsp], rax
	mov	rax, QWORD PTR 8[rsp]
	mov	r14, rax
	cmp	rax, rbp
	jne	.L370
	jmp	.L371
	.p2align 6
	.p2align 4,,10
	.p2align 3
.L550:
	mov	eax, DWORD PTR [r14]
	add	r15, 4
	add	r14, 8
	mov	DWORD PTR -4[r15], eax
	mov	QWORD PTR 8[r13], r15
	cmp	rbp, r14
	je	.L371
.L370:
	movsx	rax, DWORD PTR 4[r14]
	lea	rax, [rax+rax*2]
	lea	r13, [rbx+rax*8]
	mov	rax, QWORD PTR 16[r13]
	mov	r15, QWORD PTR 8[r13]
	mov	QWORD PTR [rsp], rax
	cmp	r15, rax
	jne	.L550
	movabs	rsi, 2305843009213693951
	mov	r9, QWORD PTR 0[r13]
	sub	r15, r9
	mov	rax, r15
	sar	rax, 2
	cmp	rax, rsi
	je	.L529
	test	rax, rax
	mov	r12d, 1
	mov	QWORD PTR 24[rsp], r9
	cmovne	r12, rax
	add	r12, rax
	movabs	rax, 2305843009213693951
	cmp	r12, rax
	cmova	r12, rax
	lea	rax, 0[0+r12*4]
	mov	rdi, rax
	mov	QWORD PTR 16[rsp], rax
.LEHB5:
	call	_Znwm@PLT
	mov	r12, rax
	mov	eax, DWORD PTR [r14]
	test	r15, r15
	mov	r9, QWORD PTR 24[rsp]
	mov	DWORD PTR [r12+r15], eax
	je	.L368
	mov	rsi, r9
	mov	rdx, r15
	mov	rdi, r12
	call	memcpy@PLT
	mov	r9, QWORD PTR 24[rsp]
.L368:
	lea	r15, 4[r12+r15]
	test	r9, r9
	je	.L369
	mov	rsi, QWORD PTR [rsp]
	mov	rdi, r9
	sub	rsi, r9
	call	_ZdlPvm@PLT
.L369:
	mov	r10, QWORD PTR 16[rsp]
	add	r14, 8
	mov	QWORD PTR 0[r13], r12
	mov	QWORD PTR 8[r13], r15
	add	r10, r12
	mov	QWORD PTR 16[r13], r10
	cmp	rbp, r14
	jne	.L370
.L371:
	lea	rax, 288[rsp]
	movsx	rsi, DWORD PTR 196[rsp]
	lea	rdx, 208[rsp]
	mov	rdi, rax
	mov	QWORD PTR 128[rsp], rdx
	mov	QWORD PTR 56[rsp], rax
	call	_ZNSt6vectorIxSaIxEEC1EmRKS0_
.LEHE5:
	mov	r14, QWORD PTR 56[rsp]
	lea	rax, 256[rsp]
	xor	r9d, r9d
	movsx	rsi, DWORD PTR 196[rsp]
	lea	rcx, 216[rsp]
	mov	rdi, rax
	mov	QWORD PTR 40[rsp], rax
	mov	rdx, r14
	mov	QWORD PTR 256[rsp], r9
	mov	QWORD PTR 96[rsp], rcx
.LEHB6:
	call	_ZNSt6vectorIS_IxSaIxEESaIS1_EEC1EmRKS1_RKS2_
.LEHE6:
	mov	rax, QWORD PTR 256[rsp]
	mov	rdi, r14
	mov	QWORD PTR 32[rsp], rax
	call	_ZNSt12_Vector_baseIxSaIxEED2Ev
	mov	rax, QWORD PTR 8[rbx]
	mov	r13d, DWORD PTR 196[rsp]
	mov	ecx, DWORD PTR -4[rax]
	cmp	ecx, r13d
	jge	.L376
	mov	rax, QWORD PTR 32[rsp]
	mov	edx, r13d
	movsx	rdi, ecx
	sub	edx, ecx
	mov	rsi, QWORD PTR [rax]
	add	rdx, rdi
	lea	rdx, [rsi+rdx*8]
	lea	rax, [rsi+rdi*8]
	mov	rcx, rdx
	sub	rcx, rax
	and	cl, 8
	je	.L375
	mov	QWORD PTR [rax], 1
	add	rax, 8
	cmp	rax, rdx
	je	.L376
.L375:
	mov	QWORD PTR [rax], 1
	add	rax, 16
	mov	QWORD PTR -8[rax], 1
	cmp	rax, rdx
	jne	.L375
.L376:
	cmp	DWORD PTR 200[rsp], 1
	jle	.L551
	mov	rax, QWORD PTR 264[rsp]
	xor	edi, edi
	mov	DWORD PTR 80[rsp], 1
	xor	r12d, r12d
	mov	QWORD PTR 72[rsp], rdi
	mov	QWORD PTR 48[rsp], rax
	sub	rax, QWORD PTR 32[rsp]
	mov	QWORD PTR 24[rsp], rax
	lea	rax, 24[rbx]
	xor	ebx, ebx
	mov	QWORD PTR 88[rsp], rax
.L413:
	mov	rax, QWORD PTR 72[rsp]
	mov	rsi, QWORD PTR 24[rsp]
	sub	rax, r12
	mov	r14, rax
	cmp	rax, rsi
	jb	.L552
	mov	r15, rbx
	sub	r15, r12
	cmp	r15, QWORD PTR 24[rsp]
	jb	.L393
	mov	rax, QWORD PTR 32[rsp]
	cmp	QWORD PTR 48[rsp], rax
	je	.L394
	mov	r13, rax
	mov	r15, r12
.L395:
	mov	rsi, r13
	mov	rdi, r15
.LEHB7:
	call	_ZNSt6vectorIxSaIxEEaSERKS1_.isra.0
.LEHE7:
	add	r15, 24
	add	r13, 24
	cmp	QWORD PTR 48[rsp], r13
	jne	.L395
	cmp	rbx, r15
	je	.L396
.L398:
	mov	rdi, QWORD PTR [r15]
	test	rdi, rdi
	je	.L397
	mov	rsi, QWORD PTR 16[r15]
	sub	rsi, rdi
	call	_ZdlPvm@PLT
.L397:
	add	r15, 24
	cmp	rbx, r15
	jne	.L398
.L402:
	mov	rax, QWORD PTR 24[rsp]
	lea	rbx, [r12+rax]
.L392:
	mov	rsi, QWORD PTR 32[rsp]
	cmp	QWORD PTR 48[rsp], rsi
	jne	.L408
.L545:
	mov	r13d, DWORD PTR 196[rsp]
.L435:
	mov	ecx, DWORD PTR 200[rsp]
	test	r13d, r13d
	jle	.L427
	lea	eax, -1[rcx]
	cmp	eax, DWORD PTR 80[rsp]
	lea	eax, -1[r13]
	mov	r15, r12
	mov	DWORD PTR 136[rsp], eax
	movsx	r9, r13d
	mov	esi, 1
	mov	DWORD PTR 140[rsp], ecx
	sete	BYTE PTR 108[rsp]
	xor	ecx, ecx
.L426:
	cmp	r13d, esi
	jle	.L414
	mov	rdi, QWORD PTR 32[rsp]
	lea	rax, [rcx+rcx*2]
	mov	DWORD PTR 112[rsp], ecx
	mov	r8d, esi
	mov	QWORD PTR 144[rsp], rbp
	lea	r14, 0[0+rsi*8]
	lea	rax, [rdi+rax*8]
	mov	QWORD PTR 152[rsp], r12
	mov	edi, ecx
	mov	QWORD PTR 160[rsp], rbx
	mov	QWORD PTR 168[rsp], rsi
	mov	QWORD PTR 176[rsp], r9
	mov	QWORD PTR 120[rsp], rax
	mov	rax, QWORD PTR 88[rsp]
.L415:
	xor	r9d, r9d
	cmp	DWORD PTR 136[rsp], r8d
	mov	r12, QWORD PTR 120[rsp]
	sete	r9b
	and	r9d, DWORD PTR 108[rsp]
	lea	r10d, [r9+r8]
	mov	r9d, DWORD PTR 112[rsp]
	cmp	r10d, ecx
	jle	.L422
	mov	DWORD PTR 16[rsp], r10d
	mov	QWORD PTR 184[rsp], rcx
	.p2align 4
	.p2align 3
.L425:
	cmp	r8d, r13d
	jge	.L424
	mov	QWORD PTR [rsp], rax
	mov	rbx, QWORD PTR [rax]
	mov	r11, r14
	mov	esi, r8d
	mov	rcx, QWORD PTR 8[rax]
	.p2align 4
	.p2align 3
.L421:
	cmp	rcx, rbx
	je	.L416
	mov	rdx, rbx
	mov	ebp, 1
	.p2align 4
	.p2align 3
.L419:
	mov	eax, DWORD PTR [rdx]
	cmp	edi, eax
	jg	.L461
	cmp	eax, r9d
	jle	.L417
.L461:
	cmp	esi, eax
	setge	r10b
	cmp	r8d, eax
	setle	al
	and	eax, r10d
	and	ebp, eax
.L417:
	add	rdx, 4
	cmp	rdx, rcx
	jne	.L419
	test	bpl, bpl
	jne	.L416
.L420:
	add	esi, 1
	add	r11, 8
	cmp	esi, r13d
	jne	.L421
	mov	rax, QWORD PTR [rsp]
.L424:
	add	r9d, 1
	add	r12, 24
	cmp	DWORD PTR 16[rsp], r9d
	jne	.L425
	mov	rcx, QWORD PTR 184[rsp]
.L422:
	add	r8d, 1
	add	r14, 8
	cmp	r8d, r13d
	jne	.L415
	mov	rbp, QWORD PTR 144[rsp]
	mov	r12, QWORD PTR 152[rsp]
	mov	rbx, QWORD PTR 160[rsp]
	mov	rsi, QWORD PTR 168[rsp]
	mov	r9, QWORD PTR 176[rsp]
.L414:
	add	rcx, 1
	add	rsi, 1
	add	r15, 24
	cmp	rcx, r9
	jne	.L426
	mov	ecx, DWORD PTR 140[rsp]
.L427:
	add	DWORD PTR 80[rsp], 1
	mov	eax, DWORD PTR 80[rsp]
	add	QWORD PTR 88[rsp], 24
	cmp	ecx, eax
	jg	.L413
	jmp	.L374
.L547:
	mov	eax, DWORD PTR 204[rsp]
	lea	rbx, 288[rsp]
	lea	rdx, 216[rsp]
	mov	rdi, rbx
	mov	QWORD PTR 56[rsp], rbx
	lea	esi, 2[rax]
	movsx	rsi, esi
.LEHB8:
	call	_ZNSt6vectorIxSaIxEEC1EmRKS0_
.LEHE8:
	mov	eax, DWORD PTR 204[rsp]
	lea	rdi, 256[rsp]
	lea	rcx, 224[rsp]
	mov	rdx, rbx
	mov	QWORD PTR 40[rsp], rdi
	lea	esi, 2[rax]
	movsx	rsi, esi
.LEHB9:
	call	_ZNSt6vectorIS_IxSaIxEESaIS1_EEC1EmRKS1_RKS2_
.LEHE9:
	mov	rdi, rbx
	call	_ZNSt12_Vector_baseIxSaIxEED2Ev
	mov	rcx, QWORD PTR 256[rsp]
	mov	esi, DWORD PTR 204[rsp]
	mov	rax, QWORD PTR [rcx]
	mov	QWORD PTR [rax], 1
	test	esi, esi
	js	.L351
	mov	rax, QWORD PTR math[rip]
	mov	QWORD PTR 88[rsp], rcx
	mov	r13d, 8
	movabs	r14, 155014655926305585
	mov	QWORD PTR 16[rsp], rcx
	mov	rbx, QWORD PTR math[rip+24]
	mov	QWORD PTR [rsp], rax
	movsx	rax, esi
	lea	r9, 16[0+rax*8]
	mov	DWORD PTR 108[rsp], esi
	mov	rsi, QWORD PTR 8[rsp]
	mov	QWORD PTR 96[rsp], r9
.L352:
	mov	r9d, DWORD PTR [rsi+r13]
	mov	eax, DWORD PTR 4[rsi+r13]
	mov	QWORD PTR 112[rsp], rbp
	mov	rdi, QWORD PTR [rsp]
	mov	edx, r9d
	sub	edx, DWORD PTR -8[rsi+r13]
	mov	DWORD PTR 24[rsp], eax
	add	eax, edx
	sub	eax, DWORD PTR -4[rsi+r13]
	mov	ecx, edx
	cmp	edx, eax
	setle	r10b
	shr	ecx, 31
	or	r10d, ecx
	movsx	rcx, eax
	sub	eax, edx
	cdqe
	lea	rdi, [rdi+rcx*8]
	movsx	rcx, edx
	mov	BYTE PTR 48[rsp], r10b
	lea	rax, [rbx+rax*8]
	mov	QWORD PTR 56[rsp], rdi
	lea	rdi, [rbx+rcx*8]
	xor	r10d, r10d
	mov	QWORD PTR 80[rsp], rax
	mov	rax, QWORD PTR 16[rsp]
	mov	QWORD PTR 72[rsp], rdi
	mov	r12, QWORD PTR 24[rax]
	mov	r15, QWORD PTR [rax]
	lea	rax, -8[r12+r13]
	lea	r11, [r12+r13]
	mov	QWORD PTR 32[rsp], rax
	jmp	.L356
.L554:
	xor	ebp, ebp
	test	edi, edi
	js	.L460
.L354:
	mov	rdi, QWORD PTR [r15+r10]
	mov	r8, QWORD PTR 32[rsp]
	imul	rdi, rcx
	add	rdi, QWORD PTR [r12+r10]
	mov	rax, rdi
	imul	r14
	mov	rax, rdx
	mov	rdx, rdi
	sar	rdx, 63
	sar	rax, 23
	sub	rax, rdx
	imul	rax, rax, 998244353
	sub	rdi, rax
	mov	QWORD PTR [r12+r10], rdi
	mov	rdi, QWORD PTR [r15+r10]
	imul	rdi, rbp
	add	rdi, QWORD PTR [r8]
	mov	rax, rdi
	imul	r14
	mov	rax, rdx
	mov	rdx, rdi
	sar	rdx, 63
	sar	rax, 23
	sub	rax, rdx
	imul	rax, rax, 998244353
	sub	rdi, rax
	mov	QWORD PTR [r8], rdi
	imul	rcx, QWORD PTR [r15+r10]
	mov	rax, rcx
	mov	rdi, rcx
	imul	r14
	sar	rdi, 63
	mov	rax, rdx
	sar	rax, 23
	sub	rax, rdi
	imul	rax, rax, 998244353
	sub	rcx, rax
	imul	rcx, rbp
	mov	rax, rcx
	mov	rdi, rcx
	imul	r14
	sar	rdi, 63
	mov	rax, rdx
	sar	rax, 23
	sub	rax, rdi
	imul	rax, rax, 998244353
	sub	rcx, rax
	mov	rdx, rcx
	mov	ecx, 998244353
	sub	rcx, rdx
	add	rcx, QWORD PTR [r11]
	mov	rax, rcx
	mov	rdi, rcx
	imul	r14
	sar	rdi, 63
	add	r10, 8
	mov	rax, rdx
	sar	rax, 23
	sub	rax, rdi
	imul	rax, rax, 998244353
	sub	rcx, rax
	mov	QWORD PTR [r11], rcx
	cmp	r13, r10
	je	.L553
.L356:
	xor	ecx, ecx
	cmp	BYTE PTR 48[rsp], 0
	je	.L353
	mov	rax, QWORD PTR 56[rsp]
	mov	rcx, QWORD PTR [rax]
	mov	rax, QWORD PTR 72[rsp]
	imul	rcx, QWORD PTR [rax]
	mov	rax, rcx
	mov	rdi, rcx
	imul	r14
	sar	rdi, 63
	mov	rax, rdx
	sar	rax, 23
	sub	rax, rdi
	imul	rax, rax, 998244353
	sub	rcx, rax
	mov	rax, QWORD PTR 80[rsp]
	mov	rdi, QWORD PTR [rax]
	imul	rdi, rcx
	mov	rax, rdi
	imul	r14
	mov	rax, rdi
	sar	rax, 63
	sar	rdx, 23
	mov	rcx, rdx
	sub	rcx, rax
	imul	rax, rcx, 998244353
	sub	rdi, rax
	mov	rcx, rdi
.L353:
	mov	eax, DWORD PTR 24[rsp]
	mov	edi, r9d
	sub	edi, DWORD PTR [rsi+r10]
	add	eax, edi
	sub	eax, DWORD PTR 4[rsi+r10]
	mov	r8d, eax
	cmp	edi, eax
	jg	.L554
.L460:
	mov	rbp, QWORD PTR [rsp]
	movsx	rax, edi
	movsx	rdx, r8d
	mov	rbp, QWORD PTR 0[rbp+rdx*8]
	imul	rbp, QWORD PTR [rbx+rax*8]
	mov	rax, rbp
	imul	r14
	mov	rax, rdx
	mov	rdx, rbp
	sar	rdx, 63
	sar	rax, 23
	sub	rax, rdx
	imul	rax, rax, 998244353
	sub	rbp, rax
	mov	eax, r8d
	sub	eax, edi
	cdqe
	mov	rdi, QWORD PTR [rbx+rax*8]
	imul	rdi, rbp
	mov	rax, rdi
	imul	r14
	mov	rax, rdi
	sar	rax, 63
	sar	rdx, 23
	sub	rdx, rax
	imul	rax, rdx, 998244353
	sub	rdi, rax
	mov	rbp, rdi
	jmp	.L354
.L553:
	add	QWORD PTR 16[rsp], 24
	mov	rbp, QWORD PTR 112[rsp]
	add	r13, 8
	cmp	QWORD PTR 96[rsp], r13
	jne	.L352
	mov	rcx, QWORD PTR 88[rsp]
	mov	esi, DWORD PTR 108[rsp]
.L351:
	lea	eax, 1[rsi]
	lea	rdi, _ZSt4cout[rip]
	cdqe
	imul	rdx, rax, 24
	mov	rdx, QWORD PTR [rcx+rdx]
	mov	ecx, 998244353
	mov	rbx, rcx
	sub	rbx, QWORD PTR [rdx+rax*8]
	mov	rax, rbx
	cqo
	idiv	rcx
	mov	rsi, rdx
.LEHB10:
	call	_ZNSo9_M_insertIxEERSoT_@PLT
	mov	esi, 10
	mov	rdi, rax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c.isra.0
.LEHE10:
	mov	rdi, QWORD PTR 40[rsp]
	call	_ZNSt6vectorIS_IxSaIxEESaIS1_EED1Ev
	mov	eax, DWORD PTR 192[rsp]
	jmp	.L334
.L360:
	xor	esi, esi
	xor	ebx, ebx
	xor	eax, eax
	mov	QWORD PTR 224[rsp], rsi
	mov	QWORD PTR 240[rsp], rsi
	jmp	.L436
.L551:
	xor	r8d, r8d
	xor	ebx, ebx
	xor	r12d, r12d
	mov	QWORD PTR 72[rsp], r8
.L374:
	lea	eax, -1[r13]
	mov	rsi, QWORD PTR 32[rsp]
	mov	ecx, 998244353
	lea	rdi, _ZSt4cout[rip]
	cdqe
	imul	rdx, rax, 24
	mov	rdx, QWORD PTR [rsi+rdx]
	mov	rax, QWORD PTR [rdx+rax*8]
	add	rax, rax
	cqo
	idiv	rcx
	mov	rsi, rdx
.LEHB11:
	call	_ZNSo9_M_insertIxEERSoT_@PLT
	mov	esi, 10
	mov	rdi, rax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c.isra.0
	mov	rax, QWORD PTR 72[rsp]
	mov	rdi, QWORD PTR 56[rsp]
	mov	QWORD PTR 288[rsp], r12
	mov	QWORD PTR 296[rsp], rbx
	mov	QWORD PTR 304[rsp], rax
	call	_ZNSt6vectorIS_IxSaIxEESaIS1_EED1Ev
	mov	rdi, QWORD PTR 40[rsp]
	call	_ZNSt6vectorIS_IxSaIxEESaIS1_EED1Ev
	lea	rdi, 224[rsp]
	call	_ZNSt6vectorIS_IiSaIiEESaIS1_EED1Ev
	jmp	.L357
.L396:
	mov	rax, QWORD PTR 24[rsp]
	lea	rbx, [r12+rax]
.L408:
	mov	r15, QWORD PTR 32[rsp]
.L410:
	mov	rax, QWORD PTR 8[r15]
	mov	rdi, QWORD PTR [r15]
	cmp	rdi, rax
	je	.L411
	sub	rax, rdi
	xor	esi, esi
	mov	rdx, rax
	call	memset@PLT
.L411:
	add	r15, 24
	cmp	QWORD PTR 48[rsp], r15
	jne	.L410
	jmp	.L545
.L394:
	mov	r15, r12
	cmp	rbx, r12
	jne	.L398
	add	rbx, QWORD PTR 24[rsp]
	jmp	.L435
	.p2align 4,,10
	.p2align 3
.L416:
	mov	rbp, QWORD PTR [r12]
	mov	rax, QWORD PTR [r15]
	add	rbp, r11
	mov	r10, QWORD PTR 0[rbp]
	add	r10, QWORD PTR [rax+r14]
	movabs	rax, 155014655926305585
	imul	r10
	mov	rax, r10
	sar	rax, 63
	sar	rdx, 23
	sub	rdx, rax
	imul	rax, rdx, 998244353
	sub	r10, rax
	mov	QWORD PTR 0[rbp], r10
	jmp	.L420
.L393:
	mov	rsi, QWORD PTR 32[rsp]
	mov	rdx, r12
	add	r15, rsi
	mov	rax, rsi
	cmp	rsi, r15
	je	.L555
.L399:
	mov	rsi, rax
	mov	rdi, rdx
	mov	QWORD PTR 16[rsp], rax
	mov	QWORD PTR [rsp], rdx
	call	_ZNSt6vectorIxSaIxEEaSERKS1_.isra.0
.LEHE11:
	mov	rax, QWORD PTR 16[rsp]
	mov	rdx, QWORD PTR [rsp]
	add	rax, 24
	add	rdx, 24
	cmp	r15, rax
	jne	.L399
	mov	rax, QWORD PTR 96[rsp]
	mov	QWORD PTR 216[rsp], rbx
	mov	QWORD PTR 288[rsp], rbx
	mov	QWORD PTR 296[rsp], rax
	cmp	QWORD PTR 48[rsp], r15
	je	.L402
.L401:
	mov	r13, rbx
	jmp	.L406
.L556:
	mov	rdi, rsi
	mov	QWORD PTR [rsp], rsi
.LEHB12:
	call	_Znwm@PLT
.LEHE12:
	mov	rsi, QWORD PTR [rsp]
	mov	rcx, rax
.L404:
	movq	xmm0, rcx
	add	rsi, rcx
	punpcklqdq	xmm0, xmm0
	mov	QWORD PTR 16[r13], rsi
	movups	XMMWORD PTR 0[r13], xmm0
	mov	rsi, QWORD PTR [r15]
	mov	rdx, QWORD PTR 8[r15]
	sub	rdx, rsi
	test	rdx, rdx
	jle	.L405
	mov	rdi, rcx
	mov	QWORD PTR [rsp], rdx
	call	memcpy@PLT
	mov	rdx, QWORD PTR [rsp]
	lea	rcx, [rax+rdx]
.L405:
	mov	QWORD PTR 8[r13], rcx
	add	r13, 24
	add	r15, 24
	mov	QWORD PTR 216[rsp], r13
	cmp	QWORD PTR 48[rsp], r15
	je	.L402
.L406:
	mov	rsi, QWORD PTR 8[r15]
	pxor	xmm6, xmm6
	sub	rsi, QWORD PTR [r15]
	mov	QWORD PTR 16[r13], 0
	movups	XMMWORD PTR 0[r13], xmm6
	jne	.L556
	xor	ecx, ecx
	jmp	.L404
.L552:
	mov	rdi, rsi
.LEHB13:
	call	_Znwm@PLT
.LEHE13:
	mov	QWORD PTR 208[rsp], rax
	mov	rsi, QWORD PTR 32[rsp]
	mov	r15, rax
	cmp	QWORD PTR 48[rsp], rsi
	je	.L557
	movq	xmm0, rax
	mov	r9, QWORD PTR 32[rsp]
	mov	r13, rax
	movhps	xmm0, QWORD PTR 128[rsp]
	movaps	XMMWORD PTR 288[rsp], xmm0
	jmp	.L385
.L559:
	mov	rdi, rsi
	mov	QWORD PTR 16[rsp], r9
	mov	QWORD PTR [rsp], rsi
.LEHB14:
	call	_Znwm@PLT
.LEHE14:
	mov	rsi, QWORD PTR [rsp]
	mov	r9, QWORD PTR 16[rsp]
	mov	rcx, rax
.L383:
	movq	xmm0, rcx
	add	rsi, rcx
	punpcklqdq	xmm0, xmm0
	mov	QWORD PTR 16[r13], rsi
	movups	XMMWORD PTR 0[r13], xmm0
	mov	rsi, QWORD PTR [r9]
	mov	rdx, QWORD PTR 8[r9]
	sub	rdx, rsi
	test	rdx, rdx
	jle	.L384
	mov	rdi, rcx
	mov	QWORD PTR 16[rsp], r9
	mov	QWORD PTR [rsp], rdx
	call	memcpy@PLT
	mov	rdx, QWORD PTR [rsp]
	mov	r9, QWORD PTR 16[rsp]
	lea	rcx, [rax+rdx]
.L384:
	mov	QWORD PTR 8[r13], rcx
	add	r13, 24
	add	r9, 24
	mov	QWORD PTR 208[rsp], r13
	cmp	QWORD PTR 48[rsp], r9
	je	.L558
.L385:
	mov	rsi, QWORD PTR 8[r9]
	pxor	xmm5, xmm5
	sub	rsi, QWORD PTR [r9]
	mov	QWORD PTR 16[r13], 0
	movups	XMMWORD PTR 0[r13], xmm5
	jne	.L559
	xor	ecx, ecx
	jmp	.L383
.L557:
	cmp	rbx, r12
	je	.L560
.L379:
	mov	r13, r12
.L391:
	mov	rdi, QWORD PTR 0[r13]
	test	rdi, rdi
	je	.L390
	mov	rsi, QWORD PTR 16[r13]
	sub	rsi, rdi
	call	_ZdlPvm@PLT
.L390:
	add	r13, 24
	cmp	rbx, r13
	jne	.L391
	jmp	.L382
.L558:
	cmp	rbx, r12
	jne	.L379
.L382:
	test	r12, r12
	je	.L387
.L380:
	mov	rsi, r14
	mov	rdi, r12
	call	_ZdlPvm@PLT
.L387:
	mov	rax, QWORD PTR 24[rsp]
	mov	r12, r15
	add	rax, r15
	mov	QWORD PTR 72[rsp], rax
	mov	rbx, rax
	jmp	.L392
.L555:
	mov	QWORD PTR 216[rsp], rbx
	mov	QWORD PTR 288[rsp], rbx
	cmp	QWORD PTR 48[rsp], rsi
	je	.L561
	mov	rax, QWORD PTR 96[rsp]
	mov	QWORD PTR 296[rsp], rax
	jmp	.L401
.L441:
	mov	rbp, r13
	jmp	.L324
.L561:
	mov	rax, QWORD PTR 24[rsp]
	lea	rbx, [r12+rax]
	jmp	.L435
.L560:
	test	rbx, rbx
	jne	.L380
	mov	rax, QWORD PTR 24[rsp]
	mov	r13d, DWORD PTR 196[rsp]
	mov	r12, r15
	lea	rbx, [r15+rax]
	mov	QWORD PTR 72[rsp], rbx
	jmp	.L435
.L549:
	lea	rbp, 8[rax]
	jmp	.L331
.L548:
	call	__stack_chk_fail@PLT
.L457:
	endbr64
	mov	r13, rax
	jmp	.L407
.L456:
	endbr64
	mov	r13, rax
	jmp	.L388
.L459:
	endbr64
	mov	r13, rax
	jmp	.L389
.L455:
	endbr64
	mov	rbx, rax
	jmp	.L431
.L522:
	endbr64
	jmp	.L523
.L524:
	endbr64
	jmp	.L525
.L453:
	endbr64
	mov	rbx, rax
	jmp	.L430
.L452:
	endbr64
	mov	rbx, rax
	jmp	.L428
	.section	.gcc_except_table,"a",@progbits
.LLSDA14981:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE14981-.LLSDACSB14981
.LLSDACSB14981:
	.uleb128 .LEHB3-.LFB14981
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB14981
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L524-.LFB14981
	.uleb128 0
	.uleb128 .LEHB5-.LFB14981
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L522-.LFB14981
	.uleb128 0
	.uleb128 .LEHB6-.LFB14981
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L455-.LFB14981
	.uleb128 0
	.uleb128 .LEHB7-.LFB14981
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L459-.LFB14981
	.uleb128 0
	.uleb128 .LEHB8-.LFB14981
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L524-.LFB14981
	.uleb128 0
	.uleb128 .LEHB9-.LFB14981
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L452-.LFB14981
	.uleb128 0
	.uleb128 .LEHB10-.LFB14981
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L453-.LFB14981
	.uleb128 0
	.uleb128 .LEHB11-.LFB14981
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L459-.LFB14981
	.uleb128 0
	.uleb128 .LEHB12-.LFB14981
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L457-.LFB14981
	.uleb128 0
	.uleb128 .LEHB13-.LFB14981
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L459-.LFB14981
	.uleb128 0
	.uleb128 .LEHB14-.LFB14981
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L456-.LFB14981
	.uleb128 0
.LLSDACSE14981:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC14981
	.type	main.cold, @function
main.cold:
.LFSB14981:
.L407:
	.cfi_def_cfa_offset 384
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	mov	rdi, QWORD PTR 56[rsp]
	call	_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED1Ev
.L389:
	mov	rax, QWORD PTR 72[rsp]
	mov	rdi, QWORD PTR 56[rsp]
	mov	QWORD PTR 296[rsp], rbx
	mov	rbx, r13
	mov	QWORD PTR 288[rsp], r12
	mov	QWORD PTR 304[rsp], rax
	call	_ZNSt6vectorIS_IxSaIxEESaIS1_EED1Ev
	mov	rdi, QWORD PTR 40[rsp]
	call	_ZNSt6vectorIS_IxSaIxEESaIS1_EED1Ev
.L432:
	lea	rdi, 224[rsp]
	call	_ZNSt6vectorIS_IiSaIiEESaIS1_EED1Ev
.L429:
	mov	rax, QWORD PTR 8[rsp]
	mov	rdi, QWORD PTR 40[rsp]
	mov	QWORD PTR 264[rsp], rbp
	mov	QWORD PTR 256[rsp], rax
	mov	rax, QWORD PTR 64[rsp]
	mov	QWORD PTR 272[rsp], rax
	call	_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev
	mov	rax, QWORD PTR 312[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L562
	mov	rdi, rbx
.LEHB15:
	call	_Unwind_Resume@PLT
.LEHE15:
.L388:
	mov	rdi, QWORD PTR 56[rsp]
	call	_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED1Ev
	mov	rsi, QWORD PTR 24[rsp]
	mov	rdi, r15
	call	_ZdlPvm@PLT
	jmp	.L389
.L562:
	call	__stack_chk_fail@PLT
.L431:
	mov	rdi, QWORD PTR 56[rsp]
	call	_ZNSt12_Vector_baseIxSaIxEED2Ev
	jmp	.L432
.L528:
	mov	rax, QWORD PTR 312[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L563
	lea	rdi, .LC0[rip]
.LEHB16:
	call	_ZSt20__throw_length_errorPKc@PLT
.L527:
	mov	rax, QWORD PTR 312[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L564
	lea	rdi, .LC3[rip]
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE16:
.L563:
	call	__stack_chk_fail@PLT
.L564:
	call	__stack_chk_fail@PLT
.L529:
	mov	rax, QWORD PTR 312[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L565
	lea	rdi, .LC3[rip]
.LEHB17:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE17:
.L458:
	endbr64
.L525:
	mov	rbx, rax
	lea	rax, 256[rsp]
	mov	QWORD PTR 40[rsp], rax
	jmp	.L429
.L565:
	call	__stack_chk_fail@PLT
.L454:
	endbr64
.L523:
	mov	rbx, rax
	lea	rax, 256[rsp]
	mov	QWORD PTR 40[rsp], rax
	jmp	.L432
.L428:
	mov	rdi, QWORD PTR 56[rsp]
	call	_ZNSt12_Vector_baseIxSaIxEED2Ev
	jmp	.L429
.L526:
	mov	rax, QWORD PTR 312[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L566
	lea	rdi, .LC0[rip]
.LEHB18:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE18:
.L566:
	call	__stack_chk_fail@PLT
.L430:
	mov	rdi, QWORD PTR 40[rsp]
	call	_ZNSt6vectorIS_IxSaIxEESaIS1_EED1Ev
	jmp	.L429
	.cfi_endproc
.LFE14981:
	.section	.gcc_except_table
.LLSDAC14981:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC14981-.LLSDACSBC14981
.LLSDACSBC14981:
	.uleb128 .LEHB15-.LCOLDB6
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB16-.LCOLDB6
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L458-.LCOLDB6
	.uleb128 0
	.uleb128 .LEHB17-.LCOLDB6
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L454-.LCOLDB6
	.uleb128 0
	.uleb128 .LEHB18-.LCOLDB6
	.uleb128 .LEHE18-.LEHB18
	.uleb128 0
	.uleb128 0
.LLSDACSEC14981:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE6:
	.section	.text.startup
.LHOTE6:
	.p2align 4
	.type	_GLOBAL__sub_I_inf, @function
_GLOBAL__sub_I_inf:
.LFB19116:
	.cfi_startproc
	endbr64
	lea	rdx, __dso_handle[rip]
	lea	rsi, math[rip]
	lea	rdi, _ZN8mathbaseD1Ev[rip]
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE19116:
	.size	_GLOBAL__sub_I_inf, .-_GLOBAL__sub_I_inf
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_inf
	.globl	math
	.bss
	.align 32
	.type	math, @object
	.size	math, 48
math:
	.zero	48
	.globl	ouf
	.section	.data.rel.ro,"aw"
	.align 8
	.type	ouf, @object
	.size	ouf, 8
ouf:
	.quad	_ZSt4cout
	.globl	inf
	.align 8
	.type	inf, @object
	.size	inf, 8
inf:
	.quad	_ZSt3cin
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	1
	.long	1
	.align 8
.LC4:
	.long	-1
	.long	-1
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
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
)");