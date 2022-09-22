#define _CRT_SECURE_NO_DEPRECATE
#define DEFAULT_SECURITY (LPSECURITY_ATTRIBUTES)NULL
#include <iostream>
#include <windows.h>

using namespace std;
#define BUF_SIZE 4096

char Mass[BUF_SIZE] = { 0 };
HANDLE hNamedPipe;

int main()
{
    cout << endl << endl << " --- This is first child process! --- " << endl << endl;
    cout << " Choose what u want to do: \n";
    cout << "1.Create file\n";
    cout << "2.Create named pipe\n";
    cout << "3.Connect to the nimed pipe\n";
    cout << "4.Read the pipe (time)\n";
    cout << "5.Write to the pipe\n";
    cout << "6.Disconnect from the nimed pipe\n";
    cout << "0.Exit\n";
    while (true)
    {
        int choice;
        while (true)
        {
            cin >> choice;
            if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 0)
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
            HANDLE hFile = CreateFile(L"D:\\source\\repos\\WinAPI_Lab4\\Childs\\Child1\\Child1\\file.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, NULL, 0);
            
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
            //FlushFileBuffers(hNamedPipe);
            break;
        }

        case 4:
        {
            LPDWORD lpNumberOfBytesRead = 0;

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
            cout << Mass << endl;
            break;
        }

        case 5:
        {
            LPDWORD lpNumberOfBytesWritten = 0;
            WriteFile(hNamedPipe, &Mass, BUF_SIZE, lpNumberOfBytesWritten, NULL);
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
        }
    }
    CloseHandle(hNamedPipe);
}


