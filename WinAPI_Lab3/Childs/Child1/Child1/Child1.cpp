#include <windows.h> // заголовочный файл,  який має у собі функції API
#include <iostream>
#include <TlHelp32.h>
#include <string>
#define BUF_SIZE 4096

using namespace std;

int main()
{

	cout <<endl<< " --- This is first child process! --- " << endl<<endl;
	// task 2
	//LPCWSTR buffer =L"C:\\HP\\DATA\\";
	//WIN32_FIND_DATA FileData;
	//TCHAR szDirPath[] = TEXT("c:\\ESD\\FILE11\\");
	//TCHAR szNewPath[MAX_PATH];
	//BOOL fFinished = FALSE;
	//if (hSearch == INVALID_HANDLE_VALUE)
	//{ 
	//	cout << "Error while seeking!"<< endl;
	//}
	//else
	//{
	//	while (!fFinished)
	//	{
	//		lstrcpy(szNewPath, szDirPath);
	//		lstrcat(szNewPath, FileData.cFileName);
	//		if (!CopyFile(FileData.cFileName, szNewPath, FALSE))
	//		{
	//			cout << "Imposible to copy!" << endl;
	//			break;
	//		}
	//		if (!FindNextFile(hSearch, &FileData))
	//		{
	//			if (GetLastError() == ERROR_NO_MORE_FILES)
	//			{
	//				cout << "All files has been copied!!" << endl;
	//				fFinished = TRUE;
	//			}
	//		}
	//	}
	//}
	//FindClose(hSearch);


	//task 4  
	TCHAR tchBuf[4098];
	LPTSTR  lpszOldValue = ((GetEnvironmentVariable(L"Date", tchBuf, 4098) > 0) ? tchBuf : NULL);
	if (lpszOldValue)
	{
		cout << "Date = ";
		TCHAR* tchBuf1 = tchBuf;
		wcout << tchBuf1 << endl;
	}//lpvoid;
	cout << endl << " --- End of first child process! --- " << endl << endl;
}