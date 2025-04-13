#include "lexical_analyzer.hpp"
/** This Contains All the GUI components, I know people do not like WINAPI, but I'll use it anyway
 * 
 */
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
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

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
            OPENFILENAMEA file= {sizeof(OPENFILENAME)};
            file.lpstrFilter="txt files * .txt\0";
            file.lpstrFileTitle="Search for the file you want to compile";
            char buff[MAX_PATH]={};
            file.nMaxFile=sizeof(buff);
            file.lpstrFile=buff;
            bool rez=GetOpenFileNameA(&file);
            if (rez)
            {
                std::vector <token> listoftoks=fileparser(file.lpstrFile);
            }            
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

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void AddMenus(HWND hWnd){
    hMenu = CreateMenu();
    AppendMenu(hMenu,MF_STRING,0x1,L"Open to Compile");
    SetMenu(hWnd,hMenu);
}