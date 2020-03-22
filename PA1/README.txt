1.	a) Mystery file 1 had the opcode of "0001" which is the EOR operation with register 2 being Rn,
           register 1 being Rm and Register 0 being Rd. If x is 8,2,15 and y is 2,2,10 then the
	   results are 10,0,5 respectively. This makes sense with an operation of EOR being done since
	   it is indeed true that if x was 15 and y was 10 the result would be 5 as seen.

     	b) Mystery file 2 had the opcode of "0000" which is the AND operation with register 2 being Rn,
           register 1 being Rm and Register 0 being Rd.  If x is 8,2,15 and y is 2,2,10 then the
	   results are 0,2,5 respectively. This makes sense with an operation of AND being done since
	   it is indeed true that if x was 8 and y was 2 the result would be 0 as seen.

	c) Mystery file 3's first line has the opcode of "000" which is the multiplication operation
	   with register 3 being Rd, register 2 being Rn and register 1 being Rm. The second line of
	   the file has the opcode "0100" which is the  ADD operation with register 2 being Rn,
	   register register 0 being Rd and register 3 being Rm. If x was 8,2,15 and y was 2,2,10 then
	   R0 is 18,6,165 and r3 is 16,4,150 respectively. This makes sense since if x was 8 and y was
	   2 then when multiplied it would store 16 into R3 and then add R3 (16) to R2 (2) to store 18
	   into R0 which is indeed true as we see with the results.
	   
2.	The first reverse is important because the bits go from 0-31 right to left which helps us read
	it but we need it to go 0-31 left to right for the machine code. The second reverse of the
	individual bytes are	important because the most significant bit is stored at the end of
	byte when it needs to be at the left or beginning of the byte.

3.	If Rm is r1 which is located at the beginning of the machine code then only the second
	hexadecimal letter would change and if r1 is Rn which is located in the middle of the machine
	code then the sixth hexadecimal letter would change depending on what the new register is
	chosen.
