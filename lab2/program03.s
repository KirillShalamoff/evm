	.file	"program.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"\nTime taken: %lf sec.\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB51:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$80, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rdi
	movq	%rdi, 72(%rsp)
	movl	$2, %edi
	call	sysconf@PLT
	movq	%rsp, %rdi
	movq	%rax, %rbx
	call	times@PLT
	leaq	32(%rsp), %rdi
	call	times@PLT
	movq	32(%rsp), %rax
	pxor	%xmm0, %xmm0
	subq	(%rsp), %rax
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movl	$2, %edi
	movl	$1, %eax
	cvtsi2sdq	%rbx, %xmm1
	leaq	.LC0(%rip), %rsi
	divsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	movq	72(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L5
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE51:
	.size	main, .-main
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
