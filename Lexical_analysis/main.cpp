#include "lexical_analyzer.hpp"
#include "../Parser/parsing.hpp"
/** This Contains All the GUI components, I know people do not like WINAPI, but I'll use it anyway
 * 
 */
HWND globalMainWindow;
HMENU hMenu;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Python Compiler (GUI)",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        400, 400, 400, 400,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );
    globalMainWindow=hwnd;
    if (hwnd == NULL)
    {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
void DrawTokenTable(HDC hdc, HWND hwnd);
std::vector <token> listoftoks;
bool tokenized=false;
bool parsing=false;
void displayErrorMessage(const std::string& message);
void drawNode(HDC hdc, int x, int y, const std::string& text);
void DrawParsingTree(HDC,HWND);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    //All Window GUI elements are here
        AddMenus(hwnd);
                
        break;
    case WM_COMMAND:
        switch (wParam)
        {
        case 1:
            {OPENFILENAMEA file= {sizeof(OPENFILENAME)};
            file.lpstrFilter="txt files *.txt\0";
            file.lpstrFileTitle="Search for the file you want to compile";
            char buff[MAX_PATH]={};
            file.nMaxFile=sizeof(buff);
            file.lpstrFile=buff;
            bool rez=GetOpenFileNameA(&file);
            if (rez)
            {
                listoftoks=fileparser(file.lpstrFile);
                tokenized=true;
                parsing=false;
                InvalidateRect(hwnd, NULL, TRUE); // Invalidate the entire client area
                UpdateWindow(hwnd);
            }}          
            break;
        case 2:{
        OPENFILENAMEA file_parse= {sizeof(OPENFILENAME)};
        file_parse.lpstrFilter="txt files *.txt\0";
        file_parse.lpstrFileTitle="Search for the file you wish to parse";
        char buff2[MAX_PATH]={};
        file_parse.nMaxFile=sizeof(buff2);
        file_parse.lpstrFile=buff2;
        bool res=GetOpenFileNameA(&file_parse);
        if(res){
            listoftoks=fileparser(file_parse.lpstrFile);
            parsing=true;
            tokenized=false;
            InvalidateRect(hwnd, NULL, TRUE); // Invalidate the entire client area
            UpdateWindow(hwnd);
        }}
        break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.
           
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            if (tokenized && !parsing)
            DrawTokenTable(hdc,hwnd);
            else if (parsing && !tokenized)
            DrawParsingTree(hdc,hwnd);
            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void AddMenus(HWND hWnd){
    hMenu = CreateMenu();
    AppendMenu(hMenu,MF_STRING,0x1,L"Open to Compile");
    AppendMenu(hMenu,MF_STRING,0x2,L"Parse");
    SetMenu(hWnd,hMenu);
}
void DrawTokenTable(HDC hdc, HWND hwnd) {
    //child window
    /**/
    //CreateWindowA("static","TestChild",WS_CHILDWINDOW |WS_CHILD|WS_VISIBLE,200,100,0x500,0x500,hwnd,NULL,NULL,NULL);
    RECT rect;
    GetClientRect(hwnd, &rect);
    int cellWidth = 200; // Adjust as needed
    int cellHeight = 50; // Adjust as needed
    int rows = (listoftoks.size() + (rect.right / cellWidth) - 1) / (rect.right / cellWidth);
    int cols = rect.right / cellWidth;
    for (int i = 0; i < listoftoks.size(); ++i) {
        int row = i / cols;
        int col = i % cols;
        int x = col * cellWidth;
        int y = row * cellHeight;
        // Draw cell boundaries
        Rectangle(hdc, x, y, x + cellWidth, y + cellHeight);
        // Draw the token text
        std::string tokenText = get_token_name(listoftoks[i].getType())+ ":" + listoftoks[i].getID();
        TextOutA(hdc, x + 5, y + 5, tokenText.c_str(), tokenText.length()+1); 
   }
}
void DrawParsingTree(HDC hdc, HWND hwnd) {
    RECT rect;
    GetClientRect(hwnd, &rect);
    int centerX = rect.right / 2;
    int startY = 50;
    int xOffset = 100;
    int yOffset = 50;

    ParseTreeNode* root = parse(listoftoks);

    if (root) {
        // Function to recursively draw the parse tree
        std::function<void(ParseTreeNode*, int, int, int)> drawNode =
            [&](ParseTreeNode* node, int x, int y, int x_offset) {
            // Draw the current node
            RECT nodeRect = {x - 50, y - 15, x + 50, y + 15};
            FrameRect(hdc, &nodeRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            DrawTextA(hdc, node->name.c_str(), -1, &nodeRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            int childCount = node->children.size();
            if (childCount > 0) {
                int childrenStartX = x - (childCount - 1) * x_offset / 2;
                for (int i = 0; i < childCount; ++i) {
                    ParseTreeNode* child = node->children[i];
                    int childX = childrenStartX + i * x_offset;
                    int childY = y + yOffset;

                    // Draw connection line
                    MoveToEx(hdc, x, y + 15, NULL);
                    LineTo(hdc, childX, childY - 15);

                    drawNode(child, childX, childY, x_offset / (childCount > 1 ? childCount : 1));
                }
            }
        };

        drawNode(root, centerX, startY, xOffset);
        delete root; // Clean up the parse tree after drawing
    } else {
        TextOutA(hdc, 10, 10, "Parsing failed", 14);
    }
}
void displayErrorMessage(const std::string& message) {
    MessageBoxA(globalMainWindow, message.c_str(), "Error", MB_OK | MB_ICONERROR);
}
void drawNode(HDC hdc, int x, int y, const std::string& text) {
    RECT rect = {x - 50, y - 15, x + 50, y + 15};
    FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    DrawTextA(hdc, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}