.text
.global mystrrev
	
@initailizes 'local variables'
mystrrev:
	@save the return address
	push {lr}
	@save r4
	push {r4}
	@save r5
	push {r5}
	@move string to r3
	mov r3, r0
	@move start to r4
	mov r4, r1
	@move end to r5
	mov r5, r2
	
@check if start is less than zero
check1:
	@add 0 to start to see if less than 0
	adds r1, r1, #0
	@if start is less than 0 then go to error
	bmi error
	
@check if start is greater than end
check2:
	@subtracts end by start
	subs r2, r5, r4
	@if start is greater than end then go to error
	bmi error
	
@check if end is greater than string length
check3:	
	@call strlen
	bl mystrlen
	@subtract one to the length
	sub r0, r0, #1
	@subract string length by end
	subs r1, r0, r5
	@if end is bigger than length then go to error
	bmi error
	@store end to r0
	mov r0, r5
	@if passes all checks then start the reverse process
	b store
	
@change index
subend:
	@sub r5 by one
	sub r5, r5, #1
	
@store reversed chars into stack
store:
	@get character
	ldrb r2, [r3, r5]
	@store the character
	push {r2}
	@check if end has reached start
	subs r1, r5, r4
	@If so then go to store reversed letters
	beq restore
	@If not then restart the loop
	b subend
	
@change index
subend1:
	@sub 1 to end
	sub r5, r5, #1
	@go to storerev
	b storerev
	
@get back original end value
restore:
	@get back original end
	mov r5, r0
	
@store reversed chars back into string
storerev:
	@get a reversed character
	pop {r2}
	@store the reversed character back into the string
	strb r2, [r3, r5]
	@check if start has reached the end
	subs r1, r5, r4
	@if so then go to finish
	beq restore1
	@if not then restart loop
	b subend1
	
@get back original end value
restore1:
	@restore value of enf
	mov r5, r0
	@go to finish to end the program
	b finish
	
@if a reverse cannot happen
error:
	@start was less than 0
	mov r0, #0xffffffff
	@end the program
	b end
	
@stores the correct value into r0
finish:
	@store the # characters reversed into r0
	sub r0, r5, r4

@ends program and restores calling resigters
end:	
	@get back original r5
	pop {r5}
	@get back original r4
	pop {r4}
	@return to where the function was called
	pop {pc}
