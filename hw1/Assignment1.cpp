#include <iostream>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;
struct segmented_memory{
    unsigned int mantissa:23;
    unsigned int exponent:8;
    unsigned int sign:1;
};

union Fhex{
    unsigned int num_for_bin;
    float num;
    struct segmented_memory seg_mem;
};

string convert_stream_to_string(std::ostringstream& stre){
    string val = stre.str();
    for(int i = val.size()-1; i>0; i-=4)
        val.insert(i+1," ");
    return val;
}



string get_size(float val){
	std::ostringstream input;
	input << ((fabs(val) > 100000 || fabs(val) < 0.000001) && val != 0 ? scientific : fixed); 
 	if((fabs(val) > 100000 || fabs(val) < 0.000001 ) && val != 0.0){
		input << setprecision(2);
	}
	else{
		input << setprecision(6);
	}
	input << val << " ";
	return input.str().substr(0,9);
}

int main(int argc, char* argv[]){
    union Fhex f;
    cin >> f.num;
    
    std::ostringstream mantissa, exponent, sign;
    mantissa << bitset<23>(f.seg_mem.mantissa);
    exponent << bitset<8>(f.seg_mem.exponent);
    sign << bitset<1>(f.seg_mem.sign);
    
    cout << "the floating value for " << f.num << " is broken out as:" << endl;
    cout << "   mantissa: 0x" << hex << setfill('0') << setw(6) << f.seg_mem.mantissa << 
            "   or:             " << convert_stream_to_string(mantissa) << endl;
    cout << "   exponent: 0x" << hex << setfill('0') << setw(2) << f.seg_mem.exponent <<
            "       or:   " << convert_stream_to_string(exponent) << endl;
    cout << "       sign: 0x" << hex << setfill('0') << setw(1) << f.seg_mem.sign <<  
            "        or: " << convert_stream_to_string(sign) << endl;
    cout << " in base 10: " << get_size(f.num) << "  or: " << 
            convert_stream_to_string(sign) << " " << convert_stream_to_string(exponent) << "" <<
            convert_stream_to_string(mantissa) << endl;
    
    return 0;
}
