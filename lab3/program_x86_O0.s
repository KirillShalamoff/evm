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
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$80, %esp
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	movl	$-589934592, -56(%ebp)
	subl	$12, %esp
	pushl	$2
	call	sysconf@PLT
	addl	$16, %esp
	movl	%eax, -52(%ebp)
	subl	$12, %esp
	leal	-44(%ebp), %eax
	pushl	%eax
	call	times@PLT
	addl	$16, %esp
	fldz
	fstps	-64(%ebp)
	movl	$0, -60(%ebp)
	jmp	.L2
.L5:
	movl	-60(%ebp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L3
	flds	-64(%ebp)
	movl	-60(%ebp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	movl	%eax, -76(%ebp)
	fildl	-76(%ebp)
	fldl	.LC1@GOTOFF(%ebx)
	fdivp	%st, %st(1)
	faddp	%st, %st(1)
	fstps	-64(%ebp)
	jmp	.L4
.L3:
	flds	-64(%ebp)
	movl	-60(%ebp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	movl	%eax, -76(%ebp)
	fildl	-76(%ebp)
	fldl	.LC2@GOTOFF(%ebx)
	fdivp	%st, %st(1)
	faddp	%st, %st(1)
	fstps	-64(%ebp)
.L4:
	addl	$1, -60(%ebp)
.L2:
	movl	-60(%ebp), %eax
	cmpl	-56(%ebp), %eax
	jle	.L5
	subl	$12, %esp
	leal	-28(%ebp), %eax
	pushl	%eax
	call	times@PLT
	addl	$16, %esp
	movl	-28(%ebp), %edx
	movl	-44(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, -48(%ebp)
	fildl	-48(%ebp)
	fildl	-52(%ebp)
	fdivrp	%st, %st(1)
	subl	$4, %esp
	leal	-8(%esp), %esp
	fstpl	(%esp)
	leal	.LC3@GOTOFF(%ebx), %eax
	pushl	%eax
	call	printf@PLT
	addl	$16, %esp
	movl	$0, %eax
	movl	-12(%ebp), %edx
	subl	%gs:20, %edx
	je	.L7
	call	__stack_chk_fail_local
.L7:
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
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
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB7:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE7:
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
