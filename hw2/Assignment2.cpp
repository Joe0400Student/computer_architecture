#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

using namespace std;
#define CASE_COUNT 1000
typedef struct {
	unsigned mantissa:23;
	unsigned exponent:8;
	unsigned sign:1;
} mem;

typedef union{
	float val;
	mem memory;
} f_32;

f_32 add(f_32 a, f_32 b){
	
	int a_mantissa = (a.memory.mantissa | (a.memory.exponent ? 1 << 23 : 0)) << (31-24);
	int a_exponent = a.memory.exponent;
	int b_mantissa = (b.memory.mantissa | (b.memory.exponent ? 1 << 23 : 0)) << (31-24);
	int b_exponent = b.memory.exponent;
	
	int exp_diff = a_exponent-b_exponent;

	int exponent = max(a_exponent,b_exponent);
	if(exp_diff < 0)
		if(exp_diff < -31)
			a_mantissa = 0;
		else
			a_mantissa >>= -exp_diff;
	else if(exp_diff > 0)
		if(exp_diff > 31)
			b_mantissa = 0;
		else
			b_mantissa >>= exp_diff;
	
	int mantissa = (a_mantissa + b_mantissa);
	int round = (mantissa % (1 << 7))/(1<<6);
	mantissa >>= 7;
	mantissa += round;
	if(mantissa & 1<<24){
		mantissa >>= 1;
		exponent++;
	}
	
	f_32 ret;
	ret.memory.sign = 0;
	ret.memory.mantissa = exponent == 0xFF? 0: mantissa;
	ret.memory.exponent = exponent;

	return ret;
}

string print_segment(ostringstream& s);

void format_f32(f_32 f){
	ostringstream a,b,c;
	a << bitset<1>(f.memory.sign);
	b << bitset<8>(f.memory.exponent);
	c << bitset<23>(f.memory.mantissa);
	cout << print_segment(a) << print_segment(b) << print_segment(c);
}
string print_segment(ostringstream& s){
	string strs = s.str();
	for(int i = strs.size()-1;i>=0;i-=4){
		strs.insert(i+1," ");
	}
	return strs;
}

int main(int argc, char* argv[]){
	f_32 a, b;
	cout << "Please enter two positive floating point values each with:" << endl;
	cout << "    - no more than 6 significant figures" << endl;
	cout << "    - a value between   +   10**37 and 10**-37" << endl << endl;
	cout << "Enter Float 1: ";
	cin  >> a.val;
	cout << "Enter Float 2: ";
	cin  >> b.val;
	
	cout << endl;
	
	cout << "Original pattern of Float 1: ";
	format_f32(a);
	cout << endl;
	cout << "Original pattern of Float 2: ";
	format_f32(b);
	cout << endl;
	cout << "Bit pattern of result      : ";
	format_f32(add(a,b));
	cout << endl;
	cout << endl;
	cout << "EMULATEd FLOATING RESULT FROM PRINTF ==>>> " << add(a,b).val << endl;
	cout << "HARDWARE FLOATING RESULT FROM PRINTF ==>>> " << a.val + b.val << endl;
	cout << "*******************************************************************" << endl;

	return 0;
}
