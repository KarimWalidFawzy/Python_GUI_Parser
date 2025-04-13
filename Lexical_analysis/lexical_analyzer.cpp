#include "lexical_analyzer.hpp"
/**
 * This Function will parse the file contents into tokens
 */
#include <map>
std::vector <token> fileparser(const char* filePath){
    using namespace std;
    vector <token> listoftokens;
    ifstream fin(filePath);
    std::string fileContents="echo ";
    std::string FF;
    while (getline(fin,FF))
    {
        if(FF[0]!='#')
        fileContents+=(fileContents.back()=='\\')?(FF):(FF+";");
    }
    for(int i=0;i<fileContents.size();i++){
        switch (fileContents[i])
        {
        case ';':
            listoftokens.push_back(token(EOL));
            break;
        case ' ':
            listoftokens.push_back(token(identation));
        break;
        case '+':
            listoftokens.push_back(token(Plus));
        break;
        case '-':
            listoftokens.push_back(token(Minus));
        break;
        case '*':
            if(fileContents[i+1]=='*'){listoftokens.push_back(token(power));i++;}
            else listoftokens.push_back(multiply);
        break;
        case '/':
          listoftokens.push_back(token(divide));
        break;
        case '(':
            listoftokens.push_back(token(open_bracket));
        break;
        case ')':
            listoftokens.push_back(token(closed_bracket));
        break;
        case '!':
            listoftokens.push_back(token(not_operator_symbol));
        break;
        case '\"':
            listoftokens.push_back(token(double_quotation));
        break;
        case '%':
            listoftokens.push_back(token(mod_operator));
        break;
        case '\'':
            listoftokens.push_back(token(single_quotation));
        break;
        case '&':
            listoftokens.push_back(token(and_operator_symbol));
        break;
        case ',':
            listoftokens.push_back(token(comma));
        break;
        case '.':
            listoftokens.push_back(token(dot));
        break;
        case ':':
            listoftokens.push_back(token(colon));
        break;
        case '~':
            listoftokens.push_back(token(bitwise_not));
        break;
        case '|':
            listoftokens.push_back(token(bitwise_or));
        break;
        case '^':
            listoftokens.push_back(token(bitwise_xor));
        break;
        case '[':
            listoftokens.push_back(token(open_square));
        break;
        case ']':
            listoftokens.push_back(token(close_square));
        break;
        case '{':
            listoftokens.push_back(token(open_curly));
        break;
        case '}':
            listoftokens.push_back(token(close_curly));
        break;
        case '<':
            if(fileContents[i+1]=='<'){listoftokens.push_back(token(bitwise_shift_left));i++;}
            else if(fileContents[i+1]=='='){listoftokens.push_back(lessthanorequalto);i++;}
            else listoftokens.push_back(token(lessthan));
        break;
        case '>':
            if(fileContents[i+1]=='>'){listoftokens.push_back(token(bitwise_shift_right));i++;}
            else if(fileContents[i+1]=='='){listoftokens.push_back(greaterthanorequalto);i++;}
            else listoftokens.push_back(token(greaterthan));
        break;
        case '=':
            if(fileContents[i+1]=='='){listoftokens.push_back(equality);i++;}
            else listoftokens.push_back(token(assignment));
        break;
        default:
            
            break;
        }
    }
    system(fileContents.c_str());
    return listoftokens;
}
token::token(std::string id){
    this->id=id;
}
std::string reservedFunctionToString(reserved_functions);
token::token(reserved_functions R){
    this->id=reservedFunctionToString(R);
    this->Type=reserve_function;
}
std::string reservedFunctionToString(reserved_functions func) {
    switch (func) {
        case print: return "print";
        case len: return "len";
        case Abs: return "abs";
        case enumerate: return "enumerate";
        case aiter: return "aiter";
        case all: return "all";
        case anext: return "anext";
        case any: return "any";
        case ascii: return "ascii";
        case bin: return "bin";
        case Bool: return "bool";
        case breakpoint: return "breakpoint";
        case bytearray: return "bytearray";
        case bytes: return "bytes";
        case callable: return "callable";
        case chr: return "chr";
        case classmethod: return "classmethod";
        case compile: return "compile";
        case complex: return "complex";
        case delattr: return "delattr";
        case dict: return "dict";
        case dir: return "dir";
        case divmod: return "divmod";
        case eval: return "eval";
        case exec: return "exec";
        case filter: return "filter";
        case Float: return "float";
        case format: return "format";
        case frozenset: return "frozenset";
        case getattr: return "getattr";
        case globals: return "globals";
        case hasattr: return "hasattr";
        case hash: return "hash";
        case help: return "help";
        case hex: return "hex";
        case id: return "id";
        case input: return "input";
        case Int: return "int";
        case isinstance: return "isinstance";
        case issubclass: return "issubclass";
        case iter: return "iter";
        case list: return "list";
        case locals: return "locals";
        case Map: return "map";
        case max: return "max";
        case memoryview: return "memoryview";
        case min: return "min";
        case next: return "next";
        case object: return "object";
        case oct: return "oct";
        case open: return "open";
        case ord: return "ord";
        case pow: return "pow";
        case property: return "property";
        case range: return "range";
        case repr: return "repr";
        case reversed: return "reversed";
        case round: return "round";
        case set: return "set";
        case setattr: return "setattr";
        case slice: return "slice";
        case sorted: return "sorted";
        case staticmethod: return "staticmethod";
        case str: return "str";
        case sum : return "sum";
        case super: return "super";
        case tuple: return "tuple";
        case type: return "type";
        case vars: return "vars";
        case zip: return "zip";
        case __import__: return "__import__";
        default: return "invalid_reserved_function";
    }
}

