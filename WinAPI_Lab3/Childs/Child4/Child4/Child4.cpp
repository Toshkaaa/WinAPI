#include <windows.h> // заголовочный файл,  який має у собі функції API
#include <iostream>
#include <TlHelp32.h>
#include <string>
#define BUF_SIZE 4096
#define BUFFER_SIZE 125
using namespace std;

void FindWord(string my, WCHAR* FileName)
{
	DWORD NumRead = 0;
	char buff[40096]{ '\0' };
	HANDLE FileHandle = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(FileHandle, buff, BUF_SIZE, &NumRead, NULL);
	int flag = 0;
	int j;
	for (int i = 0; buff[i] != '\0'; i++)
	{
		j = 0;
		while (my[j] == buff[i])
		{
			j++;
			i++;
			if (j == my.length())
			{
				cout << "String \"" << my << "\" has been found in the file ";
				wcout << FileName << endl;
				flag = 1;
				break;
			}
		}
		if (flag) break;
	}
}

void FindFile()
{
	TCHAR szDir[255];
	GetCurrentDirectory(255, szDir);
	SetCurrentDirectory(szDir);
	string string_to_find;
	cout << "Enter your string to find: ";
	cin >> string_to_find;

	WIN32_FIND_DATA wfd = { 0 };
	HANDLE hfind = FindFirstFile(L"*", &wfd);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		cout << "Search error!" << endl;
	}
	else
	{
		do
		{
			FindWord(string_to_find, wfd.cFileName);
		} while (FindNextFile(hfind, &wfd));
	}
	FindClose(hfind);
}


void FindFilePipe(string par)
{
	TCHAR szDir[255];
	GetCurrentDirectory(255, szDir);
	SetCurrentDirectory(szDir);

	WIN32_FIND_DATA wfd = { 0 };
	HANDLE hfind = FindFirstFile(L"*", &wfd);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		cout << "Search error!" << endl;
	}
	else
	{
		do
		{
			FindWord(par, wfd.cFileName);
		} while (FindNextFile(hfind, &wfd));
	}
	FindClose(hfind);
}


int main()
{
	cout << endl << " --- This is fourth child process! --- " << endl << endl;
	//task 5 
	//FindFile();

	//task 6
	HANDLE Readhandle= GetStdHandle(STD_INPUT_HANDLE);
	CHAR buffer[BUFFER_SIZE] = {0};
	DWORD read;
	/* getting the read handle of the pipe */
	/* the child reads from the pipe */
	if (ReadFile(Readhandle, buffer, BUFFER_SIZE, &read, NULL))
	{
		cout << "Child proccess read the word ----> " << buffer << endl;
		FindFilePipe(buffer);
	}
	else
	{
		cout << "Error reading from pipe" << endl;
	}
	cout << endl << " --- End of fourth child process! --- " << endl << endl;
}