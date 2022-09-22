#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
#define BUF_SIZE 4096

struct PARAMETERS
{
	string mystring;
	char buffer[BUF_SIZE] = { 0 };
};

HANDLE hEvent;
PARAMETERS param;

struct PARAMETERS2
{
	string mystring;
	char symb;
};

PARAMETERS2 param2;

DWORD ThreadID;
HANDLE hNamedPipe;
string num;
LPDWORD lpNumberOfBytesWritten = 0;
string global_string;

DWORD WINAPI ThreadFun2(void* par)
{
	PARAMETERS* params = (PARAMETERS*)par;
	BOOL counter = 1;
	for (int i = 0; i < params->mystring.length(); i++)
	{
		if (params->mystring[i] != 'a' && params->mystring[i] != 'b' && params->mystring[i] != 'c' && params->mystring[i] != 'd' && params->mystring[i] != 'e' && params->mystring[i] != 'f' && params->mystring[i] != 'g' && params->mystring[i] != 'h'
			&& params->mystring[i] != 'i' && params->mystring[i] != 'j' && params->mystring[i] != 'k' && params->mystring[i] != 'l' && params->mystring[i] != 'm' && params->mystring[i] != 'n' && params->mystring[i] != 'o' && params->mystring[i] != 'p'
			&& params->mystring[i] != 'q' && params->mystring[i] != 'r' && params->mystring[i] != 's' && params->mystring[i] != 't' && params->mystring[i] != 'u' && params->mystring[i] != 'v' && params->mystring[i] != 'w' && params->mystring[i] != 'x'
			&& params->mystring[i] != 'y' && params->mystring[i] != 'z')
		{
			//cout << "NO" << endl;
			counter = 0;
			break;
		}
	}
	if (counter)
	{
		global_string += params->mystring + " ";
		cout << params->mystring + " ";
	}
	SetEvent(hEvent);
	return 0;
}

DWORD WINAPI ThreadFun1(void * par)
{
	PARAMETERS* params = (PARAMETERS*)par;
	
	for (int i = 0; i < BUF_SIZE; i++)
	{
		if (params->buffer[i] == ' ' or params->buffer[i] == '.')
		{
			clock_t time1 = clock();

			HANDLE hTreandHandle1 = CreateThread(NULL, 0, ThreadFun2, &param, 0, &ThreadID);
			WaitForSingleObject(hEvent, INFINITE);
			cout << " | ID of the thread-> " << ThreadID <<" |"<< endl;
			
			clock_t time2 = clock();
			int delta = (time2 - time1) * 1000 / CLOCKS_PER_SEC;
			num = to_string(delta);
			WriteFile(hNamedPipe, num.c_str(), sizeof(num), lpNumberOfBytesWritten, NULL);

			params->mystring = "";
			ResetEvent(hEvent);
			CloseHandle(hTreandHandle1);
		}
		else
		{
			params->mystring += params->buffer[i];
		}
		if (params->buffer[i] == '\0' and params->buffer[i + 1] == '\0')
		{
			cout << endl << "End of your output!" << endl;
			num = "end";
			WriteFile(hNamedPipe, num.c_str(), sizeof(num), lpNumberOfBytesWritten, NULL);
			return 0;
		}
	}
}

DWORD WINAPI ThreadFun4(void* par)
{
	PARAMETERS2* params = (PARAMETERS2*)par;
	cout << "Letter " << params->symb << " coincides!" << endl;
	return 0;
}

DWORD WINAPI ThreadFun3(void *par)
{
	PARAMETERS2* params = (PARAMETERS2*)par;
	vector<char>myvector;
	bool one;
	for (int i = 0; i < params->mystring.length(); i++)
	{
		one = 1;
		if (params->mystring[i] != ' ')
		{
			for (int j = 0; j < params->mystring.length(); j++)
			{
				if (params->mystring[i] == params->mystring[j] && j != i)
				{
					for (int y = 0; y < myvector.size(); y++)
					{
						if (params->mystring[i] == myvector[y])
						{
							one = 0;
							break;

						}
					}
					if (one)
					{
						myvector.push_back(params->mystring[i]);
						params->symb = params->mystring[i];
						HANDLE hTreandHandle4 = CreateThread(NULL, 0, ThreadFun4, &param, 0, &ThreadID);
						WaitForSingleObject(hTreandHandle4,INFINITE);
						CloseHandle(hTreandHandle4);
						
					}
					break;
				}
			}
		}
	}
	return 0;
}

int main()
{
	//DWORD dwNoBytesRead = 0;
	//char Buf[BUF_SIZE];
	//ReadFile(hNamedPipe, Buf, BUF_SIZE, &dwNoBytesRead, NULL);
	//cout << Buf <<endl;

	cout << endl << " --- This is second child process! --- " << endl << endl;

	cout << " Choose what u want to do: \n";
	cout << "1.Connect to the nimed pipe\n";
	cout << "2.Read file, filter content and transfer time through pipe\n";
	cout << "3.Find repetitive letters\n";
	cout << "4.Transfer all content \n";
	cout << "5.Disconnect\n";
	cout << "0.Exit\n";
	while (true)
	{
		int choice;
		while (true)
		{
			cin >> choice;
			if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 0)
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
			Sleep(1000);
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
				cout << "Success" << endl;
			}

			break;
		}
		case 2:
		{
			hEvent = CreateEvent(NULL, FALSE, FALSE, L"MyEvent");

			HANDLE FileHandle = CreateFile(L"D:\\source\\repos\\WinAPI_Lab4\\Childs\\Child1\\Child1\\file.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, 0);
			if (INVALID_HANDLE_VALUE == FileHandle)
			{
				cout << "Error during opening file! " << endl;
			}

			LPDWORD lpNumberOfBytesRead = 0;
			ReadFile(FileHandle, param.buffer, BUF_SIZE, lpNumberOfBytesRead, NULL);

			HANDLE hTreandHandle = CreateThread(NULL, 0, ThreadFun1, &param, 0, &ThreadID);
			WaitForSingleObject(hTreandHandle, INFINITE);
			cout << "ID of the first thread-> " << ThreadID << endl;
			//CloseHandle(hTreandHandle);
			cout << global_string << endl << endl;
			CloseHandle(FileHandle);
			break;
		}
		case 3:
		{
			param.mystring = global_string;
			HANDLE hTreandHandle3 = CreateThread(NULL, 0, ThreadFun3, &param, 0, &ThreadID);
			WaitForSingleObject(hTreandHandle3, INFINITE);
			cout << "ID of the third thread-> " << ThreadID << endl;
			CloseHandle(hTreandHandle3);
			break;
		}
		case 4:
		{
			char Mass[BUF_SIZE] = "\0";
			strcpy(Mass, global_string.c_str());
			LPDWORD lpNumberOfBytesWritten = 0;
			WriteFile(hNamedPipe, &Mass, BUF_SIZE, lpNumberOfBytesWritten, NULL);
			break;
		}

		case 5:
		{
			if (!DisconnectNamedPipe(hNamedPipe))
			{
				cout << L"U have been successfuly disconnected!" << endl;
			}
			break;
		}
		}
	}
	CloseHandle(hEvent);
	CloseHandle(hNamedPipe);
}

