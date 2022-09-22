#include <windows.h>
#include <iostream>
#include <string>
#include<TlHelp32.h>
#define BUF_SIZE 4096

using namespace std;

void Findnumber()
{
	SetCurrentDirectory(L"C:\\ESD");

	WIN32_FIND_DATA wfd = { 0 };
	HANDLE hfind = FindFirstFile(L"*", &wfd);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		cout << "Search error!" << endl;
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
		cout << "Max number is " << number << " in the file ";
		wcout << Myfile << endl;
	}
	FindClose(hfind);
}

int main()
{
	cout << endl << " --- This is third child process! --- " << endl << endl;
	//task 5
	Findnumber();
	cout << endl << " --- End of third child process! --- " << endl << endl;
}