email: joseph_scannell@student.uml.edu
name: joseph scannell
grade deserved: 50% (late by 50%)

I believe i deserve a 50% as it operates properly. 50% is taken off due to tardiness.
To get this to work, what i had done is made strings that i work into, so that i can copy to str1 so that i can reuse str1
i would copy over the intial part of the string, which is "THE SUM OF THE ADDITION IS: "to the str1
then i determine if the numbers were negative, and if they are id jump to negative
id then push n onto the stack

the for the function it would work like this:

int pos = 15;
short* str = &str1;
short handthrough;
void getn(int n){
	if(n == 0)
		return;
	int remainder = n % 10;
	int quotient = n / 10;
	if(quotient == 0){
		handthrough = ' ' + (remainder + '0') * 256;
		insert();
	}
	else{
		int remainder2 = quotient % 10
		getn( quotient / 10);
		pos++;
		handthrough = remainder2 + '0' + (remainder + '0') * 256;
		insert();
	}
	return;
}

void insert(){
	*(str + pos) = handthrough;
	return;
}
		

	
commands are in commands.txt
output files are in output.txt

