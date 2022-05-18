email: joseph_scannell@student.uml.edu
Name: Joseph Scannell

i believe i should get 99% as i checked it with a random tester and its outputs match what it should
However their may be a bug I missed and dont want to risk loosing all points, however it follows
the algorithm the hardware uses.

The assignment had us add two floating point numbers by using integer operations.

How this is done is by calculating the difference between the exponents by subracting b.exponent
from a.exponent

then we slam the hidden bit into the mantissa IF the exponent of each float is not 0 
Then we artificially extend precision so that rounding can occur by shifting the floats to fill a
31 bit int

then we shift a or b based on the sign of the difference of the exponents, if negative a gets shifted
right by abs(difference of exponents)
if positive then we shift b right by abs(difference of exponents)

then we add the two mantissa together

then we calculate the rounding digit by taking the last 6 digits and dividing by 0x20.

then we shift mantissa to fit 24 bits and add the rounding bit to it.
then we calculate exponent by taking the max of both exponents

then if the 25th bit exists then increment exponent then right shift mantissa by 1.

if exponent = 0xFF, then we set mantissa to 0



IT TOOK SO LONG TO FIND OUT ABOUT THE ROUNDING BIT!


https://en.wikipedia.org/wiki/Floating-point_arithmetic#Addition_and_subtraction
> The lowest three digits of the second operand (654) are essentially lost. This is round-off 
> error. In extreme cases, the sum of two non-zero numbers may be equal to one of them:
>
>   e=5;  s=1.234567
> + e=−3; s=9.876543
>   e=5;  s=1.234567
> + e=5;  s=0.00000009876543 (after shifting)
> ----------------------
>   e=5;  s=1.23456709876543 (true sum)
>   e=5;  s=1.234567         (after rounding and normalization)
> In the above conceptual examples it would appear that a large number of extra digits would need 
> to be provided by the adder to ensure correct rounding; however, for binary addition or 
> subtraction using careful implementation techniques only two extra guard bits and one extra 
> sticky bit need to be carried beyond the precision of the operands
 (Citation: Wikipedia explanation)
