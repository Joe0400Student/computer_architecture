#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <bitset>

using std::bitset;
using std::regex;
using std::regex_search;
using std::smatch;
using std::ifstream;

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::exception;

using std::stoi;



#define ExceptionBuilder(Exception_Name, Exception_String)\
class Exception_Name: public exception{\
    public:\
        string value;\
        Exception_Name(string s = Exception_String){\
            value = s;\
        }\
        const char* what() const throw(){\
            return value.c_str();\
        }\
};\

template <size_t N> 
string string_get_bits(int number){
    return bitset<N>(number).to_string();
}


ExceptionBuilder(NoArgumentException,"No arguments are passed to the CLI interface, please provied arguments to the interface for the linker")
ExceptionBuilder(SymbolNotFoundException,"No symbol matching found in the symbol table");

class Code{
private:
    string references;
    int line;
    string code;
    bool refers_to_something;
public:
    Code(string code, int line, string refs){
        this->code = code;
        references = refs;
        this->line = line;
        refers_to_something = true;
    }
    Code(string code, int line){
        this->code = code;
        this->line = line;
        refers_to_something = false;
    }
    void offset(int v){
        line += v;
    }
    void print(){
        cout << line << ":" << code;
        if(refers_to_something){
            cout << ":" << references;
        }
        cout << endl;
    }
    int get_line(){
        return line;
    }
    bool refers(){
        return refers_to_something;
    }
    string reference(){
        return references;
    }
    void set_address(int address){
        switch(code[0]){
            case 'F':
                code = string_get_bits<16>(address);
                break;
            case 'U':
                code = code.substr(1,4) + string_get_bits<12>(address);
                break;
            case 'H':
                code = code.substr(1,8) + string_get_bits<8>(address);
                break;
	        case 'Q':
		        code = code.substr(1,10) + string_get_bits<6>(address);
		        break;
        }
    }
    string resolve(){
        return code;
    }
};

class Symbol{
private:
    string name;
    int position;
public:
    Symbol(string name, int position){
        this->name = name;
        this->position = position;
    }
    void print(){
        cout << this->name << ":" << position << endl;
    }
    void offset(int val){
        position += val;
    }
    string get_name(){
        return name;
    }
    int location(){
        return position;
    }
};

string reduce_whitespace(string s){
    string ret;
    bool whitespace = false;
    for(char c: s){
        if(!whitespace && (c == ' ' || c == '\t')){
            whitespace = true;
            ret += " ";
        }
        else if(c != ' ' && c != '\t'){
            whitespace = false;
            ret += c;
        }
    }
    return ret;
}

vector<string> split_whitespace(string s){
    vector<string> ret;
    s = reduce_whitespace(s);
    if(s.size() == 0)
        return ret;
    s = s.substr(1);
    string tmp = "";
    for(char c: s){
        if(c == ' '){
            ret.push_back(tmp);
            tmp = "";
        }
        else{
            tmp += c;
        }
    }
    if(tmp != "")
        ret.push_back(tmp);
    return ret;
}

class Object{
private:
    string filename;
    vector<Symbol> symbols;
    vector<Code> code_lines;
public:
    Object(string filename){
        this->filename = filename;
    }
    void read_in(){
        ifstream file;
        file.open(this->filename);
        bool symbol = false;
        string response;
        smatch m;
        while(file){
            getline(file,response);
//            cout << response;
            if(regex_search(response,m,regex("4096 x"))){
                symbol = true;
            }else{
                vector<string> split = split_whitespace(response);
                if(split.size() == 0)
                    break;
                if(symbol)
                    symbols.push_back(Symbol(split[0],stoi(split[1])));
                else{
                    if(split.size() == 2)
                        code_lines.push_back(Code(split[1],stoi(split[0])));
                    else
                        code_lines.push_back(Code(split[1],stoi(split[0]),split[2]));
                }
            }
        }
        file.close();
    }
    
    void print(){
        cout << filename << ":" << endl;
        cout << "\tsymbols:" << endl;
        for(Symbol s: symbols){
            cout << "\t\t";
            s.print();
        }
        cout << "\tcode:" << endl;
        for(Code c: code_lines){
            cout << "\t\t";
            c.print();
        }
    }
    void offset_code(int v){
        for(Code& c: code_lines){
            c.offset(v);
        }
    }
    void offset_symbol(int v){
        for(Symbol& s: symbols){
            s.offset(v);
        }
    }
    vector<Symbol> get_symbols(){
        return symbols;
    }
    vector<Code> get_code(){
        return code_lines;
    }
};

int main(int argc, char** argv){
    if(argc == 1){
        throw NoArgumentException();
    }

    vector<Object> objects;
    for(int i = 1;i<argc;i++){
        string tmp(argv[i]);
        objects.push_back(Object(tmp));
    }
    
    vector<Symbol> symbol_table;
    vector<Code> code_lines;
    
    for(Object& o: objects){
        o.read_in();
    }

    for(Object o: objects){
        int offset = code_lines.size();
        if(code_lines.size() != 0){
            o.offset_symbol(offset);
            o.offset_code(offset);
        }
        for(auto c: o.get_code())
            code_lines.push_back(c);
        for(auto s: o.get_symbols())
            symbol_table.push_back(s);
    }

    for(Code &c: code_lines){
        if(c.refers()){
            bool found = false;
            for(Symbol s: symbol_table){
                if(s.get_name() == c.reference()){
                    c.set_address(s.location());
                    found = true;
                    break;
                }
            }
            if(!found){
                throw SymbolNotFoundException(c.reference() + " was not found in the existing symbol table");
            }
        }
    }
    for(Code c: code_lines)
        cout << c.resolve() << endl;

    return 0;
}

