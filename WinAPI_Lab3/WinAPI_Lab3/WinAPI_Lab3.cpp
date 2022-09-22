#include <windows.h> // заголовочный файл,  який має у собі функції API
#include <iostream>
#include <string>
#include <TlHelp32.h>

using namespace std;
#define BUFSIZE 4098

int main()
{
	STARTUPINFO si = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFO);

	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&pi, sizeof(pi));

	SECURITY_ATTRIBUTES sa = { 0 };
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	int tmp;
	cout << " Choose what u want to do: \n";
	cout << "1. Create system of directories \n";
	cout << "2. Copy files and create one new\n";
	cout << "3. Transfer parametr \n";
	cout << "4. Change parametr \n";
	cout << "5. Execute processes\n";
	cout << "6. Pipes\n";
	cout << "7. Snapshot of Processes\n";
	cout << "8. Window\n";
	cout << "0. Exit\n";
	while (true)
	{
		int choice;
		while (true)
		{
			cin >> choice;
			if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 ||  choice == 6 || choice == 7  || choice == 8|| choice == 0)
			{
				break;
			}
			else cout << "Invalid input,please try again\n";
		}
		if (choice == 0) break;
		switch (choice)
		{
			case 1:
			{
				cout << endl << "   ---This is parent process!---   " << endl;
				CreateDirectory(L"C:\\ESD\\FILE11\\", NULL);
				CreateDirectory(L"C:\\ESD\\FILE11\\FILE12\\", NULL);
				CreateDirectory(L"C:\\ESD\\FILE11\\FILE12\\FILE13", NULL);
				CreateDirectory(L"C:\\ESD\\FILE21\\", NULL);
				CreateDirectory(L"C:\\ESD\\FILE21\\FILE22\\", NULL);
				break;
			}

			case 2:
			{
				CreateProcess(L"C:\\Users\\toxa\\source\\repos\\Child1\\Debug\\Child1.exe", NULL,
					NULL,
					NULL,
					FALSE,
					NULL,
					NULL,
					NULL,
					&si,
					&pi);
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);

				DWORD ID = pi.dwProcessId;
				cout << "Process ID ->" << pi.dwProcessId << endl;
				CreateProcess(L"C:\\Users\\toxa\\source\\repos\\Child2\\Debug\\Child2.exe", NULL,
					NULL,
					NULL,
					FALSE,
					NULL,
					NULL,
					NULL,
					&si,
					&pi);
				WaitForSingleObject(pi.hProcess, INFINITE);
				ID = pi.dwProcessId;
				cout << "Process ID ->" << pi.dwProcessId << endl;
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);

				break;
			}

			case 3:
			{
				SYSTEMTIME st = { 0 };
				GetSystemTime(&st);
				wstring year = std::to_wstring(st.wYear);
				wstring month = std::to_wstring(st.wMonth);
				wstring day = std::to_wstring(st.wDay);
				wchar_t point = '.';
				wstring date = day + point + month + point + year;
				LPCWSTR lpdate = date.c_str();
				BOOL SeV = SetEnvironmentVariable(L"Date", lpdate);
				if (SeV)
				{
					cout << "Environment Variable has been added!" << endl;
				}
				else
				{
					cout << "Error during adding Environment Variable!" << endl;
				}
				
				break;
			}

			case 4:
			{
				wstring myPath;
				cout << "Enter your path:  ";
				wcin >> myPath;
				LPCWSTR lpPath = myPath.c_str();
				BOOL SeV = SetEnvironmentVariable(L"Path", lpPath);
				if (SeV)
				{
					cout << "Path has been changed!" << endl;
				}
				else
				{
					cout << "Error during changing Path!" << endl;
				}
				break;
			}

			case 5:
			{

				CreateProcess(L"C:\\Users\\toxa\\source\\repos\\Child3\\Debug\\Child3.exe", NULL,
					NULL,
					NULL,
					FALSE,
					NULL,
					NULL,
					NULL,
					&si,
					&pi);
				WaitForSingleObject(pi.hProcess, INFINITE);
				DWORD ID = pi.dwProcessId;
				cout << "Process ID ->" << pi.dwProcessId << endl;
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);

				CreateProcess(L"C:\\Users\\toxa\\source\\repos\\Child4\\Debug\\Child4.exe", NULL,
					NULL,
					NULL,
					FALSE,
					NULL,
					NULL,
					NULL,
					&si,
					&pi);
				WaitForSingleObject(pi.hProcess, INFINITE);
				ID = pi.dwProcessId;
				cout << "Process ID ->" << pi.dwProcessId << endl;

				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				break;
			}

			case 6: 
			{ 
				HANDLE ReadHandle, WriteHandle;
				STARTUPINFO pipe_si;
				PROCESS_INFORMATION pipe_pi;

				string word;
				cout << "Enter your world to find: " ;
				cin >> word;
				DWORD length = word.length();
				const char* message = word.c_str();

				DWORD written;
				/* set up security attributes to allow pipes to be inherited */
				SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
				ZeroMemory(&pipe_pi, sizeof(pipe_pi));
				if (!CreatePipe(&ReadHandle, &WriteHandle, &sa, 0))
				{
					cout << "Create Pipe Failed" << endl;
					return 1;
				}
				/* establishing the START INFO structure for the child process*/
				GetStartupInfo(&pipe_si);
				/* redirecting standard input to the read end of the pipe */
				pipe_si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
				pipe_si.hStdInput = ReadHandle;
				pipe_si.dwFlags = STARTF_USESTDHANDLES;
				SetHandleInformation(WriteHandle, HANDLE_FLAG_INHERIT, 0);
				CreateProcess(L"C:\\Users\\toxa\\source\\repos\\Child4\\Debug\\Child4.exe", NULL, NULL, NULL, TRUE,  0, NULL, NULL, &pipe_si, &pipe_pi);
				CloseHandle(ReadHandle);
				if (!WriteFile(WriteHandle, message, length, &written, NULL))
				{
					cout << "Error writing to pipe." << endl;
				}
				CloseHandle(WriteHandle);
				WaitForSingleObject(pipe_pi.hProcess, INFINITE);
				CloseHandle(pipe_pi.hProcess);
				CloseHandle(pipe_pi.hThread);
				break;
			}
			
			case 7: 
			{
				PROCESSENTRY32 ProcInfo = { 0 };
				ProcInfo.dwSize = sizeof(ProcInfo);
				int count = 0;
				HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
				cout << " --------------------ProcList----------------- " <<endl<<endl;
				while (Process32Next(hSnapshot,&ProcInfo)!=FALSE)
				{
					cout << "-----------------------------------" << endl;
					cout << "\tNumber " << ++count<<endl;
					cout << "-----------------------------------" << endl;
					cout << "Thread ->" << ProcInfo.cntThreads << endl;
					cout << "Size ->" << ProcInfo.dwSize << endl;
					cout << "Priority -> " << ProcInfo.pcPriClassBase << endl;
					wcout << "Executable -> " << ProcInfo.szExeFile << endl;
					cout << "PID -> " << ProcInfo.th32ProcessID << endl;
					cout << "PPID -> " << ProcInfo.th32ParentProcessID << endl << endl << endl;
				}
				CloseHandle(hSnapshot);

				cout << "-----------------------------------" << endl;
				cout << "\t Environment Variables "  << endl;
				cout << "-----------------------------------" << endl;
				LPCWSTR lpszVariable;
				LPVOID lpvEnv= GetEnvironmentStrings();
				for (lpszVariable = (LPTSTR)lpvEnv; *lpszVariable; lpszVariable++)
				{
					while (*lpszVariable)
						putchar(*lpszVariable++);
					putchar('\n');
				}
				FreeEnvironmentStrings((LPTSTR)lpvEnv);

				break;
			}

			case 8: 
			{
				HWND hwndRcv;
				int sizeArray = 256;
				char nData[256];
				STARTUPINFO si = { 0 };
				PROCESS_INFORMATION pi = { 0 };

				hwndRcv = FindWindowW(L"WinRcv", nullptr);
				if (!hwndRcv)
				{
					if (!CreateProcess(L"C:\\Users\\toxa\\source\\repos\\Temp\\Debug\\Temp", NULL, 
						NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi)) {
						cout << "Error !" << endl;
						//return 1;
					}
					while (!hwndRcv) {
						Sleep(250);
						hwndRcv = FindWindowW(L"WinRcv", nullptr);
					}
				}
				else

					for (int i = 0; i < sizeArray; i++)
						nData[i] = i * 10;
				COPYDATASTRUCT cds;

				cds.dwData = 0;
				cds.cbData = (sizeArray + 1) * sizeof(int);
				cds.lpData = (PVOID)nData;
				SendMessage(hwndRcv, WM_COPYDATA, (WPARAM)nullptr, (LPARAM)&cds);
				break;
			}
		}
	}

	DWORD excode;	
	GetExitCodeProcess(pi.hProcess, &excode);
	cout << "Excode= " << excode << endl;
	if (excode==STILL_ACTIVE)
	{
		cout << "Process stil active!" << endl;
	}
	else
	{
		cout << "Done!" << endl;
	}
}