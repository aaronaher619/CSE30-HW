.text
.global palindrome
	
@initializes 'local variables'
palindrome:
	@save return address
	push {lr}
	@save r4
	push {r4}
	@save r5
	push {r5}
	@save r6
	push {r6}
	@save string into r4
	mov r4, r0
	@get length of string
	bl mystrlen
	@mov a copy of length to r3
	mov r3, r0
	@mov 2 into r1 to divide by 2
	mov r1, #2
	@get modulo of length to see if even or odd
	bl __aeabi_idivmod
	@move the quotient into r5
	mov r5, r0
	@mov 0 into r2 to have index of first letter
	mov r2, #0
	@go to beginning of loop
	b loopp
	
@change the factor of char checking
factor:
	@add one to get the next char
	add r2, r2, #1
	@sub one to get previous char
	sub r3, r3, #1
	@sub the quotient be the factor of starting char
	@to see if reached middle
	subs r6, r5, r2
	@if zero then it is a palindrome
	beq yespal
	
@main loop to check if chars are the same
loopp:
	@store first char into r0
	ldrb r0, [r4, r2]
	@store last char into r1
	ldrb r1, [r4, r3]
	@subract one by the other
	subs r6, r0, r1
	@if it equals zero then cotinue loop
	beq factor
	@if it is not zero then it is not a palindrome
	b notpalindrome
	
@case that it is not a palindrome
notpalindrome:
	@move 0 into r0 since it is not a palindrome
	mov r0, #0
	@go to end of program
	b end
	
@case that it is a plaindrome
yespal:
	@move 1 into r0 since it is a palindrome
	mov r0, #1

@ends program and restores calling resigters
end:
	@get back original r6
	pop {r6}
	@get back original r5
	pop {r5}
	@get back original r4
	pop {r4}
	@Go to return address
	pop {pc}
