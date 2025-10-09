	.file	"program.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"\nTime taken: %lf sec.\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB36:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	pushl	%esi
	pushl	%ebx
	.cfi_escape 0x10,0x6,0x2,0x75,0x7c
	.cfi_escape 0x10,0x3,0x2,0x75,0x78
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x74,0x6
	subl	$88, %esp
	movl	%gs:20, %eax
	movl	%eax, -28(%ebp)
	xorl	%eax, %eax
	pushl	$2
	call	sysconf@PLT
	movl	%eax, %esi
	leal	-60(%ebp), %eax
	movl	%eax, (%esp)
	call	times@PLT
	leal	-44(%ebp), %eax
	movl	%eax, (%esp)
	call	times@PLT
	movl	-44(%ebp), %eax
	subl	-60(%ebp), %eax
	movl	%esi, -76(%ebp)
	fildl	-76(%ebp)
	movl	%eax, -76(%ebp)
	fidivrl	-76(%ebp)
	pushl	%eax
	pushl	%eax
	leal	.LC0@GOTOFF(%ebx), %eax
	fstpl	(%esp)
	pushl	%eax
	pushl	$2
	call	__printf_chk@PLT
	movl	-28(%ebp), %eax
	subl	%gs:20, %eax
	je	.L2
	call	__stack_chk_fail_local
.L2:
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE36:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB37:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE37:
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
