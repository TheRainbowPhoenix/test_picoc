
!Based on https://code.woboq.org/linux/linux/arch/sh/lib/udivsi3_i4i.S.html
!Slightly modified by SnailMath

!THIS IS NOT MY OWN WORK!!!


/* SPDX-License-Identifier: GPL-2.0+ WITH GCC-exception-2.0
   Copyright (C) 1994, 1995, 1997, 1998, 1999, 2000, 2001, 2002, 2003,
   2004, 2005, 2006
   Free Software Foundation, Inc.
*/
!! libgcc routines for the Renesas / SuperH SH CPUs.
!! Contributed by Steve Chamberlain.
!! sac@cygnus.com
!! ashiftrt_r4_x, ___ashrsi3, ___ashlsi3, ___lshrsi3 routines
!! recoded in assembly by Toshiyasu Morita
!! tm@netcom.com
/* SH2 optimizations for ___ashrsi3, ___ashlsi3, ___lshrsi3 and
   ELF local label prefixes by J"orn Rennecke
   amylaar@cygnus.com  */
/* This code used shld, thus is not suitable for SH1 / SH2.  */
/* Signed / unsigned division without use of FPU, optimized for SH4.
   Uses a lookup table for divisors in the range -128 .. +128, and
   div1 with case distinction for larger divisors in three more ranges.
   The code is lumped together with the table to allow the use of mova.  */
!#ifdef CONFIG_CPU_LITTLE_ENDIAN
!#define L_LSB 0
!#define L_LSWMSB 1
!#define L_MSWLSB 2
!#else
!#define L_LSB 3
!#define L_LSWMSB 2
.equ L_LSWMSB, 2
!#define L_MSWLSB 1
.equ L_MSWLSB, 1
!#endif
	.balign 4
	.global	___udivsi3_i4i
	.global	___udivsi3_i4
	.set	___udivsi3_i4, ___udivsi3_i4i
	.type	___udivsi3_i4i, @function
___udivsi3_i4i:
	mov.w c128_w, r1
	div0u
	mov r4,r0
	shlr8 r0
	cmp/hi r1,r5
	extu.w r5,r1
	bf udiv_le128
	cmp/eq r5,r1
	bf udiv_ge64k
	shlr r0
	mov r5,r1
	shll16 r5
	mov.l r4,@-r15
	div1 r5,r0
	mov.l r1,@-r15
	div1 r5,r0
	div1 r5,r0
	bra udiv_25
	div1 r5,r0
div_le128:
	mova div_table_ix,r0
	bra div_le128_2
	mov.b @(r0,r5),r1
udiv_le128:
	mov.l r4,@-r15
	mova div_table_ix,r0
	mov.b @(r0,r5),r1
	mov.l r5,@-r15
div_le128_2:
	mova div_table_inv,r0
	mov.l @(r0,r1),r1
	mov r5,r0
	tst #0xfe,r0
	mova div_table_clz,r0
	dmulu.l r1,r4
	mov.b @(r0,r5),r1
	bt/s div_by_1
	mov r4,r0
	mov.l @r15+,r5
	sts mach,r0
	/* clrt */
	addc r4,r0
	mov.l @r15+,r4
	rotcr r0
	rts
	shld r1,r0
div_by_1_neg:
	neg r4,r0
div_by_1:
	mov.l @r15+,r5
	rts
	mov.l @r15+,r4
div_ge64k:
	bt/s div_r8
	div0u
	shll8 r5
	bra div_ge64k_2
	div1 r5,r0
udiv_ge64k:
	cmp/hi r0,r5
	mov r5,r1
	bt udiv_r8
	shll8 r5
	mov.l r4,@-r15
	div1 r5,r0
	mov.l r1,@-r15
div_ge64k_2:
	div1 r5,r0
	mov.l zero_l,r1
	.rept 4
	div1 r5,r0
	.endr
	mov.l r1,@-r15
	div1 r5,r0
	mov.w m256_w,r1
	div1 r5,r0
	mov.b r0,@(L_LSWMSB,r15)
	xor r4,r0
	and r1,r0
	bra div_ge64k_end
	xor r4,r0

div_r8:
	shll16 r4
	bra div_r8_2
	shll8 r4
udiv_r8:
	mov.l r4,@-r15
	shll16 r4
	clrt
	shll8 r4
	mov.l r5,@-r15
