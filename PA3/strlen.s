.text
.global mystrlen

@initializes 'local variables'
mystrlen:
	@save the return address
	push {lr}
	@save r3
	push {r3}	
	@Moves the address of the string to r1
	mov r1, r0
	@moves a 0 length to r0
	mov r0, #0
	@Keeps track of the index of the string
	mov r2, #0
	
@loop of finding length
loop:
	@Store the first character into r3
	ldrb r3, [r1, r2]
	@subract r3 by 1 to see if its negative
	subs r3, #1
	@Go to the end of the program if its negative
	@If so then it means the character was zero
	bmi end
	@adds 1 to the index
	add r2, #1
	@adds 1 to the length
	add r0, #1
	@loop back up to see if there are more characters
	b loop

@ends program and restores calling resigters
end:
	@get back original r3
	pop {r3}
	@return to where the function was called
	pop {pc}
