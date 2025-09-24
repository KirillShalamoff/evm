	.file	"program.c"
	.text
	.section	.rodata
.LC3:
	.string	"\nTime taken: %lf sec.\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$4000000000, %eax
	movq	%rax, -104(%rbp)
	movl	$2, %edi
	call	sysconf@PLT
	movq	%rax, -96(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	times@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -116(%rbp)
	movq	$0, -112(%rbp)
	jmp	.L2
.L5:
	movq	-112(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	jne	.L3
	pxor	%xmm1, %xmm1
	cvtss2sd	-116(%rbp), %xmm1
	movq	-112(%rbp), %rax
	addq	%rax, %rax
	addq	$1, %rax
	pxor	%xmm2, %xmm2
	cvtsi2sdq	%rax, %xmm2
	movsd	.LC1(%rip), %xmm0
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -116(%rbp)
	jmp	.L4
.L3:
	pxor	%xmm1, %xmm1
	cvtss2sd	-116(%rbp), %xmm1
	movq	-112(%rbp), %rax
	addq	%rax, %rax
	addq	$1, %rax
	pxor	%xmm2, %xmm2
	cvtsi2sdq	%rax, %xmm2
	movsd	.LC2(%rip), %xmm0
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -116(%rbp)
.L4:
	addq	$1, -112(%rbp)
.L2:
	movq	-112(%rbp), %rax
	cmpq	-104(%rbp), %rax
	jle	.L5
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	times@PLT
	movq	-48(%rbp), %rdx
	movq	-80(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, -88(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2sdq	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	-96(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1074790400
	.align 8
.LC2:
	.long	0
	.long	-1072693248
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
