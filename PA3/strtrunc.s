.text
.global mystrtrunc
	
@initializes 'local variables'
mystrtrunc:
	@save reuten address
	push {lr}
	@save r4
	push {r4}
	@save r5
	push {r5}
	@save the string
	mov r4, r0
	@save the length to truncate
	mov r5, r1
	@find out the length by calling strlen
	bl mystrlen
	@find out if the truncate length if greater than the length
	@of the string
	subs r0, r0, r5
	@If negative then impossible and return original string
	bmi nothing
	@If the truncate is the entire length
	beq zerolength
	@Go to the loop to truncate
	b trunc
	
@where trunc happens
trunc:
	@move 0 into r2
	mov r2, #0
	@Store 0 into the place where it needs to be truncated
	strb r2, [r4, r0]
	@finish program
	b end
	
@if it trunc nothing
nothing:
	@do nothing to the string
	b end
	
@if it truncs a zero sting length
zerolength:
	@move 0 into r2
	mov r2, #0
	@move an empty string into r0
	strb r2, [r4, #0]

@ends program and restores calling resigters
end:	
	@get back original value of r4
	pop {r5}
	@get back original value of r5
	pop {r4}
	@get back return address
	pop {pc}