div_r8_2:
	rotcl r4
	mov r0,r1
	div1 r5,r1
	mov r4,r0
	rotcl r0
	mov r5,r4
	div1 r5,r1
	.rept 5
	rotcl r0; div1 r5,r1
	.endr
	rotcl r0
	mov.l @r15+,r5
	div1 r4,r1
	mov.l @r15+,r4
	rts
	rotcl r0
	.global	___sdivsi3_i4i
	.global ___sdivsi3_i4
	.global	___sdivsi3
	.set	___sdivsi3_i4, ___sdivsi3_i4i
	.set	___sdivsi3, ___sdivsi3_i4i
	.type	___sdivsi3_i4i, @function
	/* This is link-compatible with a __sdivsi3 call,
	   but we effectively clobber only r1.  */
___sdivsi3_i4i:
	mov.l r4,@-r15
	cmp/pz r5
	mov.w c128_w, r1
	bt/s pos_divisor
	cmp/pz r4
	mov.l r5,@-r15
	neg r5,r5
	bt/s neg_result
	cmp/hi r1,r5
	neg r4,r4
pos_result:
	extu.w r5,r0
	bf div_le128
	cmp/eq r5,r0
	mov r4,r0
	shlr8 r0
	bf/s div_ge64k
	cmp/hi r0,r5
	div0u
	shll16 r5
	div1 r5,r0
	div1 r5,r0
	div1 r5,r0
udiv_25:
	mov.l zero_l,r1
	div1 r5,r0
	div1 r5,r0
	mov.l r1,@-r15
	.rept 3
	div1 r5,r0
	.endr
	mov.b r0,@(L_MSWLSB,r15)
	xtrct r4,r0
	swap.w r0,r0
	.rept 8
	div1 r5,r0
	.endr
	mov.b r0,@(L_LSWMSB,r15)
div_ge64k_end:
	.rept 8
	div1 r5,r0
	.endr
	mov.l @r15+,r4 ! zero-extension and swap using LS unit.
	extu.b r0,r0
	mov.l @r15+,r5
	or r4,r0
	mov.l @r15+,r4
	rts
	rotcl r0
div_le128_neg:
	tst #0xfe,r0
	mova div_table_ix,r0
	mov.b @(r0,r5),r1
	mova div_table_inv,r0
	bt/s div_by_1_neg
	mov.l @(r0,r1),r1
	mova div_table_clz,r0
	dmulu.l r1,r4
	mov.b @(r0,r5),r1
	mov.l @r15+,r5
	sts mach,r0
	/* clrt */
	addc r4,r0
	mov.l @r15+,r4
	rotcr r0
	shld r1,r0
	rts
	neg r0,r0
pos_divisor:
	mov.l r5,@-r15
	bt/s pos_result
	cmp/hi r1,r5
	neg r4,r4
neg_result:
	extu.w r5,r0
	bf div_le128_neg
	cmp/eq r5,r0
	mov r4,r0
	shlr8 r0
	bf/s div_ge64k_neg
	cmp/hi r0,r5
	div0u
	mov.l zero_l,r1
	shll16 r5
	div1 r5,r0
	mov.l r1,@-r15
	.rept 7
	div1 r5,r0
	.endr
	mov.b r0,@(L_MSWLSB,r15)
	xtrct r4,r0
	swap.w r0,r0
	.rept 8
	div1 r5,r0
	.endr
	mov.b r0,@(L_LSWMSB,r15)
div_ge64k_neg_end:
	.rept 8
	div1 r5,r0
	.endr
	mov.l @r15+,r4 ! zero-extension and swap using LS unit.
	extu.b r0,r1
	mov.l @r15+,r5
	or r4,r1
div_r8_neg_end:
	mov.l @r15+,r4
	rotcl r1
	rts
	neg r1,r0
div_ge64k_neg:
	bt/s div_r8_neg
	div0u
	shll8 r5
	mov.l zero_l,r1
	.rept 6
	div1 r5,r0
	.endr
	mov.l r1,@-r15
	div1 r5,r0
	mov.w m256_w,r1
	div1 r5,r0
	mov.b r0,@(L_LSWMSB,r15)
	xor r4,r0
	and r1,r0
	bra div_ge64k_neg_end
	xor r4,r0
c128_w:
	.word 128
div_r8_neg:
	clrt
	shll16 r4
	mov r4,r1
	shll8 r1
	mov r5,r4
	.rept 7
	rotcl r1; div1 r5,r0
	.endr
	mov.l @r15+,r5
	rotcl r1
	bra div_r8_neg_end
	div1 r4,r0
m256_w:
	.word 0xff00
/* This table has been generated by divtab-sh4.c.  */
	.balign 4
div_table_clz:
	.byte	0
	.byte	1
	.byte	0
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-3
	.byte	-3
	.byte	-3
	.byte	-3
	.byte	-3
	.byte	-3
	.byte	-3
	.byte	-3
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
/* Lookup table translating positive divisor to index into table of
   normalized inverse.  N.B. the '0' entry is also the last entry of the
 previous table, and causes an unaligned access for division by zero.  */
