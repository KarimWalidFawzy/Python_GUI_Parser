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
        TextOutA(hdc, x + 5, y + 5, get_token_name(listoftoks[i].getType()).c_str(), get_token_name(listoftoks[i].getType()).length()+1); 
   }
}
void DrawParsingTree(HDC hdc, HWND hwnd) {
    // Parsing Tree code
    // You can use the same logic as in the previous example to draw the parsing tree
    // For simplicity, let's just draw a placeholder for the parsing tree
    RECT rect;
    GetClientRect(hwnd, &rect);
    int x = rect.right / 2;
    int y = rect.bottom / 2;
    int xOffset = 50;
    int yOffset = 50;
    ParseTreeNode* root = parse(listoftoks);
    if (root) {
        drawParseTree(hdc, root, x, y, xOffset, yOffset);
        delete root; // Clean up the parse tree after drawing
    } else {
        TextOutA(hdc, 10, 10, "Parsing failed", 15);
    }
    // Clean up the parse tree after drawing
    // You can use the same logic as in the previous example to draw the parsing tree
    // For simplicity, let's just draw a placeholder for the parsing tree
    // Draw a placeholder for the parsing tree
    TextOutA(hdc, x, y, "Parsing Tree", 12);
    // Draw the root node
    Rectangle(hdc, x - 20, y - 20, x + 20, y + 20);
    TextOutA(hdc, x - 15, y - 15, "Root", 4);
    // Draw child nodes
    int childX = x - 50;
    int childY = y + 50;
    for (int i = 0; i < 2; ++i) { // Example: 2 child nodes
        Rectangle(hdc, childX - 20, childY - 20, childX + 20, childY + 20);
        TextOutA(hdc, childX - 15, childY - 15, "Child", 5);
        childX += 50; // Adjust spacing between child nodes
    }
    // Draw lines connecting parent and child nodes
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, childX - 50, childY); // Connect to the first child
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, childX, childY); // Connect to the second child
    // Clean up the parse tree after drawing
    // You can use the same logic as in the previous example to draw the parsing tree
    // For simplicity, let's just draw a placeholder for the parsing tree
    // Draw a placeholder for t
}