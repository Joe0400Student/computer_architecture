#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <cctype>
#include <exception>
#include <memory>
#include <bitset>
#include <algorithm>

using std::remove_if;
using std::bitset;
using std::unique_ptr;
using std::to_string;
using std::exception;
using std::string;
using std::vector;
using std::regex;
using std::regex_match;
using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::smatch;
using std::regex_search;

#define ExceptionBuilder(ExceptionName, ExceptionString)\
class ExceptionName : exception{\
private: string why;\
public:\
    ExceptionName(string reason = ExceptionString){\
        this->why = reason;\
    }\
    const char* what() const throw(){\
        return this->why.c_str();\
    }\
};


ExceptionBuilder(TokenMissingException,"No matching token!")
ExceptionBuilder(InstructionMissingArgument,"Instruction is missing an argument")
ExceptionBuilder(NoMatchingToken,"Token is unresolvable!")

template <size_t N>
string get_bits(int value){
    return bitset<N>(value).to_string();
}

string convert6(int value){
    return get_bits<6>(value);
}
string convert8(int value){
    return get_bits<8>(value);
}
string convert12(int value){
    return get_bits<12>(value);
}
string convert16(int value){
    return get_bits<16>(value);
}



class Symbol{
private:
    string value;
    int reference;
public:
    Symbol(string value, int reference){
        this->value = value;
        this->reference = reference;
    }
    int get_reference(){
        return reference;
    }
    string get_symbol(){
        return value;
    }
    string return_object_line(){
        return get_symbol() + " " + to_string(get_reference());
    }
};

class Data{
private:
    string value;
    bool resolved;
    string reference;
    int length;
public:
    Data(string value){
        this->value = value;
        this->resolved = true;
    }
    Data(string value, string reference, int length){
        this->value = value;
        this->reference = reference;
        this->resolved = false;
        this->length = length;
    }
    Data(string value, int numeric, int length){
        this->value = value;
        this->length = length;
        this->resolved = false;
        this->insert_static_value(numeric);
    }
        
        
    bool is_resolved(){
        return resolved;
    }
    string get_reference(){
        return reference;
    }
    string get_value(){
        return value;
    }
    int get_reference_length(){
        return length;
    }
    string return_object_line(){
        string tmp = "";
        if(!this->is_resolved())
            switch(this->get_reference_length()){
                case 16:
                    tmp += 'F';
                    break;
                case 12:
                    tmp += 'U';
                    break;
                case 8:
                    tmp += 'H';
                    break;
                case 6:
                    tmp += 'Q';
                    break;
            };
        tmp += this->get_value();
        tmp += " ";
        if(this->is_resolved())
            return tmp;
        return tmp + " " + this->get_reference();
    }
    void update_refs(vector<Symbol> symbol_table){
        for(Symbol s: symbol_table){
            if(this->get_reference() == s.get_symbol()){
                this->insert_static_value(s.get_reference());
                return;
            }
        }
	for(auto a: symbol_table){
		std::cerr << a.get_symbol() << endl;
	}
        std::cerr << this->reference << endl;
        throw NoMatchingToken("No matching lables to " + this->get_reference() + " !");
    }
    void insert_static_value(int value){
        this->resolved = true;
        switch(this->get_reference_length()){
            case 16:
                this->value = convert16(value);
                return;
            case 12:
                this->value = this->value.substr(0,4) + convert12(value);
                return;
            case 8:
                this->value = this->value.substr(0,8) + convert8(value);
                return;
            case 6:
                this->value = this->value.substr(0,10) + convert6(value);
                return;
        }
    }
};
vector<string> split(string s, char delimiter){
    string tmp = "";
    vector<string> ret;
    for(int i = 0;i<s.size();i++){
        if(s[i] == delimiter){
            ret.push_back(tmp);
            tmp = "";
        }
        else{
            tmp += s[i];
        }
    }
    ret.push_back(tmp);
    return ret;
}

string ignore_char(string s, char c){
    string tmp;
    for(char cs : s)
        if(cs != c)
            tmp += cs;
    return tmp;
}

