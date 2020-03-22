1. in memory you will see
0x50 61626364
0x54 00000000

Each character needs a byte because a char is represented in 8 bits
 in order to include ascii and a byte is 8 bits. 

2. You can do it by finding the length of the first string which is the
 index to the byte after the string ends. So then you can get the first
 char from the second string and store in in the index that was found. 
 Then you add one to the index and get the next char and store it until
 you reach the end of the second string. Then store the end byte for a
 string to signal the end.

3. The information a function needs to preserve is all the calling
 registers which are r4-r11 and r0-r3 to if they are not parameters
 for the function. It also needs to preserve the address where the function 
 was called from in order to return to where it was called from
 and not some random place.
