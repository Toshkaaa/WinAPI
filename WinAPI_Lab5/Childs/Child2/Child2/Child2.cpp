#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <windows.h> // заголовочный файл,  який має у собі функції API
#include <string>
#include <time.h> 
using namespace std;
#define BUF_SIZE 4096

int random()
{
    int random_number= rand() % 20 + 1;
    return random_number;
}
struct PARAMETERS
{
    char buffer[BUF_SIZE] = { 0 };
};

PARAMETERS param;
HANDLE hFile;
HANDLE hMutex;
HANDLE hEvent;
HANDLE hMutextmp;
HANDLE hNamedPipe;
int num=5;

DWORD WINAPI Administrator(LPVOID lpParam)
{
    cout << "Administrator: ";
    char temp[16] = "Administrator: ";
    WriteFile(hNamedPipe, temp, sizeof(temp), 0, NULL);
    string number = to_string(*(DWORD*)lpParam)+";";
    for (int i = 0; i < BUF_SIZE; i++)
    {
        if (param.buffer[i - 1] == '=' and param.buffer[i] == number[0] and param.buffer[i + 1] == number[1])
        {
            hMutex = OpenMutex(MUTEX_ALL_ACCESS, NULL, (LPCWSTR)number.c_str());
            if (hMutex == NULL)
            {
                cout << "Mutex is not exsist!" << endl;
                hMutex = CreateMutex(NULL, TRUE, (LPCWSTR)number.c_str());
                if (!hMutex)
                {
                    cout << "Mutex has not created!" << endl;
                }
            }
            DWORD result = WaitForSingleObject(hMutex, 0);
            if (result == WAIT_OBJECT_0)
            {
                cout << "We have found room for " << (*(DWORD*)lpParam) << " days!" << endl;

                char temp1[24] = "We have found room for ";
                WriteFile(hNamedPipe, temp1, sizeof(temp1), 0, NULL);
                char temp2[5];
                sprintf(temp2, "%d", (*(DWORD*)lpParam));
                WriteFile(hNamedPipe, temp2, sizeof(temp2), 0, NULL);
                char temp3[7] = " days\n";
                WriteFile(hNamedPipe, temp3, sizeof(temp3), 0, NULL);

                cout << "Number of room " << param.buffer[i - 2] << endl;

                char temp4[16] = "Number of room ";
                WriteFile(hNamedPipe, temp4, sizeof(temp4), 0, NULL);
                char temp5[2] = {0};
                temp5[0] = param.buffer[i - 2];
                WriteFile(hNamedPipe, temp5, sizeof(temp5), 0, NULL);
                char temp6[3] = "\n";
                WriteFile(hNamedPipe, temp6, sizeof(temp6), 0, NULL);
            }
            else
            {
                cout << "Room for " << (*(DWORD*)lpParam) << " days already busy" << endl;

                char temp1[10] = "Room for ";
                WriteFile(hNamedPipe, temp1, sizeof(temp1), 0, NULL);
                char temp2[5];
                sprintf(temp2, "%d", (*(DWORD*)lpParam));
                WriteFile(hNamedPipe, temp2, sizeof(temp2), 0, NULL);
                char temp3[20] = " days already busy\n";
                WriteFile(hNamedPipe, temp3, sizeof(temp3), 0, NULL);

                break;
            }
            return 0;
        }
    }
    cout << "Unforunately we have not room for " << (*(DWORD*)lpParam) << " days!" << endl;

    char temp1[35] = "Unforunately we have not room for ";
    WriteFile(hNamedPipe, temp1, sizeof(temp1), 0, NULL);
    char temp2[5];
    sprintf(temp2, "%d", (*(DWORD*)lpParam));
    WriteFile(hNamedPipe, temp2, sizeof(temp2), 0, NULL);
    char temp3[8] = " days!\n";
    WriteFile(hNamedPipe, temp3, sizeof(temp3), 0, NULL);

    (*(DWORD*)lpParam) = (*(DWORD*)lpParam) - 1;
    Administrator(lpParam);
}