class Instruction{
private:
    string binary;
    int length;
    string mnem;
    regex regx;
public:
    Instruction(string binary, int length, string mnem){
        this->binary = binary;
        this->length = length;
        this->mnem = mnem;
        string reg;
        for(char c: mnem){
            reg += '[' + std::toupper(c) + std::tolower(c) + ']';
        }

        regx = regex(reg);
    }
    Instruction(string value){
        value = value.substr(1,value.size()-2);
        vector<string> splitted = split(value,',');
        string s_mnem = splitted[0];
        string s_widt = splitted[1];
        string s_binr = splitted[2];
        this->mnem = split(s_mnem,':')[1];
        this->binary = split(s_binr,':')[1];
        this->length = std::stoi(split(s_widt,':')[1]);
        this->mnem = ignore_char(this->mnem,'"');
        this->binary = ignore_char(this->binary,'"');
        string reg;
        for(char c: this->mnem){ 
            reg.push_back('[');
            reg.push_back(std::toupper(c)); 
            reg.push_back(std::tolower(c));
            reg.push_back(']');
        }
        this->regx = regex(reg);
    }
    regex get_regex(){
        return regx;
    }
    bool takes_operand(){
        return length != 0;
    }
    int operand_length(){
        return length;
    }
    string get_binary(){
        return binary;
    }
    string print(){
        return mnem + " : " + binary + " : " + std::to_string(length);
    }
    string get_mnem(){
        return mnem;
    }
};




class JSON{
private:
    string filename;
public:
    JSON(string filename){
        //cout << "here";
        this->filename = filename;
    }
    vector<Instruction> parse_json(){
        ifstream file;
        file.open(this->filename);
        string whole_file = "";
        while(file){
            string tmp = "";
            getline(file,tmp);
            whole_file += tmp + "\n";
        }
        file.close();
        regex whitespace("( |\t|\n)+");
        whole_file = regex_replace(whole_file,whitespace,"");
        regex find_inside("\\[.*\\]");
        smatch inside;
        regex_search(whole_file,inside,find_inside);
        string list = inside[0];
        smatch sets;
        regex grouping("\\{[^\\{]*\\}");
        vector<Instruction> retn;
        while(regex_search(list,sets,grouping)){
            retn.push_back(Instruction(sets[0]));
            list = sets.suffix().str();
        }

        return retn;
    }
};

string string_builder(string s){
    regex quote("\"");
    smatch matches;
    while(regex_search(s,matches,quote)){
        s = std::regex_replace(s,quote,"");
    }
    string ret = "";
    for(int i = 0;i < s.length(); i += 2){
        short value = s[i];
        if(i + 1 < s.length()){
            value += s[i+1] << 8;
        }
        ret += to_string(value) + " ";
    }
    return ret;
}

string pre_processor(string s){
    smatch matches;
    regex quotation("\"[^\"]*\"");
    while(regex_search(s,matches,quotation)){
        s = std::regex_replace(s,quotation,string_builder(matches[0]),std::regex_constants::format_first_only);
    }
    return s;
}

