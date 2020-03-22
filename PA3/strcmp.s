.text
.global mystrcmp
	
@initializes 'local variables'
mystrcmp:
	@save lr
	push {lr}
	@move the first string to r1
	mov r2, r1
	@move the second string to r2
	mov r1, r0
	@move 0 to r0 incase strings are equal
	mov r0, #0
	@move 0 to r3 to serve as index
	mov r3, #0
	@move stack pointer to store r4 and r5
	sub sp, sp, #16
	@save r4
	str r4, [sp]
	@save r5
	str r5, [sp, #4]
	@go to loop to start comparing
	b loop
	
@is the index
restart:
	@Move the index by one
	add r3, #1
	
@main loop to compare
loop:
	@get a character from the first string and put it in r4
	ldrb r4, [r1, r3]
	@get a character from the second string and put it in r5
	ldrb r5, [r2, r3]
	@see if we reached the end of the second string
	cmp r5, #0
	@if the first sting is at zero then they are equal
	beq equal
	@subract r4 by r5 to see which is greater
	subs r4, r4, r5
	@If they are the same characters then restart the loop
	beq restart
	@This means the first sting is less than the second string
	bmi less
	@This means the first sting is greater than the second string
	b greater
	
@case if it is less
less:
	@If less than store -1 into r0
	mov r0, #0xffffffff
	@end the program
	b end
	
@case if it is more
greater:
	@If greater than store 1 into r0
	mov r0, #1
	@end the program
	b end
	
@case if it is equal
equal:
	@if stings are equal then store 0 into 0
	mov r0, #0

@ends program and restores calling resigters
end:
	@get original r4 value
	ldr r4, [sp]
	@get original r5 value
	ldr r5, [sp, #4]
	@restore the stack pointer
	add sp, sp, #16
	@put return address into pc
	pop {pc}
