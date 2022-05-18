email: joseph_scannell@student.uml.edu
name: joseph scannell
grade deserved: 100%

I believe i deserve a 100% as it operates properly. 
RSHIFT worked outta gate
MULT i had to pull off the stack, mask out the variable to count against
then i had to check to see if the sign of the count variable is different than the sign of the one from the stack
if it is then i have to set accumulator to negative one
else i keep doing it then push it onto the stack

for div i create two variables and read from the stack for the numerator and denominator
if the denominaotr is zero, then i push -1, 0 onto the stack then return
else
i set two more variables to (0,1) (numerator_sign,denominator_sign)
if the numerator is negative, set value of numerator sign to negative, and invert
if the denominator is negative, i keep it the same,
else i set the denominator sign to zero
i set f to numerator
i set e to 0
while f > 0:
	f = f -denominator
	e++;
if f < 0:
	f = f + denominator
	e--;
if(numeratorsign + denominator sign != 0){
	e = -e;
}
if(numeratorsign != 0){
	f = -f;
}
push e, f onto stack
then return


	
commands are in commands.txt
output files are in output.txt

