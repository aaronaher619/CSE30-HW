.text
.global mystrfind
	
@initializes 'local variables'
mystrfind:
	@save the return address
	push {lr}
	@save r4
	push {r4}
	@save r5
	push {r5}
	@save r6
	push {r6}
	@save r7
	push {r7}
	@save r8
	push {r8}
	@save r9
	push {r9}
	@save r10
	push {r10}
	@save 0 to r6 for an index of tofind
	mov r6, #0
	@save string
	mov r3, r0
	@save tofind
	mov r4, r1
	@move tofind to r0 to use strlen
	mov r0, r1
	
@get lengths of the 2 strings
length:
	@get length of tofind
	bl mystrlen
	@store the length of tofind into r7
	mov r7, r0
	@move string into r0
	mov r0, r3
	@get length of string
	bl mystrlen
	@check if string is 0
	adds r0, r0, #0
	@if sting zero then return 0
	beq zerolength
	@store the length of string into r2
	mov r2, r0
	@subtract 1 to length to get last index
	sub r2, r2, #1
	@subtract 1 to length to get last index
	sub r7, r7, #1
	@store 0 into r0
	mov r0, #0
	@start to finding process
	b find
	
@change index of first string
factor:
	@add one to the factor for the string
	add r0, r0, #1
	@sub last index by current index
	subs r8, r2, r0
	@if zero then not found
	bmi notfound
	
@main loop of finding a char in tofin in string
find:
	@get a char from the string
	ldrb r1, [r3, r0]
	@get a char from tofind
	ldrb r5, [r4, r6]
	@compare it to the first char of the tofind
	subs r8, r1, r5
	@if its zero then it matches
	beq donemaybe
	@if not then check next char
	b factor
	
@checks if there is more of tofind to check is it is in string
@if so then change index of tofind
donemaybe:
	@flag that tofind index needs to be modified
	mov r9, #1
	@sub last index of tofind by current tofind index
	subs r8, r7, r6
	@if it equals zero then tofind was found
	beq found
	@if not at the end of the length of tofind then continue find loop
	@and add an index to tofind
	add r6, r6, #1
	b factor
	
@if sting is of zero length
zerolength:
	@move 0 into r0
	mov r0, #0
	@go to the end
	b end
	
@if tofind was found
found:
	@check r9 flag
	subs r9, r9, #1
	beq found2
	@go to the end
	b end
	
@if tofind was more than one char and need to get
@first occurance
found2:
	@get first occurance
	sub r0, r0, r7
	@go to end
	b end
	
@if tofind wasnt found
notfound:
	@move -1 to r0
	mov r0, #0xffffffff
	
@ends program and restores calling resigters
end:
	@get back original r10
	pop {r10}
	@get back original r9
	pop {r9}
	@get back original r8
	pop {r8}
	@get back original r7
	pop {r7}
	@get back original r6
	pop {r6}
	@get back original r5
	pop {r5}
	@get back original r4
	pop {r4}
	@go to return address
	pop {pc}
