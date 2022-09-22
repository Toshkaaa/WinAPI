#include <Windows.h>
#include <iostream>
#include <strsafe.h>
#include <string>
using namespace std;
#define BUF_SIZE 4096

HWND hwnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCopyData(HWND, COPYDATASTRUCT*);

wchar_t szClassName[] = L"WinRcv";
wchar_t szTitle[] = L"Temp";

void Findnumber()
{
    SetCurrentDirectory(L"C:\\ESD");

    WIN32_FIND_DATA wfd = { 0 };
    HANDLE hfind = FindFirstFile(L"*", &wfd);
    if (hfind == INVALID_HANDLE_VALUE)
    {
        MessageBox(hwnd,L"Error",L"System", MB_ICONQUESTION);
    }
    else
    {
        int number = NULL;
        wstring Myfile;
        do
        {
            DWORD NumRead = 0;
            char buff[BUF_SIZE]{ '\0' };
            HANDLE FileHandle = CreateFile(wfd.cFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            wstring year = wfd.cFileName;
            //wcout << wfd.cFileName << endl;
            ReadFile(FileHandle, buff, BUF_SIZE, &NumRead, NULL);
            if (number < (atoi(buff)))
            {
                year = wfd.cFileName;
                Myfile = year;
                number = atoi(buff);
            }
        } while (FindNextFile(hfind, &wfd));
        string str=std::to_string(number);
        MessageBoxA(hwnd, str.c_str(), "Max number", MB_ICONASTERISK);
       // MessageBoxA(hwnd, Myfile.c_str(), "File", MB_ICONASTERISK);
       // cout << "Max number is " << number << " in the file ";
     //   wcout << Myfile << endl;
    }
    FindClose(hfind);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    MSG Msg;
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wc.lpszClassName = szClassName;
    RegisterClass(&wc);

    hwnd = CreateWindowW(
        szClassName,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        210, 200, 200, 200,
        HWND_DESKTOP,
        nullptr,
        hInst,
        nullptr
        );

    ShowWindow(hwnd, SW_NORMAL);
    while (GetMessage(&Msg, nullptr, 0, 0))
        DispatchMessage(&Msg);
    return 0;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COPYDATA:
    {
        COPYDATASTRUCT* pcds = (COPYDATASTRUCT*)lParam;
        Findnumber();
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
    }break;
    default:
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }
}