DWORD WINAPI Client(LPVOID  lpParam)
{
    //DWORD lpNumberOfBytesWritten = SetFilePointer(hFile, 0, NULL, FILE_END);
    cout << "Client: I want to rent room for " << (*(DWORD*)lpParam) << " days " << endl;

    char tmp[33] = "Client: I want to rent room for ";
    WriteFile(hNamedPipe, tmp, sizeof(tmp), 0, NULL);

    char tmp1[5];
    sprintf(tmp1, "%d", (*(DWORD*)lpParam));
    WriteFile(hNamedPipe, tmp1, sizeof(tmp1), 0, NULL);

    char tmp2[7] = " days\n";
    WriteFile(hNamedPipe, tmp2, sizeof(tmp2), 0, NULL);

    DWORD ThreadID;
    HANDLE hAdmin = CreateThread(NULL, 0, Administrator, lpParam, 0, &ThreadID);
    cout << "Thread-> ID = " << ThreadID << endl;

    //char tmp3[15] = "Thread-> ID = ";
    //WriteFile(hNamedPipe, tmp3, sizeof(tmp3), 0, NULL);
    //char tmp4[10];
    //sprintf(tmp4, "%d", ThreadID);
    //WriteFile(hNamedPipe, tmp4, sizeof(tmp4), 0, NULL);

    WaitForSingleObject(hAdmin, INFINITE);
    SetEvent(hEvent);
    Sleep((*(DWORD*)lpParam) * 1000);
    string name_event = to_string(*(DWORD*)lpParam) + ";";
    hMutextmp = OpenMutex(MUTEX_ALL_ACCESS, NULL, (LPCWSTR)name_event.c_str());
    CloseHandle(hMutextmp);
    CloseHandle(hAdmin);
    return 0;
}

DWORD WINAPI Receptionist(void* par)
{
    hFile = CreateFile(L"D:\\source\\repos\\WinAPI_Lab5\\hostel.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, 0);
    if (!hFile)
    {
        cout << "Error during opening file!" << endl;
    }
    LPDWORD lpNumberOfBytesRead = 0;
    ReadFile(hFile, param.buffer, BUF_SIZE, lpNumberOfBytesRead, NULL);
    char tmp[15] = "Receptionist:\n";
    cout << tmp;
    cout << param.buffer << endl;

    WriteFile(hNamedPipe, tmp, sizeof(tmp), 0, NULL);

   // DWORD lpNumberOfBytesWritten = SetFilePointer(hFile, 0, NULL, FILE_END);
    WriteFile(hNamedPipe, param.buffer,BUF_SIZE, 0, NULL);

    CloseHandle(hFile);
    return 0;
}

int main()
{
    cout << endl << endl << " --- This is second child process! --- " << endl << endl;

    cout << " Choose what u want to do: \n";
    cout << "1.Connect to the nimed pipe\n";
    cout << "2.Execute threads with your number\n";
    cout << "3.Read nimed pipe\n";
    cout << "0.Exit\n";
    while (true)
    {
        int choice;
        while (true)
        {
            cin >> choice;
            if (choice == 1 || choice == 2 || choice == 3  || choice == 0)
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
            hNamedPipe = CreateFile(
                L"\\\\.\\pipe\\MYNAMEDPIPE",
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
            if (hNamedPipe == INVALID_HANDLE_VALUE)
            {
                cout << "Error during connecting!!" << endl;
            }
            else
            {
                cout << "Connection successful!" << endl;
            }
            break;
        }
        case 2:
        {
            if (num>0)
            { 
                srand(time(NULL));
                DWORD ThreadID;
                HANDLE hTreandHandle = CreateThread(NULL, 0, Receptionist, NULL, 0, &ThreadID);
                cout << "Thread-> ID = " << ThreadID << endl;
                WaitForSingleObject(hTreandHandle, INFINITE);

                hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);


                DWORD* arr = new DWORD[num];
                for (int i = 0; i < num; i++)
                {
                    arr[i] = random();
                }

                HANDLE* hThreadClients = new HANDLE[num];
                for (int i = 0; i < num; i++)
                {
                    hThreadClients[i] = CreateThread(NULL, 0, Client, &arr[i], 0, &ThreadID);
                    cout << "Thread-> ID = " << ThreadID << " ";
                    WaitForSingleObject(hEvent, INFINITE);
                    ResetEvent(hEvent);
                }
                WaitForMultipleObjects(num, hThreadClients, TRUE, INFINITE);
                for (int i = 0; i < num; i++)
                {
                    CloseHandle(hThreadClients[i]);
                }
                string end_of_pipe = "end";
                WriteFile(hNamedPipe, end_of_pipe.c_str(), sizeof(end_of_pipe), 0, NULL);

            }
            else
            {
                cout << "Please enter number more than 0" << endl;
            }
            break;
        }
        case 3:
        {
            char buffer[BUF_SIZE] = { 0 };
            LPDWORD lpNumberOfBytesRead = 0;
            ReadFile(hNamedPipe, &buffer, BUF_SIZE, lpNumberOfBytesRead, NULL);
            string text = string(buffer);
            num = stoi(text);
            cout <<"U have entered "<< num<<" in the main window"<< endl;
            break;
        }

        }
    }
   
}