token::token(reserved_keywords res){
    this->res_key=res;
    this->Type=reserved_keyword;
    switch (res)
    {
    case False:
        this->id="False";
        break;
    case None:
        this->id="None";
        break;
    case True:
        this->id="True";
        break;
    case AND:
        this->id="and";
        break;
    case as:
        this->id="as";
        break;     
    case assert:
        this->id="assert";
        break; 
    case async:
        this->id="async";
        break; 
    case await:
        this->id="await";
        break;
    case Break:
        this->id="break";
        break;
    case Class:
        this->id="class";
        break;
    case Continue:
        this->id="continue";
        break;
    case def:
        this->id="def";
        break;
    case elif:
        this->id="elif";
        break;
    case Else:
        this->id="else";
        break;
    case except:
        this->id="except";
        break;
    case finally:
        this->id="finally";
        break;
    case For:
        this->id="for";
        break;
    case from:
        this->id="from";
    break;
    case global:
        this->id="global";
        break;
    case If:
        this->id="if";
    break;
    case import:
    this->id="import";
    break;
    case in:
    this->id="in";
    break;
    case is:
    this->id="is";
    break;
    case lambda:
    this->id="lambda";
    break;
    case nonlocal:
    this->id="nonlocal";
    break;
    case Not:
    this->id="not";
    break;
    case Or:
    this->id="or";
    break;
    case pass:
    this->id="pass";
    break;
    case Raise:
    this->id="raise";
    break;
    case Return:
    this->id="return";
    break;
    case Try:
    this->id="try";
    break;
    case While:
    this->id="while";
    break;
    case with:
    this->id="with";
    break;
    case yield:
    this->id="yield";
    break;
    }
}
token::token(float num){
    this->id=std::to_string(num);
}
token::token(tokentype T){
    this->Type=T;
    if(T!=reserve_function && T!=reserved_keyword){
        switch (T)
        {
        case identation:
            this->id=" ";
            break;
        
        default:
            break;
        }
    }
}
std::string token::getID(){
    return this->id;
}
tokentype token::getType(){
    return this->Type;
}
/**
 * ID : [(a-z)|(A-Z)|_] 
 */