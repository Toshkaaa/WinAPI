#include <windows.h>
#include <iostream>
#include <string>
#include <TlHelp32.h>
#define BUF_SIZE 4096

using namespace std;

int main()
{
	cout << endl << " --- This is second child process! --- " << endl << endl;
	////task 2
	//HANDLE FileHandle = CreateFile(L"C://ESD//FILE11//MyFile.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, NULL, 0);
	//if (FileHandle==INVALID_HANDLE_VALUE)
	//{
	//	cout<<"Error during creating file!"<<endl;
	//}
	//else
	//{
	//	cout << "File has been created!" <<endl;
	//	CloseHandle(FileHandle);
	//}

	//task 4
	TCHAR tchBuf[4098];
	LPTSTR  lpszOldValue = ((GetEnvironmentVariable(L"Path", tchBuf, 4098) > 0) ? tchBuf : NULL);
	if (lpszOldValue)
	{
		cout << "Path = ";
		TCHAR* tchBuf1 = tchBuf;
		wcout << tchBuf1 << endl;
	}
	cout << endl << " --- End of second child process! --- " << endl << endl;
}