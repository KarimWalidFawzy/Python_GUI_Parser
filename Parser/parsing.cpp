#include "parsing.hpp"
/** 
 * python expression 
 * expression -> term (('+' | '-') term)*
 * term -> factor (('*' | '/') factor)*
 * factor -> number | identifier | '(' expression ')'
 * expression -> reserved_function '(' expression ')'
 * reserved_function -> 'print' | 'input' | 'len' | 'str' | 'int' | 'float'
 * expression -> 'if' expression ':' statement
 * statement -> 'for' identifier 'in' expression ':' statement
 * statement -> 'while' expression ':' statement
 * statement -> 'def' identifier '(' (identifier (',' identifier)*)? ')' ':' statement
 * * statement -> 'return' expression
 * * statement -> 'break'
 * * statement -> 'continue'
 * * statement -> 'pass'
 * * statement -> 'class' identifier '(' (identifier (',' identifier)*)? ')' ':' statement
 * * statement -> 'try' statement 'except' statement
 * * statement -> 'finally' statement
 * * statement -> 'with' expression ':' statement
 * * statement -> 'assert' expression
 * * statement -> 'raise' expression
 * * statement -> 'global' identifier
 * * * statement -> 'nonlocal' identifier
 * * * statement -> 'async' statement
 * * * statement -> 'await' expression
 * * * statement -> 'yield' expression
 * * * statement -> 'import' identifier
 * * * statement -> 'from' identifier 'import' identifier
 * * * statement -> 'as' identifier
 * * * statement -> 'elif' expression ':' statement
 * * * statement -> 'else' ':' statement
 * * * statement -> 'break' | 'continue' | 'pass'
 * * * statement -> 'elif' expression ':' statement
 * * * statement -> 'else' ':' statement
 * * * statement -> 'try' statement 'except' statement
 * * * * statement -> 'finally' statement
 * * * * * statement -> 'with' expression ':' statement
 * * * * * * statement -> 'assert' expression
 * * * * * * * statement -> 'raise' expression
 * * * * * * * * statement -> 'global' identifier
 * * * * * * * * * statement -> 'nonlocal' identifier
 * * * * * * * * * * statement -> 'async' statement
 * * * * * * * * * * statement -> 'await' expression
 *   
 *
*/
ParseTreeNode* parse(std::vector <token> listtoks){
    ParseTreeNode* root = new ParseTreeNode("root");
    
}
void drawParseTree(HDC hdc, ParseTreeNode* node, int x, int y, int xOffset, int yOffset){

}