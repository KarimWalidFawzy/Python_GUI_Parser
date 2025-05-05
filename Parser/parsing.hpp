#ifndef PARSING_HPP
#define PARSING_HPP
    #include "../Lexical_analysis/lexical_analyzer.hpp"
    class ParseTreeNode {
    private:
    public:
    std::string name;
    std::vector<ParseTreeNode*> children;
    std::string value; // Store the value of a token, e.g., the number or identifier
    ParseTreeNode(const std::string& nodeName) : name(nodeName){};
    ~ParseTreeNode() {
        for (auto child : children) {
            delete child;
        }
        children.clear();
    }
    };
    std::vector<token> tokenize(const std::string& code);
    ParseTreeNode* parse_statement(std::vector<token>& tokens, int& position);
    ParseTreeNode* parse_expression(std::vector<token>& tokens, int& position);
    ParseTreeNode* parse_term(std::vector<token>& tokens, int& position);
    ParseTreeNode* parse_factor(std::vector<token>& tokens, int& position);
    void drawParseTree(HDC hdc, ParseTreeNode* node, int x, int y, int xOffset, int yOffset);
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