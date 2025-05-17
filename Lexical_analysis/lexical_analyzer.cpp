#include "lexical_analyzer.hpp"
/**
 * This Function will parse the file contents into tokens
 */

std::string idgetter(std::string & strtobeparsed, int index){
    //This function takes the string and 
    int L=1;
    using namespace std;
    regex identifier_pattern(R"([a-zA-Z_][a-zA-Z0-9_]*)");
    while (regex_match(strtobeparsed.substr(index,L),identifier_pattern))
    {
        L++;
    }
    L--;
    return strtobeparsed.substr(index,L);        
}
std::vector <token> fileparser(const char* filePath){
    using std::vector;
    using std::string;
    vector <token> listoftokens;
    using std::stack;
    using std::getline;
    std::ifstream fin(filePath);
    string fileContents="";
    string FF;
    stack <char> nbb,sbb,cbb,dqb,sqb;
    while (getline(fin,FF))
    {
        if(FF[0]!='#')
        fileContents+=(fileContents.back()=='\\')?(FF):(FF+";");
    }
    unsigned int Length= fileContents.size(); 
    for(int i=0;i<Length;i++){
        switch (fileContents[i])
        {
        case ';':
            listoftokens.push_back(token(EOL));
            break;
        case ' ':
            listoftokens.push_back(token(identation));
        break;
        case '+':
            if (fileContents[i+1]=='=') {listoftokens.push_back(token(plusequal));i++;}
            else
            listoftokens.push_back(token(Plus));
        break;
        case '-':
        if (fileContents[i+1]=='=') {listoftokens.push_back(token(minusequal));i++;}
        else if (fileContents[i+1]=='>') {listoftokens.push_back(token(rarrow));i++;}
        else    listoftokens.push_back(token(Minus));
        break;
        case '*':
            if(fileContents[i+1]=='*'&&fileContents[i+2]!='='){listoftokens.push_back(token(power));i++;}
            else if (fileContents[i+1]=='=') {listoftokens.push_back(token(mulequal));i++;}
            else if (fileContents[i+1]=='*'&&fileContents[i+2]=='=') {listoftokens.push_back(token(pow_equal));i+=2;}
            else listoftokens.push_back(token(multiply));
        break;
        case '/':
        if (fileContents[i+1]=='=') {listoftokens.push_back(token(divequal));i++;}
        else if (fileContents[i+1]=='/') {listoftokens.push_back(token(double_divide));i++;}
        else if (fileContents[i+1]=='/'&&fileContents[i+2]=='=') {listoftokens.push_back(token(doubledivideequal));i++;}
        else   listoftokens.push_back(token(divide));
        break;
        case '(':
            listoftokens.push_back(token(open_bracket));
            nbb.push('(');
        break;
        case ')':
            listoftokens.push_back(token(closed_bracket));
            nbb.pop();
        break;
        case '!':
            if (fileContents[i+1]=='=') {i++; listoftokens.push_back(token(notequalto));}
            else
            listoftokens.push_back(token(not_operator_symbol));
        break;
        case '@':
            if(fileContents[i+1]=='='){listoftokens.push_back(token(atequal));i++;}
            else listoftokens.push_back(token(at_operator));
        break;
        case '\"':
            listoftokens.push_back(token(string_tkn));
            if(dqb.empty()){dqb.push('\"');int lenofstr=0; while (fileContents[i+1+lenofstr]!='\"' && fileContents.substr(i+1+lenofstr,2)!="\\\""){lenofstr++;}listoftokens.back().setstring(fileContents.substr(i,lenofstr));i+=lenofstr;} else dqb.pop();
        break;
        case '%':
        if (fileContents[i+1]=='=') {listoftokens.push_back(token(modequal));i+=2;}
            listoftokens.push_back(token(mod_operator));
        break;
        case '\'':
            listoftokens.push_back(token(string_tkn));
            if(sqb.empty()){sqb.push('\'');int lenofstr=0; while (fileContents[i+1+lenofstr]!='\''&& fileContents.substr(i+1+lenofstr,2)!="\\\'"){lenofstr++;}listoftokens.back().setstring(fileContents.substr(i+1,lenofstr));i+=lenofstr;} else sqb.pop();
            break;
        case '&':
        if (fileContents[i+1]=='=') {listoftokens.push_back(token(andequal));i+=2;}
        else listoftokens.push_back(token(and_operator_symbol));
        break;
        case ',':
            listoftokens.push_back(token(comma));
        break;
        case '.':
            if(fileContents.substr(i,3)=="..."){listoftokens.push_back(token(ellipsis));i+=2;}
            else
            listoftokens.push_back(token(dot));
        break;
        case ':':
            if(fileContents[i+1]=='=') {listoftokens.push_back(token(colequal));i++;}
            else listoftokens.push_back(token(colon));
        break;
        case '~':
            listoftokens.push_back(token(bitwise_not));
        break;
        case '|':
        if (fileContents[i+1]=='=') {listoftokens.push_back(token(orequal));i++;}
            listoftokens.push_back(token(bitwise_or));
        break;
        case '^':
        if (fileContents[i+1]=='=') {listoftokens.push_back(token(xorequal));i++;}
        else  listoftokens.push_back(token(bitwise_xor));
        break;
        case '[':
            listoftokens.push_back(token(open_square));
            sbb.push('[');
        break;
        case ']':
            listoftokens.push_back(token(close_square));
            sbb.pop();
        break;
        case '{':
            listoftokens.push_back(token(open_curly));
            cbb.push('{');
        break;
        case '}':
            listoftokens.push_back(token(close_curly));
            nbb.pop();
        break;
        case '<':
            if(fileContents[i+1]=='<'){listoftokens.push_back(token(bitwise_shift_left));i++;}
            else if(fileContents[i+1]=='='){listoftokens.push_back(token(lessthanorequalto));i++;}
            else if(fileContents[i+1]=='<'&&fileContents[i+2]=='='){listoftokens.push_back(token(shifteql));i+=2;}
            else listoftokens.push_back(token(lessthan));
        break;
        case '>':
            if(fileContents[i+1]=='>'){listoftokens.push_back(token(bitwise_shift_right));i++;}
            else if(fileContents[i+1]=='='){listoftokens.push_back(token(greaterthanorequalto));i++;}
            else if(fileContents.substr(i,3)==">>="){listoftokens.push_back(token(shifteqr));i+=2;}
            else listoftokens.push_back(token(greaterthan));
        break;
        case '=':
            if(fileContents[i+1]=='='){listoftokens.push_back(token(equality));i++;}
            else listoftokens.push_back(token(assignment));
        break;
        case 'a':
            if(fileContents.substr(i,3)=="and"){i+=3;listoftokens.push_back(token(AND));}
            else if(fileContents.substr(i,2)=="as"){i+=2;listoftokens.push_back(token(as));}
            else if(fileContents.substr(i,6)=="assert"){i+=6;listoftokens.push_back(token(assert));}
            else if(fileContents.substr(i,5)=="async"){i+=5;listoftokens.push_back(token(async));}
            else if(fileContents.substr(i,5)=="await"){i+=5;listoftokens.push_back(token(await));}
            else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
            break;
        case 'b':
        if(fileContents.substr(i,5)=="break"){i+=5;listoftokens.push_back(token(Break));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'c':
        if(fileContents.substr(i,5)=="class"){i+=5;listoftokens.push_back(token(Class));}
        else if(fileContents.substr(i,8)=="continue"){i+=8;listoftokens.push_back(token(Continue));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'd':
        if(fileContents.substr(i,3)=="def"){i+=3;listoftokens.push_back(token(def));}
        else if(fileContents.substr(i,3)=="del"){i+=3;listoftokens.push_back(token(del));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'e':
        if(fileContents.substr(i,4)=="else"){i+=4;listoftokens.push_back(token(Else));}
        else if(fileContents.substr(i,4)=="elif"){i+=4;listoftokens.push_back(token(elif));}
        else if(fileContents.substr(i,6)=="except"){i+=6;listoftokens.push_back(token(except));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'F':
        if(fileContents.substr(i,5)=="False"){i+=5;listoftokens.push_back(token(False));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'f':
        if(fileContents.substr(i,3)=="for"){i+=3;listoftokens.push_back(token(For));}
        else if(fileContents.substr(i,4)=="from"){i+=4;listoftokens.push_back(token(from));}
        else if(fileContents.substr(i,7)=="finally"){i+=7;listoftokens.push_back(token(finally));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'g':
        if(fileContents.substr(i,6)=="global"){i+=6;listoftokens.push_back(token(global));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'i':
        if(fileContents.substr(i,2)=="if"){i+=2;listoftokens.push_back(token(If));}
        else if(fileContents.substr(i,6)=="import"){i+=6;listoftokens.push_back(token(Import));}
        else if(fileContents.substr(i,2)=="in"){i+=2;listoftokens.push_back(token(in));}
        else if(fileContents.substr(i,2)=="is"){i+=2;listoftokens.push_back(token(is));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'l':
        if(fileContents.substr(i,6)=="lambda"){i+=6;listoftokens.push_back(token(lambda));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'n':
        if(fileContents.substr(i,8)=="nonlocal"){i+=8;listoftokens.push_back(token(nonlocal));}
        else if(fileContents.substr(i,3)=="not"){i+=3;listoftokens.push_back(token(Not));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();}
        break;
        case 'N':
        if(fileContents.substr(i,4)=="None"){i+=4;listoftokens.push_back(token(None));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'o':
        if(fileContents.substr(i,2)=="or"){i+=2;listoftokens.push_back(token(Or));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'p':
        if(fileContents.substr(i,4)=="pass"){i+=4;listoftokens.push_back(token(pass));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
        case 'r':
        if(fileContents.substr(i,5)=="raise"){i+=5;listoftokens.push_back(token(Raise));}
        else if(fileContents.substr(i,6)=="return"){i+=6;listoftokens.push_back(token(Return));}
        else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
        break;
            case 't':
            if(fileContents.substr(i,3)=="try"){i+=3;listoftokens.push_back(token(Try));}
            else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
            break;
            case 'T':
            if(fileContents.substr(i,4)=="True"){i+=4;listoftokens.push_back(token(True));}
            else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
            break;
            case 'w':
            if(fileContents.substr(i,5)=="while"){i+=5;listoftokens.push_back(token(While));}
            else if(fileContents.substr(i,4)=="with"){i+=4;listoftokens.push_back(token(with));}
            else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
            break;
            case 'y':
            if(fileContents.substr(i,5)=="yield"){i+=5;listoftokens.push_back(token(yield));}
            else {string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));}
            break;
        default:
        //identifierdetectortotoken();
        string iD=idgetter(fileContents,i);i+=iD.size();listoftokens.push_back(token(iD));
            break;
        }
    }
    if(!sbb.empty() || !cbb.empty() || !nbb.empty()){
        MessageBoxA(0,"Error, brackets not balanced", "Error", MB_OK);
    } else {
        system("echo Success, brackets are balanced");
    }
    if (!sqb.empty() || !dqb.empty())
    {
        MessageBoxA(0,"Error, brackets not balanced", "Error", MB_OK);
    }
    else 
    {
        system("echo Quotation marks balanced");
    }    
    fin.close();
    return listoftokens;
}
std::string reservedFunctionToString(reserved_functions);
token::token(std::string id){
    this->id=id;
    this->Type=identifier;
    reserved_functions RF;
    for (RF =(reserved_functions)0; RF <__import__ ; RF=(reserved_functions)(1+RF))
    {
        if (id==reservedFunctionToString(RF))
        {
            this->Type=reserve_function;
            this->function=RF;
            break;
        }        
    }    
}
std::string reservedFunctionToString(reserved_functions);
reserved_functions stringtoreserved(std::string id){
    reserved_functions RF;
    for (RF =(reserved_functions)0; RF <__import__ ; RF=(reserved_functions)(1+RF))
    {
        if (id==reservedFunctionToString(RF))
        {
            return RF;
        }        
    }
    return __import__;
}
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
        case Pow: return "pow";
        case property: return "property";
        case range: return "range";
        case repr: return "repr";
        case reversed: return "reversed";
        case Round: return "round";
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
std::string get_token_name(tokentype type) {
    switch (type) {
        case reserved_keyword:
            return "reserved_keyword";
        case identifier:
            return "identifier";
        case number:
            return "number";
        case identation:
            return "identation";
        case EOL:
            return "EOL";
        case reserve_function:
            return "reserve_function";
        case Plus:
            return "Plus";
        case Minus:
            return "Minus";
        case multiply:
            return "multiply";
        case open_bracket:
            return "open_bracket";
        case closed_bracket:
            return "closed_bracket";
        case power:
            return "power";
        case divide:
            return "divide";
        case single_quotation:
            return "single_quotation";
        case double_quotation:
            return "double_quotation";
        case not_operator_symbol:
            return "not_operator_symbol";
        case mod_operator:
            return "mod_operator";
        case and_operator_symbol:
            return "and_operator_symbol";
        case comma:
            return "comma";
        case dot:
            return "dot";
        case colon:
            return "colon";
        case bitwise_shift_left:
            return "bitwise_shift_left";
        case bitwise_shift_right:
            return "bitwise_shift_right";
        case lessthan:
            return "lessthan";
        case greaterthan:
            return "greaterthan";
        case lessthanorequalto:
            return "lessthanorequalto";
        case greaterthanorequalto:
            return "greaterthanorequalto";
        case bitwise_not:
            return "bitwise_not";
        case bitwise_or:
            return "bitwise_or";
        case bitwise_xor:
            return "bitwise_xor";
        case open_square:
            return "open_square";
        case close_square:
            return "close_square";
        case open_curly:
            return "open_curly";
        case close_curly:
            return "close_curly";
        case equality:
            return "equality";
        case assignment:
            return "assignment";
        case string_tkn:
            return "string_tkn";
        case error:
            return "error";
        case notequalto:
            return "notequalto";
        case plusequal:
            return "plusequal";
        case minusequal:
            return "minusequal";
        case mulequal:
            return "mulequal";
        case divequal:
            return "divequal";
        case andequal:
            return "andequal";
        case xorequal:
            return "xorequal";
        case orequal:
            return "orequal";
        case colequal:
            return "colequal";
        case modequal:
            return "modequal";
        case atequal:
            return "atequal";
        case at_operator:
            return "at_operator";
        case pow_equal:
            return "pow_equal";
        case double_divide:
            return "double_divide";
        case doubledivideequal:
            return "doubledivideequal";
        case rarrow:
            return "rarrow";
        case ellipsis:
            return "ellipsis";
        case shifteql:
            return "shifteql";
        case shifteqr:
            return "shifteqr";
        default:
            return "UNKNOWN_TOKEN_TYPE";
    }
}
void token::setstring(std::string str){
    this->id=str;
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
    case Import:
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
std::string tokenToSymbol(tokentype tok) {
    switch (tok) {
        case EOL: return ";";
        case identation: return " ";
        case Plus: return "+";
        case Minus: return "-";
        case power: return "**";
        case multiply: return "*";
        case divide: return "/";
        case open_bracket: return "(";
        case closed_bracket: return ")";
        case not_operator_symbol: return "!";
        case double_quotation: return "\"";
        case mod_operator: return "%";
        case single_quotation: return "'";
        case and_operator_symbol: return "&";
        case comma: return ",";
        case dot: return ".";
        case colon: return ":";
        case bitwise_not: return "~";
        case bitwise_or: return "|";
        case bitwise_xor: return "^";
        case open_square: return "[";
        case close_square: return "]";
        case open_curly: return "{";
        case close_curly: return "}";
        case bitwise_shift_left: return "<<";
        case bitwise_shift_right: return ">>";
        case lessthanorequalto: return "<=";
        case lessthan: return "<";
        case greaterthanorequalto: return ">=";
        case greaterthan: return ">";
        case equality: return "==";
        case assignment: return "=";
        case notequalto: return "!=";
        case plusequal: return "+=";
        case minusequal: return "-=";
        case mulequal: return "*=";
        case divequal: return "/=";
        case andequal: return "&=";
        case xorequal: return "^=";
        case orequal: return "|=";
        case colequal: return ":=";
        case modequal: return "%=";
        case atequal: return "@=";
        case at_operator: return "@";
        case pow_equal: return "**=";
        case double_divide: return "//";
        case doubledivideequal: return "//=";
        case rarrow: return "->";
        case ellipsis: return "...";
        case shifteql: return "<<=";
        case shifteqr: return ">>=";
        default: return "<unknown>";
    }
}
token::token(tokentype T){
    this->Type=T;
    if(T!=reserve_function && T!=reserved_keyword){
        this->id=tokenToSymbol(T);
    }
}
std::string token::getID(){
    return this->id;
}
tokentype token::getType(){
    return this->Type;
}
std::string getName(){
    
}
/**
 * ID : [(a-z)|(A-Z)|_](alnum | _) 
 */