div_table_ix:
	.byte	-6
	.byte	-128
	.byte	-128
	.byte	0
	.byte	-128
	.byte	-64
	.byte	0
	.byte	64
	.byte	-128
	.byte	-96
	.byte	-64
	.byte	-32
	.byte	0
	.byte	32
	.byte	64
	.byte	96
	.byte	-128
	.byte	-112
	.byte	-96
	.byte	-80
	.byte	-64
	.byte	-48
	.byte	-32
	.byte	-16
	.byte	0
	.byte	16
	.byte	32
	.byte	48
	.byte	64
	.byte	80
	.byte	96
	.byte	112
	.byte	-128
	.byte	-120
	.byte	-112
	.byte	-104
	.byte	-96
	.byte	-88
	.byte	-80
	.byte	-72
	.byte	-64
	.byte	-56
	.byte	-48
	.byte	-40
	.byte	-32
	.byte	-24
	.byte	-16
	.byte	-8
	.byte	0
	.byte	8
	.byte	16
	.byte	24
	.byte	32
	.byte	40
	.byte	48
	.byte	56
	.byte	64
	.byte	72
	.byte	80
	.byte	88
	.byte	96
	.byte	104
	.byte	112
	.byte	120
	.byte	-128
	.byte	-124
	.byte	-120
	.byte	-116
	.byte	-112
	.byte	-108
	.byte	-104
	.byte	-100
	.byte	-96
	.byte	-92
	.byte	-88
	.byte	-84
	.byte	-80
	.byte	-76
	.byte	-72
	.byte	-68
	.byte	-64
	.byte	-60
	.byte	-56
	.byte	-52
	.byte	-48
	.byte	-44
	.byte	-40
	.byte	-36
	.byte	-32
	.byte	-28
	.byte	-24
	.byte	-20
	.byte	-16
	.byte	-12
	.byte	-8
	.byte	-4
	.byte	0
	.byte	4
	.byte	8
	.byte	12
	.byte	16
	.byte	20
	.byte	24
	.byte	28
	.byte	32
	.byte	36
	.byte	40
	.byte	44
	.byte	48
	.byte	52
	.byte	56
	.byte	60
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	80
	.byte	84
	.byte	88
	.byte	92
	.byte	96
	.byte	100
	.byte	104
	.byte	108
	.byte	112
	.byte	116
	.byte	120
	.byte	124
	.byte	-128
/* 1/64 .. 1/127, normalized.  There is an implicit leading 1 in bit 32.  */
	.balign 4
zero_l:
	.long	0x0
	.long	0xF81F81F9
	.long	0xF07C1F08
	.long	0xE9131AC0
	.long	0xE1E1E1E2
	.long	0xDAE6076C
	.long	0xD41D41D5
	.long	0xCD856891
	.long	0xC71C71C8
	.long	0xC0E07039
	.long	0xBACF914D
	.long	0xB4E81B4F
	.long	0xAF286BCB
	.long	0xA98EF607
	.long	0xA41A41A5
	.long	0x9EC8E952
	.long	0x9999999A
	.long	0x948B0FCE
	.long	0x8F9C18FA
	.long	0x8ACB90F7
	.long	0x86186187
	.long	0x81818182
	.long	0x7D05F418
	.long	0x78A4C818
	.long	0x745D1746
	.long	0x702E05C1
	.long	0x6C16C16D
	.long	0x68168169
	.long	0x642C8591
	.long	0x60581606
	.long	0x5C9882BA
	.long	0x58ED2309
div_table_inv:
	.long	0x55555556
	.long	0x51D07EAF
	.long	0x4E5E0A73
	.long	0x4AFD6A06
	.long	0x47AE147B
	.long	0x446F8657
	.long	0x41414142
	.long	0x3E22CBCF
	.long	0x3B13B13C
	.long	0x38138139
	.long	0x3521CFB3
	.long	0x323E34A3
	.long	0x2F684BDB
	.long	0x2C9FB4D9
	.long	0x29E4129F
	.long	0x27350B89
	.long	0x24924925
	.long	0x21FB7813
	.long	0x1F7047DD
	.long	0x1CF06ADB
	.long	0x1A7B9612
	.long	0x18118119
	.long	0x15B1E5F8
	.long	0x135C8114
	.long	0x11111112
	.long	0xECF56BF
	.long	0xC9714FC
	.long	0xA6810A7
	.long	0x8421085
	.long	0x624DD30
	.long	0x4104105
	.long	0x2040811
	/* maximum error: 0.987342 scaled: 0.921875*/



