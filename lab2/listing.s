	.file	"program.c"
	.text
	.section	.rodata
.LC1:
	.string	"enter N (N*10^9): "
.LC2:
	.string	"%ld"
	.align 8
.LC6:
	.string	"\n=====Iteration %d===== \nTime taken: %lf sec.\n"
	.align 8
.LC7:
	.string	"\n=====TOTAL===== \nMin time taken: %lf sec."
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
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, -112(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-120(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movq	-120(%rbp), %rax
	imulq	$1000000000, %rax, %rax
	movq	%rax, -120(%rbp)
	movl	$0, -128(%rbp)
	jmp	.L2
.L9:
	movl	$2, %edi
	call	sysconf@PLT
	movq	%rax, -96(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	times@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -124(%rbp)
	movq	$0, -104(%rbp)
	jmp	.L3
.L6:
	movq	-104(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	jne	.L4
	pxor	%xmm1, %xmm1
	cvtss2sd	-124(%rbp), %xmm1
	movq	-104(%rbp), %rax
	addq	%rax, %rax
	addq	$1, %rax
	pxor	%xmm2, %xmm2
	cvtsi2sdq	%rax, %xmm2
	movsd	.LC4(%rip), %xmm0
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -124(%rbp)
	jmp	.L5
.L4:
	pxor	%xmm1, %xmm1
	cvtss2sd	-124(%rbp), %xmm1
	movq	-104(%rbp), %rax
	addq	%rax, %rax
	addq	$1, %rax
	pxor	%xmm2, %xmm2
	cvtsi2sdq	%rax, %xmm2
	movsd	.LC5(%rip), %xmm0
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -124(%rbp)
.L5:
	addq	$1, -104(%rbp)
.L3:
	movq	-120(%rbp), %rax
	cmpq	%rax, -104(%rbp)
	jle	.L6
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
	movl	-128(%rbp), %edx
	addl	$1, %edx
	movq	%rax, %xmm0
	movl	%edx, %esi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	pxor	%xmm0, %xmm0
	cvtsi2sdq	-88(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtsi2sdq	-96(%rbp), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movsd	-112(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L7
	pxor	%xmm0, %xmm0
	cvtsi2sdq	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	-96(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -112(%rbp)
.L7:
	addl	$1, -128(%rbp)
.L2:
	cmpl	$2, -128(%rbp)
	jle	.L9
	movq	-112(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	-1
	.long	2146435071
	.align 8
.LC4:
	.long	0
	.long	1074790400
	.align 8
.LC5:
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
