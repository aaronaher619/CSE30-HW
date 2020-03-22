	.text	
	.global _start

@initializes registries
_start:
	mov r2, r0
	mov r6, r0
	mov r3, r1
	mov r4, r1
	mov r9, #4
@decides whether the upper or lower byte will be used
step1:
	lsls r3, #17
	bcs upperbyte
	b lowerbyte
@Case in which upper byte is chosen
upperbyte:
	lsr r1, #8
	b and_eor
@Cse in which lower byte is chosen
lowerbyte:
	lsl r1, #24
	lsr r1, #24
	b and_eor
@Does the AND and EOR operation to get encrypted charater
@Also initializes other registries
and_eor:
	and r1, r1, #0x1F
	eor r0, r1, r0
	mov r1, r4
	mov r5, r0
@This multiplies the old key by 4
step2:
	mul r1, r9, r1
@This step calculates whether finding an N is possible or not
step3:
	subs r5, #11
	mov r9, #6
	mov r5, r0
	bmi step3a
	b step3b
@This step means N cannot be calculates
@So then add by the old character
step3a:	
	add r1, r0, r1
	b step4
@This step restats the registries that are involved in the loop
restartloop:
	add r9, #1
	mov r5, r0
@This means N is possible to find and starts evaluating N
@Starting with 6 and so on
step3b:
	subs r5, r5, r9
	bmi modulo
	b step3b
@This step means that is checking to see if the modulo is 5
@If not then restart loop
modulo:
	add r5, r5, r9
	subs r5, #5
	beq step3c
	b restartloop
@This step Then adds the found N
step3c:
	add r1, r1, r9
@This step divides by 2
step4:	
	lsr r1, #1
@This step subracts by the old character
step5:
	sub r1, r1, r6
	mov r9, #0
@This step is to shift the value until it reaches the far left and does a carry
step6:
	mov r5, r1
	lsls r1, #1
	bcs step6a
	lsls r1, #1
	add r9, #1	
	b step6
@This step decides if it is bigger than 2 bytes
@Depening on when the carry happened
step6a:
	subs r9, #16
	bmi step6c
@If it is bigger than 2 bytes then do the nesseccary amount of shifts
step6b:
	add r9, #16
	lsr r5, r9
	mov r1,r5
	b step7
@If it is 2 bytes then get original value back and leave as is
step6c:
	lsr r5, #16
	mov r1, r5
@This step flips the most significant bit
step7:
	lsl r1, #16
	add r1, #0x80000000
	lsr r1, #16
end:
	@mov r7, #1
	@svc #0
	
