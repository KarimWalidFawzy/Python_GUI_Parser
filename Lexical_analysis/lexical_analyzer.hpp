#ifndef LEXICAL_ANALYZER_HPP
#define LEXICAL_ANALYZER_HPP
    #include <regex>
    #include <cstdlib>
    #include <string>
    #include <fstream>
    #include <vector>
    #define NOMINMAX 0
    #define WIN32_LEAN_AND_MEAN
    #ifndef UNICODE
    #define UNICODE
    #endif 
    #include <windows.h>
    #include <commdlg.h>
    #include <gdiplus.h>
    #include <GL/gl.h>
    #include <d2d1.h>
    typedef enum {
        False,
        None, 
        True, 
        AND, 
        as, 
        assert, 
        async, 
        await, 
        Break, 
        Class, 
        Continue, 
        def, 
        del, 
        elif, 
        Else, 
        except, 
        finally, 
        For, from, global, 
        If, Import, in, is, lambda, nonlocal, Not, Or, pass, Raise, Return, Try, While, with, yield}
        reserved_keywords;
    typedef enum {
        print,len,Abs,aiter,all,anext,any,ascii,
        bin,Bool,breakpoint,bytearray,bytes,
        callable,chr,classmethod,compile,complex,
        delattr,dict,dir,divmod,
        enumerate,eval,exec,filter,Float,format,frozenset,
        getattr,globals,hasattr,hash,help,hex,
        id,input,Int,isinstance,issubclass,iter,list,locals,
        Map,max,memoryview,min,next,
        object,oct,open,ord,Pow,property,        
        range,repr,reversed,Round,
        set,setattr,slice,sorted,staticmethod,str,sum,super,tuple,type,
        vars,zip,__import__
        } reserved_functions;
    typedef enum {
        reserved_keyword,
        identifier,
        number,
        identation,
        EOL,
        reserve_function,
        Plus,
        Minus,
        multiply,
        open_bracket,
        closed_bracket,
        power,
        divide,
        single_quotation,
        double_quotation,
        not_operator_symbol,
        mod_operator,
        and_operator_symbol,
        comma,
        dot,
        colon,
        bitwise_shift_left,
        bitwise_shift_right,
        lessthan,
        greaterthan,
        lessthanorequalto,
        greaterthanorequalto,
        bitwise_not,
        bitwise_or,
        bitwise_xor,
        open_square,
        close_square,
        open_curly,
        close_curly,
        equality,
        assignment,
        string_tkn,
        notequalto,
        plusequal,
        minusequal,
        mulequal,
        divequal,
        andequal,
        xorequal,
        orequal,
        colequal,
        modequal,
        atequal,
        at_operator,
        pow_equal,
        double_divide,
        doubledivideequal,
        rarrow,
        ellipsis,
        shifteql,
        shifteqr,
        error 
    }tokentype;
    class token{
        private:
        std::string id;
        reserved_keywords res_key;
        tokentype Type;
        reserved_functions function;
        public: 
        token(std::string id);
        token(reserved_keywords);
        token(float num);
        token(tokentype);
        token(reserved_functions);
        void setstring(std::string);
        std::string getID(void);
        tokentype getType(void);
    };    
    std::vector <token> fileparser(const char*);
    std::string get_token_name(tokentype);
#endif
/*
    2.	Basic Constructs of Python: 
 
 a. Keywords 
The lexer must identify the following reserved keywords: 
False, None, True, and, as, assert, async, await, break, class, continue, def, del, elif, else, except, finally, for, from, global, if, import, in, is, lambda, nonlocal, not, or, pass, raise, return, try, while, with, yield 
 
 b. Variable Identifiers 
•	Must start with a letter (a-z, A-Z) or an underscore (_). 
•	Can contain letters, digits (0-9), and underscores (_). 
•	Case-sensitive (e.g., myVar and myvar are different). 
•	Cannot be a reserved keyword. 
 
 c. Function Identifiers 
•	Follows the same rules as variable identifiers. 
•	Function definitions must start with the def keyword followed by the function name. 
 
 d. Data Types 
The lexer must recognize basic Python data types: 
•	Integers: Whole numbers, positive or negative. 
•	Floats: Decimal numbers. 
•	Strings: Enclosed in single (''), double (""), or triple quotes (''' or """). 
•	Booleans: True or False. 
•	Lists: Enclosed in square brackets []. 
•	Dictionaries: Key-value pairs enclosed in curly brackets {}. 
•	Tuples: Ordered, immutable sequences enclosed in (). 
•	None: Represents the absence of value. 
 
 
3.	Functions: 
•	Defined using def followed by the function name and parentheses (). 
•	Can accept parameters and return values using return. 
•	Recognize built-in functions like print(), len(), input(), etc. 
 
 
4.	Statements: 
i. Assignment Statement 
•	Syntax: variable = expression 
•	Example: x = 5 
 
ii. Declaration Statement 
•	Python doesn’t require explicit type declarations, but the lexer must handle variable initialization. 
•	Example: name = "John" 
 
iii. Return Statement 
•	Syntax: return expression 
•	Example: return x + y 
 
iv. Iterative Statement 
•	For loop: for variable in sequence: 
•	While loop: while condition: 
•	Example: for i in range(5): 
    print(i) 
 
v. Conditional Statements 
•	If statement: if condition: 
•	Elif statement: elif condition: 
•	Else statement: else: 
•	Example: 
if x > 0: 
    print("Positive") elif x < 0: 
    print("Negative") else: 
    print("Zero") 
 
vi. Function Call Statement 
•	Syntax: function_name(arguments) 
•	Example: print("Hello World") 
 
 
 
5. Expressions: 
i. Arithmetic Expressions 
•	Supported operators: +, -, *, /, //, %, ** 
•	Example: result = (a + b) * c 
 
ii. Boolean Expressions 
•	Supported operators: and, or, not, ==, !=, <, >, <=, >= 
•	Example: is_valid = (x > 0) and (y < 5) 
 
 
 
6.	Error Handling: 
•	Lexical Errors: 
o	Unrecognized symbols. o Incorrect identifier naming. 
o	String or comment termination issues. 
 
•	Syntax Errors: 
o	Missing or extra brackets. o Incorrect statement structures. 
o	Unexpected tokens. 

*/