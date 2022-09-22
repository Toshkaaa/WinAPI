#include <windows.h> // ������������ ����,  ���� �� � ��� ������� API
#include <string>
#define BUF_SIZE 4096

using namespace std;

HWND hEdbox{};
HWND hEdbox1{};
HANDLE 	hNamedPipe;


int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) //1 - �������� �� ������� ������������ ������,
{		       //2 - ���������������� � 16- �� ³�����; 3 - �������� �� ������ 
			   // 4 - �� ���� ������������ ����

	MSG msg{}; // ��������� , ��� ������ ���� ��� �����������
	HWND hwnd{}; // ���������� ����, �������� �� ��'��� ����
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; // �������������� ����
	wc.cbClsExtra = 0; // ��� �������� ���'�� 
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//���������� ���� 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);//������ 
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);//������
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);//�������� ������
	wc.hInstance = hInstance;//���������� ���������� ����������
	wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT //��������� , ��� ������� �� ������� ����������
																					 // 1 - ���������� ����; 2 - ��� �����������; 3,4 - ���������, 
																					 //� ���� �������� ������� ���� ��� �����������	
	{
		switch (uMsg) // ������� ������� ����������
		{
		case  WM_CREATE:
		{
			hEdbox = CreateWindow(L"EDIT", nullptr, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 100, 50, 300, 64, hwnd, nullptr, nullptr, nullptr);
			HWND hButton = CreateWindow(L"BUTTON", L"Create Processes", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 0, 300, 30, hwnd, reinterpret_cast<HMENU>(1024), nullptr, nullptr);
			HWND hButton1 = CreateWindow(L"BUTTON", L"Conect to the pipe", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 130, 300, 30, hwnd, reinterpret_cast<HMENU>(1025), nullptr, nullptr);
			HWND hButton2 = CreateWindow(L"BUTTON", L"Read from the pipe", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 180, 300, 30, hwnd, reinterpret_cast<HMENU>(1026), nullptr, nullptr);
			hEdbox1 = CreateWindow(L"EDIT", nullptr, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 100, 220, 300, 64, hwnd, nullptr, nullptr, nullptr);
			HWND hButton3 = CreateWindow(L"BUTTON", L"Disconect from the pipe", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 300, 300, 30, hwnd, reinterpret_cast<HMENU>(1027), nullptr, nullptr);
		}
		return 0;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 1024:
			{
				STARTUPINFO si = { 0 };
				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(STARTUPINFO);

				PROCESS_INFORMATION pi = { 0 };
				ZeroMemory(&pi, sizeof(pi));

				if (!CreateProcess(L"D:\\source\\repos\\WinAPI_Lab4\\Childs\\Child1\\Debug\\Child1.exe",   // No module name (use command line)
					NULL,        // Command line
					NULL,           // Process handle not inheritable
					NULL,           // Thread handle not inheritable
					FALSE,          // Set handle inheritance to FALSE
					NULL,              // No creation flags
					NULL,           // Use parent's environment block
					NULL,           // Use parent's starting directory 
					&si,            // Pointer to STARTUPINFO structure
					&pi)           // Pointer to PROCESS_INFORMATION structure
					)
				{
					MessageBox(hwnd, L"The first process has not been created!", L"Error", MB_ICONHAND);
				}
				else
				{
					string prior = to_string(GetPriorityClass(pi.hProcess));
					string my = to_string(pi.dwProcessId);
					SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Process ID -> "));
					SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM(my.c_str()));
					SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("  "));
					SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Priority -> "));
					SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM(prior.c_str()));
					SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("  "));
					ZeroMemory(&si, sizeof(si));
					si.cb = sizeof(STARTUPINFO);
					ZeroMemory(&pi, sizeof(pi));
					if (!CreateProcess(L"D:\\source\\repos\\WinAPI_Lab4\\Childs\\Child2\\Debug\\Child2.exe",   // No module name (use command line)
						NULL,        // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						FALSE,          // Set handle inheritance to FALSE
						NULL,              // No creation flags
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory 
						&si,            // Pointer to STARTUPINFO structure
						&pi)           // Pointer to PROCESS_INFORMATION structure
						)
					{
						MessageBox(hwnd, L"The second process has not been created!", L"Error", MB_ICONHAND);
					}
					else
					{
						prior = to_string(GetPriorityClass(pi.hProcess));
						my = to_string(pi.dwProcessId);
						SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Process ID -> "));
						SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM(my.c_str()));
						SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("  "));
						SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Priority -> "));
						SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM(prior.c_str()));
						SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("  "));
					}
				}
			}
			break;

			case 1025:
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
					MessageBox(hwnd, L"Error during connecting!!", L"System warning", MB_ICONHAND);
				}
				
				WaitNamedPipe(L"\\\\.\\pipe\\MYNAMEDPIPE", INFINITE);
				MessageBox(hwnd, L"U have been successfuly connected!", L"System warning", MB_ICONASTERISK);
			}
			break;

			case 1026:
			{
				DWORD dwNoBytesRead = 0;
				LPVOID Buf = (CHAR*)calloc(BUF_SIZE + 1, sizeof(CHAR));
				if (!ReadFile(hNamedPipe, Buf, BUF_SIZE, &dwNoBytesRead, NULL))
				{
					MessageBox(hwnd, L"Error during reading from the pipe!", L"Error", MB_ICONHAND);
				}
				else
				{
					SendMessageA(hEdbox1, WM_SETTEXT, WPARAM(0), (LPARAM)Buf);
				}
			}
			break;

			case 1027:
			{
				if (!DisconnectNamedPipe(hNamedPipe))
				{
					MessageBox(hwnd, L"U have been successfuly disconnected!", L"System warning", MB_ICONASTERISK);
				}
				CloseHandle(hNamedPipe);
			}
			break;
			}
		return 0;
		}
		case WM_DESTROY: //����������� WM_DESTROY � ������� ������ (�)
		{
			PostQuitMessage(EXIT_SUCCESS);// ������� WM_DESTROY , ����� ������ , �� ����� ������ ������ �� ���������
		}
		return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam); // ����������� ���� ����������� ��� �� ������������
		};
		wc.lpszClassName = L"MyApp"; // ��'� �����
		wc.lpszMenuName = nullptr; // �������� �� ����
		wc.style = CS_VREDRAW | CS_HREDRAW; //����� ����  

		if (!RegisterClassEx(&wc)) //��������� � ������ ����� ������ ����
		{
			return EXIT_FAILURE;//����� � ����� ����
		}
		if (hwnd = CreateWindow(wc.lpszClassName, L"Laba4", WS_OVERLAPPEDWINDOW, //��������� ���� WS_OVERLAPPEDWINDOW - ���� ����
			0, 0, 700, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)// ���������� ������ � ���� - 0
			return EXIT_FAILURE;

		ShowWindow(hwnd, nCmdShow); //����� ����
		UpdateWindow(hwnd);//������������ ���� ����

		while (GetMessage(&msg, nullptr, 0, 0)) //������� ���������� 1 - �������� �� ���� ���������, 2 - hwnd ����, 3 - �������
		{
			TranslateMessage(&msg);//���������� ���� �����������
			DispatchMessageW(&msg);//������ ����������� � ������ ��������� �� �������
		}
		return  static_cast<int>(msg.wParam);//��������� �������� ����� ����� 
}

