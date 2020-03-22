	.text
	.global totalLength
	
        @resets r5 if need be
totalLength:	
	@adds 0 to r5
	adds r5, #0
	@checks if zero and if so then goes ot count
	beq totalLength1
	@if not zero then set to zero
	mov r5, #0

	@start of totalLength function
totalLength1:
	@Saves the return address
	push {lr}
	@save r1	
	push {r1}
	@save r2
	push {r2}
	@save r3
	push {r3}
	@save r4
	push {r4}
	@save r10
	push {r10}
	@save r6
	push {r6}
	@save r7
	push {r7}
	@save r8
	push {r8}
	@save r9
	push {r9}
	
start1:
	@saves the node	
	mov r1, r0
	@store 0 into r2
	mov r2, #0
	@store 0 into r3
	mov r3, #0
	@store 0 into r4
	mov r4, #0
	@index 1
	mov r6, #3
	@index 2
	mov r7, #7
	@index 3
	mov r8, #11
	@index 4
	mov r9, #4
	
	@start loop to get addresses of node
	b loop1

	@changes the index
index1:
	@subtracs one to index 1
	sub r6, r6, #1
	@shifts r3 to make room for next byte
	lsl r2, #8
	@subtracs one to index 2
	sub r7, r7, #1
	@shifts r3 to make room for next byte
	lsl r3, #8
	@subtracs one to index 3
	sub r8, r8, #1
	@shifts r4 to make room for next byte
	lsl r4, #8
	
	@loop to get fields of node into individual registers
loop1:
	@load byte of first address into r5
	ldrb r10, [r1, r6]
	@store r5's byte into r2
	add r2, r2, r10

	@load byte of second address into r6
	ldrb r10, [r1, r7]
	@store r5's byte into r3
	add r3, r3, r10

	@load byte of third address into r7
	ldrb r10, [r1, r8]
	@store r5's byte into r4
	add r4, r4, r10

	@index for number of loop iterations
	subs r9, r9, #1
	@if iterated 4 times exit loop
	beq loop2
	@go to index
	b index1

	@checks if we are at a leaf node
loop2:
	@adds 0 to left node to check if empty
	adds r3, r3, #0
	@goes to recursive left since left node isn't empty
	bne recursiveleft

	@adds 0 to right node to check if empty
	adds r4, r4, #0
	@goes to recursive right since right node isn't empty
	bne recursiveright

	@Go to strlen
	bl strlen
	
	@moves totallength to r0
	mov r0, r5

	@end loop
	b end
	
	@call totalLength recursively with left node
recursiveleft:
	@move left node into r0
	mov r0, r3
	@call totalLength
	bl totalLength1	
	@move 0 into node to check it off
	mov r3, #0
	@go back to loop2
	b loop2

	@Call totalLength recursively with right node
recursiveright:
	@move right node into r0
	mov r0, r4
	@call totalLength
	bl totalLength1
	@move zero into node to check it off
	mov r4, #0 
	@go back to loop2
	b loop2
strlen:
	@saves address where it was called from
	push {lr}
	@moves a 0 length to r0
	mov r0, #0
	@Keeps track of the index of the string
	mov r10, #0

	@loop of finding length
loop:
	@Store the first character into r9
	ldrb r9, [r2, r10]
	@subract r9 by 1 to see if its negative to verify if at end
	subs r9, #1
	@if negative then reached end of string and finish
	bmi finish
	@adds 1 to the index
	add r10, #1
	@adds 1 to the totallength
	add r5, #1
	@loop back up to see if there are more characters
	b loop

	@ends program and restores calling resigters
finish:
	@return to where the function was called
	pop {pc}
end:
	@get back original r9
	pop {r9}
	@get back original r8
	pop {r8}
	@get back original r7
	pop {r7}
	@get back original r6
	pop {r6}
	@get back original r10
	pop {r10}
	@get back original r4
	pop {r4}
	@get back original r3
	pop {r3}
	@get back original r2
	pop {r2}
	@get back original r1
	pop {r1}
	@Goes to return address
	pop {pc}
