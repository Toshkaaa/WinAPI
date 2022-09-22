#include <iostream>
#include <windows.h> // заголовочный файл,  який має у собі функції API
#include <string>
using namespace std;

#define BUF_SIZE 4096
HANDLE hNamedPipe;
string text2 = "";
char buffer[BUF_SIZE] = { 0 };

DWORD WINAPI Func1(LPVOID  lpParam)
{
    WriteFile(hNamedPipe, text2.c_str(), text2.length(), 0, NULL);
    return 0;
}

DWORD WINAPI Func2(LPVOID lpParam) 
{
    LPDWORD lpNumberOfBytesRead = 0;
    char buff[BUF_SIZE] = { 0 };

    string text1;

    while (true)
    {
        if (ReadFile(hNamedPipe, &buff, sizeof(buff), lpNumberOfBytesRead, NULL))
        {
            text1 = string(buff);
            if (text1 == "end")
            {
                cout << "End of output" << endl;
                break;
            }
            text2 = text2 + string(buff);
            cout << buff;
        }
    }
    return 0;
}

DWORD WINAPI Func3(LPVOID lpParam)
{
    LPDWORD lpNumberOfBytesWritten = 0;
    WriteFile(hNamedPipe, &buffer, BUF_SIZE, lpNumberOfBytesWritten, NULL);
    return 0;
}

DWORD WINAPI Func4(LPVOID lpParam)
{
    LPDWORD lpNumberOfBytesRead = 0;
    ReadFile(hNamedPipe, &buffer, BUF_SIZE, lpNumberOfBytesRead, NULL);
    cout << buffer << endl;
    return 0;
}

int main()
{
    cout << endl << endl << " --- This is first child process! --- " << endl << endl;

    cout << " Choose what u want to do: \n";
    cout << "1.Create file\n";
    cout << "2.Create named pipe\n";
    cout << "3.Connect to the nimed pipe\n";
    cout << "4.Read the pipe\n";
    cout << "5.Write to the pipe\n";
    cout << "6.Disconnect from the nimed pipe\n";
    cout << "7.Read text from the pipe\n";
    cout << "8.Write to the main window\n";
    cout << "0.Exit\n";
    while (true)
    {
        int choice;
        while (true)
        {
            cin >> choice;
            if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7 || choice == 8 || choice == 0)
            {
                break;
            }
            else cout << "Invalid input, please try again\n";
        }
        if (choice == 0) break;
        switch (choice)
        {
        case 1:
        {
            HANDLE hFile = CreateFile(L"D:\\source\\repos\\WinAPI_Lab5\\hostel.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, 0);
            if (!hFile)
            {
                cout << "Error during creating file" << endl;
            }
            break;
        }

        case 2:
        {
            hNamedPipe = CreateNamedPipe(L"\\\\.\\pipe\\MYNAMEDPIPE",
                PIPE_ACCESS_DUPLEX,
                PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                PIPE_UNLIMITED_INSTANCES,
                0,
                0,
                0,
                NULL);

            if (hNamedPipe == INVALID_HANDLE_VALUE)
            {
                cout << "Error during creating named pipe! Error = " << GetLastError() << endl;
            }
            else
            {
                cout << "Pipe was created successfully!" << endl;
            }

            break;
        }

        case 3:
        {
            cout << "Waiting for a conection..." << endl;
            if (ConnectNamedPipe(hNamedPipe, NULL))
            {
                cout << "Client connected" << endl;
            }
            break;
        }

        case 4:
        {
            /*LPDWORD lpNumberOfBytesRead = 0;
            string number2;
            while (true)
            {
                ReadFile(hNamedPipe, &Mass, BUF_SIZE, lpNumberOfBytesRead, NULL);
                number2 = string(Mass);
                if (number2 == "end")
                {
                    cout << "End of output" << endl;
                    break;
                }
                cout << number2 << " ms " << endl;
            }
            ReadFile(hNamedPipe, &Mass, BUF_SIZE, lpNumberOfBytesRead, NULL);
            cout << "Your output is  ";
            cout << Mass << endl;*/

            CreateThread(NULL, 0, Func4, NULL, 0, NULL);
            break;
        }

        case 5:
        {
            CreateThread(NULL, 0, Func3, NULL, 0, NULL);
            break;
        }

        case 6:
        {
            DisconnectNamedPipe(hNamedPipe);
            cout << "Waiting for a conection..." << endl;
            if (ConnectNamedPipe(hNamedPipe, NULL))
            {
                cout << "Client connected" << endl;
            }
            break;
        }

        case 7:
        {
            CreateThread(NULL, 0, Func2, NULL, 0, NULL);
            break;
            
        }
        case 8:
        {
            CreateThread(NULL, 0, Func1, NULL, 0, NULL);
            break;
        }
        }
    }
    CloseHandle(hNamedPipe);

}