vector<string> parse_tokens(vector<Instruction> instructions, regex token, regex integer, vector<string> tokens, bool object_file){
    vector<Symbol> symbols;
    vector<Data> data;
    int instruction = 0;
    for(int i = 0;i < tokens.size();i++){
        if(regex_match(tokens[i],token)){
            symbols.push_back(Symbol(tokens[i],instruction));
            if(i + 1 < tokens.size() && regex_match(tokens[i+1],token)){
                data.push_back(
                    Data(
                        "0000",
                        tokens[i+1],
                        16
                    )
                );
                i++;
                instruction++;   
            }
        }
        else if(regex_match(tokens[i],integer)){
            data.push_back(
                Data(
                    convert16(stoi(tokens[i]))
                )
            );
            instruction++;
        }
        else{
            bool found = false;
            for(Instruction inst: instructions){
                if(regex_match(tokens[i],inst.get_regex())){
                    if(inst.takes_operand()){
                        if( i + 1 >= tokens.size()          || 
                           (!regex_match(tokens[i+1],token) &&
                           !regex_match(tokens[i+1],integer))){
                           throw TokenMissingException();
                        }
                        else if(regex_match(tokens[i+1],token)){
                            data.push_back(
                                Data(
                                    inst.get_binary(),
                                    tokens[i+1],
                                    inst.operand_length()
                                )
                            );

                            found = true;
                            i++;
                            instruction++;
                            break;
                        }
                        else{
                            data.push_back(
                                Data(
                                    inst.get_binary(),
                                    stoi(tokens[i+1]),
                                    inst.operand_length()
                                )
                            );
                            found = true;
                            i++;
                            instruction++;
                            break;
                        }  
                    }
                    else{
                        data.push_back(Data(inst.get_binary()));
                        found = true;
                        instruction++;
                        break;
                    }
                }   
            }
            if(!found){
                std::cerr << tokens[i] <<endl;
                throw NoMatchingToken();
            }
        }
    }
    vector<string> ret;
    
    if(object_file){
        for(int line_number = 0; line_number < data.size(); line_number++)
            ret.push_back(
                " " + to_string(line_number) + " " +
                data[line_number].return_object_line() + "\n"
            );
        ret.push_back(" 4096 x\n");
        for(Symbol s : symbols)
            ret.push_back(" " + s.return_object_line() + "\n");
    }else{
        for(Data& d: data){
            if(!d.is_resolved()){
                d.update_refs(symbols);
            }
            ret.push_back(d.get_value() + "\n");
        }
    }
    return ret;
}

int main(int argc, char** argv){
    if(argc == 1){
        cout << "No input arguments are provided! For help add the argument \"--help\" for information" << endl;
        return 1;
    }
    bool object_file = false;
    string file_name = "";
    for(int i = 1; i < argc; i++){
        string tmp(argv[i]);
        if(tmp == "--help"){
            cout << "This assembler was a completely different standard than to what was provided.\n"
                    "   This compiler uses a .json file with the embedded instructions inside of it\n"
                    "   How this works is that the compile sees the instruction_booklet.json, reads\n"
                    "   the booklet, and constructs the regular expressions to match the mnemonic\n"
                    "   It then looks that the width and stores it into an Instruction object which\n"
                    "   indicated whether or not it takes an argument. Then it uses the binary to \n"
                    "   indicate what opcode is responsible for which\n"
                    "\n"
                    "\n"
                    "       --help: Provides the help page for the compiler\n"
                    "       -o:     Compiles the object file for the provided input\n"
                    "\n"
                    "\n"
                    "Written by Joseph Scannell.\n";
            return 0;
        }
        if(tmp == "--object" || tmp == "-c" || tmp == "-o")
            object_file = true;
        else{
            file_name = tmp;
        }
    }
    if(file_name == ""){
        cout << "NO FILE NAME WAS PROVIDED!\n";
        return 1;
    }
    ifstream source;
    source.open(file_name);
    string value = "";
    while(source){
        string tmp;
        getline(source,tmp);
        value += tmp + '\n';
    }
    source.close();
    regex comments(";.*\n");
    regex whitespace("( |\n|\t)+");
    value = std::regex_replace(value,comments,"");
    value = std::regex_replace(value,whitespace," ");
    value = pre_processor(value);
    auto tokenized = split(value,' ');
    tokenized.erase(
        remove_if(
            tokenized.begin(),
            tokenized.end(),
            [](string s){ 
                return s == "";
            }
        ),
        tokenized.end()
    );
    regex symbol("[a-zA-Z\\-_\\.][a-zA-Z\\-_0-9]*:");
    regex integer("-?[0-9]+");
    JSON j("instruction_booklet.json");
    //std::cerr << "here";
    for(auto value: tokenized){
        //cout << value << endl;
    }
    //cout << endl << endl;
    auto instructions = j.parse_json();
    try{
        auto binary = parse_tokens(instructions, symbol, integer, tokenized, object_file);
        for(auto s: binary){
            cout << s;
        }
    }catch(const std::exception& e){
        cout << e.what() << endl;
        return -1;
    }
    return 0;
}
