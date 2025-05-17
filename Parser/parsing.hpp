#ifndef PARSING_HPP
#define PARSING_HPP
    #include "../Lexical_analysis/lexical_analyzer.hpp"
    void stacksinit();
    class ParseTreeNode {
    private:
    std::string value;
    public:
    std::string name;
    std::vector<ParseTreeNode*> children;
     // Store the value of a token, e.g., the number or identifier
    ParseTreeNode(const std::string& nodeName) : name(nodeName){};
    ~ParseTreeNode() {\
        for (auto child : children) {\
            delete child;\
        }\
        children.clear();\
    }
    void addChild(ParseTreeNode* child) { children.push_back(child);}
    std::string getValue() const {return value;}
    void setValue(const std::string& val) { value = val; }
    };
    std::vector<token> tokenize(const std::string& code);
    ParseTreeNode* parse_statement(std::vector<token>& tokens, int& position);
    ParseTreeNode* parse_expression(std::vector<token>& tokens, int& position);
    ParseTreeNode* parse_term(std::vector<token>& tokens, int& position);
    ParseTreeNode* parse_factor(std::vector<token>& tokens, int& position);
    void displayErrorMessage(const std::string& message);
    // Global variables
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int TREE_NODE_WIDTH = 100;
    const int TREE_NODE_HEIGHT = 30;
    const int X_START = 50;
    const int Y_START = 50;
    const int X_OFFSET = 150;
    const int Y_OFFSET = 50;
    ParseTreeNode* parse(std::vector <token>);
#endif
/**
 * expression-seq -> expression EOL expression-seq 
 * expression -> [simple-stmt | compound_stmt EOL identation] expression  
 * simple-stmt -> assignment| type_alias| star_expressions | return_stmt| import_stmt| raise_stmt| 'pass' | del_stmt| yield_stmt| assert_stmt| 'break' | 'continue' | global_stmt| nonlocal_stmt
 * compound-stmt-> function_def| if_stmt| class_def | with_stmt| for_stmt | try_stmt | while_stmt | match_stmt
 * assignment -> identifier 
 * 
 * */