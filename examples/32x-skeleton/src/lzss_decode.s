! LZSS decoder for SEGA 32X
! /Mic, 2009

	.section .text
	.align 1
	
	.global		_lzss_decode

! In: r4 = compressed data, r5 = compressed size, r6 = destination
!
_lzss_decode: ! save the registers to stack pointer?
	mov.l	r8,@-r15	
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov.l	r14,@-r15

	mov.l	text_buf,r3 !copy text_buf to r3
	mov	#0,r1			!set r1 to 0 (r1 is local variable)
	mov.w	N_minus_F,r0	!set r0 to word 4078 (0x0FEE)
	mov	r0,r7			!set r7 to to r0 (0x0FEE)
_init_text_buf:			! Set all bytes in text_buf to 0x00
	add	#-1,r0
	mov.b	r1,@(r0,r3)
	cmp/pl	r0
	bt	_init_text_buf

	mov.w	buf_pos_mask,r9	! store buf_pos_mask word to r9
	mov.l	text_buf,r11	!store text_buf longword to r11
	mov	#0,r3		! Input stream position
	mov	#0,r13		! Hi/lo byte counter
	mov	#0,r14		! set r14 to 0
_lzss_loop:
	cmp/hs	r5,r3	! if compressed size > input stream pos
	bt	_lzss_done	! then delayed branch to _lzss_done, break loop (If T = 1, disp X 2 + PC --> PC; if T = 0, nop )
	mov	r4,r0		! set compressed data address to r0
	mov.b	@(r0,r3),r8	! The first byte of each block contains the flags, save flag in R8 ((R0 + Rm) --> Sign extension --> Rn)
	mov	#8,r10		! 8 flags in one byte
	add	#1,r3		! add 1 to input stream position
_check_flags:
	shlr	r8		! Shift the next flag from r8 into T
	bf	_flag_clear		! Branch _flag_clear If T = 0, disp X 2 + PC --> PC; if T = 1, nop
	cmp/hs	r5,r3		! Make sure we're not beyond the last byte of the input stream
	bt	_lzss_done		! then delayed branch to _lzss_done, break loop
	mov	r4,r0		! set compressed data address to r0
	mov.b	@(r0,r3),r1	!	Get the second byte in r1
	mov	r11,r0		! set the r11 t r0
	add	#1,r3		! add 1 to input stream position
	bra	_output_byte	! Delayed branch to writing output byte, does next line first
	mov	#1,r2		! Make sure the bf after _output_byte isn't taken
_flag_clear:
	cmp/hs	r5,r3
	bt	_lzss_done
	mov	r4,r0
	mov.b	@(r0,r3),r2	! idx
	extu.b	r2,r2
	add	#1,r3
	mov.b	@(r0,r3),r1	! j
	add	#1,r3
	extu.b	r1,r12
	shlr2	r12
	shlr2	r12
	shll8	r12		! r12 = (j & 0xf0) << 4
	or	r2,r12		! r12 = ((j & 0xf0) << 4) | idx
	mov	#15,r2		! write 15 to r2
	and	r1,r2		! r1 and'd r2 -> r2
	mov	r11,r0		! write r11 to r0
	add	#3,r2		! r2 = (j & 0x0f) + THRESHOLD + 1
_copy_string:		! copies address?
	and	r9,r12			! r9 and'd r12 -> r12
	mov.b	@(r0,r12),r1	! Write address of r0 + r12 
	add	#1,r12			! add 1 to r12
_output_byte:			
	extu.b	r1,r1		! Zero extend byte from input stream in r1(A byte in Rm is zero-extended --> Rn)
	mov.b	r1,@(r0,r7)	! Write to text_buf at address r0 + r7
	add	#1,r7			! add 1 to text_buf address
	tst	r13,r13			! R13 & R13; if the result is 0, 1 --> T
	bt	_no_vram_write	! Delayed branch, if T = 1, disp X 2 + PC --> PC; if T = 0, nop
	shll8	r14			! R14 8-bit shift left --> R14
	or	r1,r14			! r1 or'd to r14 -> r14
	mov.w	r14,@r6		! Write to the output stream address
	bra	_wrap_adr		! Delayed branch to wrap addr, does next line first
	add	#2,r6			! Add 2 to the framebuffer's address
_no_vram_write:
	extu.b	r1,r14		! Zero extend byte from input stream (A byte in Rm is zero-extended --> Rn)
_wrap_adr:
	and	r9,r7			! r9 and'd to r7 -> r7
	mov	#1,r1			! set r1 to 1
	xor	r1,r13			! r13 xor'd r1 (0000 0000 0000 0001)
_next_string_pos:
	dt	r2				! r2 - 1 --> R2, when Rn is 0, 1 --> T. When Rn is nonzero, 0 --> T
	bf	_copy_string	! Branch _copy_string loop. If T = 0, go to _copy_string; if T = 1, nop
_next_flag:
	dt	r10				! r10 - 1 --> r10, when Rn is 0, 1 --> T. When Rn is nonzero, 0 --> T
	bt	_lzss_loop		! Delayed branch, if T = 1, disp X 2 + PC --> PC; if T = 0, nop
	bra	_check_flags	! Delayed branch _check_flags, does next line first
	or	r0,r0			! r0 or'd with itself?
_lzss_done:
	mov.l	@r15+,r14	
	mov.l	@r15+,r13	
	mov.l	@r15+,r12	
	mov.l	@r15+,r11	
	mov.l	@r15+,r10	
	mov.l	@r15+,r9	
	mov.l	@r15+,r8	
	rts
	nop
	
	
	.align 2
text_buf:
	.long	_text_buf
N_minus_F:
	.short	4078
buf_pos_mask:
	.short	4095

	.comm	_text_buf, 4096, 4
	! seems above was overrunning the buffer and corrupting following common symbol, see text_buf in output.map
	