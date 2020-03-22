1. In order to get something fragmented you would need to have small chucks
 of free memory between the occupied space. Once all space is full on heap
 when you try to malloc more for a relatively small memory request then you
 would get beck NULL even though there is still lots of free space. This is
 because all the free space is in small chunks.

2. A workload that would be faster if the free list was reversed would be
 if all the small spaces are in the begining. Lets say there are 30 4 bit
 free spaces at the begining of the list and the largest (ex 100) is at
 the end. Then it would be faster if you searched at the end first, therby
 searching the list in reverse.
