	.text
	.global _start
@Initalizes registry
_start:
	mov r3, #0
@The loop to subrtact until zero or negative
loop:
	subs r0,  r0, r1
	beq divide
	bmi modulo	
	add r3, #1
	b loop
@If zero then no remainder and move the answer to r0
divide:
	add r3, #1
	mov r1, #0
	mov r0, r3
	b end
@If negative then make the remainder non-negative and
@add answeres to correct registries
modulo:
	add r0, r1, r0
	mov r1, r0
	mov r0, r3
	b end

end:

