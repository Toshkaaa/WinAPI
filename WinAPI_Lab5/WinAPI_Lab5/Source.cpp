#include <windows.h> // заголовочный файл,  який має у собі функції API
#include <string>
#define BUF_SIZE 4096
#define BUF_SIZE1 44096

using namespace std;

HWND hEdbox{};
HWND hEdbox1{};
HWND hEdbox2{};
HANDLE hNamedPipe;
char buffer_number[40] = { 0 };

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) //1 - вказівник на початок виконуваного модулю,
{		       //2 - використовувався в 16- біт Віндовс; 3 - вказівник на строку 
			   // 4 - як буде показуватися вікно

	MSG msg{}; // структура , яка містить інфу про повідомлення
	HWND hwnd{}; // дескриптор вікна, вказівник на об'єкт ядра
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; // характеристики вікна
	wc.cbClsExtra = 0; // доп виділення пам'яті 
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//дескриптор кисті 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);//курсор 
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);//іконка
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);//маленька іконка
	wc.hInstance = hInstance;//дескриптор экземпляра приложения
	wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT //процедура , яка відповідає за обробку повідомлень
																					 // 1 - дескриптор вікна; 2 - код повідомлення; 3,4 - вказівники, 
																					 //в яких міститься необіхна інфа для повідомлення	
	{
		switch (uMsg) // обробка віконних повідомлень
		{
		case  WM_CREATE:
		{
			HWND hButton = CreateWindow(L"BUTTON", L"Create Processes", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 0, 200, 30, hwnd, reinterpret_cast<HMENU>(1100), nullptr, nullptr);
			HWND hButton1 = CreateWindow(L"BUTTON", L"Send signal!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 0, 200, 30, hwnd, reinterpret_cast<HMENU>(1101), nullptr, nullptr);
			HWND hButton2 = CreateWindow(L"BUTTON", L"Connect to the pipe!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 0, 200, 30, hwnd, reinterpret_cast<HMENU>(1102), nullptr, nullptr);
			HWND hButton3 = CreateWindow(L"BUTTON", L"Read from the pipe!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 550, 0, 200, 30, hwnd, reinterpret_cast<HMENU>(1103), nullptr, nullptr);
			HWND hButton5 = CreateWindow(L"BUTTON", L"Write to the pipe!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 550, 50, 200, 30, hwnd, reinterpret_cast<HMENU>(1104), nullptr, nullptr);
			HWND hButton4 = CreateWindow(L"BUTTON", L"Discconnect from the pipe!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 50, 200, 30, hwnd, reinterpret_cast<HMENU>(1105), nullptr, nullptr);
			hEdbox2 = CreateWindow(L"EDIT", L"Enter your number of threads", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 350, 50, 150, 50, hwnd, nullptr, nullptr, nullptr);
			hEdbox = CreateWindow(L"EDIT", nullptr, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 20, 120, 350, 300, hwnd, nullptr, nullptr, nullptr);
			hEdbox1 = CreateWindow(L"EDIT", nullptr, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 420, 120, 700, 300, hwnd, nullptr, nullptr, nullptr);
		}
		return 0;

		case WM_COMMAND:
		{	
			switch (LOWORD(wParam))
			{
				case 1100:
				{
					PROCESS_INFORMATION pi = { 0 };
					ZeroMemory(&pi,sizeof(pi));
					STARTUPINFO si = { 0 };
					ZeroMemory(&si,sizeof(si));
					si.cb = sizeof(STARTUPINFO);
					if (!CreateProcess(L"D:\\source\\repos\\WinAPI_Lab5\\Childs\\Child1\\Debug\\Child1.exe",   // No module name (use command line)
						NULL,           // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						FALSE,          // Set handle inheritance to FALSE
						NULL,           // No creation flags
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory 
						&si,            // Pointer to STARTUPINFO structure
						&pi)            // Pointer to PROCESS_INFORMATION structure
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


						ZeroMemory(&pi, sizeof(pi));
						ZeroMemory(&si, sizeof(si));
						si.cb = sizeof(STARTUPINFO);
						if (!CreateProcess(L"D:\\source\\repos\\WinAPI_Lab5\\Childs\\Child2\\Debug\\Child2.exe",   // No module name (use command line)
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

				case 1101:
				{
					GetWindowText(hEdbox2, (LPWSTR)buffer_number, MAX_PATH);
					MessageBox(hwnd,(LPCWSTR)buffer_number,(LPCWSTR)buffer_number,NULL);
				}
				break;

				case 1102:
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
					else
					{
						MessageBox(hwnd, L"Connection successful!", L"System warning", MB_ICONASTERISK);
					}
				}
				break;

				case 1103:
				{
					DWORD dwNoBytesRead = 0;
					//LPVOID Buf = (CHAR*)calloc((BUF_SIZE*10) + 1, sizeof(CHAR));
					char Bufer[BUF_SIZE1] = {0};
		
					if (ReadFile(hNamedPipe, Bufer, BUF_SIZE1, &dwNoBytesRead, NULL))
					{
						SendMessageA(hEdbox1, WM_SETTEXT, WPARAM(0), (LPARAM)Bufer);
					}
				}
				break;

				case 1104:
				{
					LPDWORD lpNumberOfBytesWritten = 0;
					if (!WriteFile(hNamedPipe, &buffer_number, BUF_SIZE, lpNumberOfBytesWritten, NULL))
					{
						MessageBox(hwnd, L"Error during writing to the pipe!", L"Error", MB_ICONHAND);
					}
				}
				break;

				case 1105:
				{
					if (DisconnectNamedPipe(hNamedPipe)!=NULL)
					{
						CloseHandle(hNamedPipe);
					}
				}
			}
			return 0;
		}
		case WM_DESTROY: //повідомлення WM_DESTROY у випадку виходу (х)
		{
			PostQuitMessage(EXIT_SUCCESS);// обробка WM_DESTROY , вказує системі , що поток зробив запрос на закінчення
		}
		return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam); // викликається якщо повідомлення ніяк не оброблюється
	};
	wc.lpszClassName = L"MyApp"; // ім'я класу
	wc.lpszMenuName = nullptr; // вказівник на меню
	wc.style = CS_VREDRAW | CS_HREDRAW; //стиль вікна  

	if (!RegisterClassEx(&wc)) //реєстрація в системі класа нашого вікна
	{
		return EXIT_FAILURE;//виход з точки коду
	}
	hwnd = CreateWindow(wc.lpszClassName, L"Laba5", WS_OVERLAPPEDWINDOW, //створення вікна WS_OVERLAPPEDWINDOW - стилі вікна
		0, 0, 1200, 600, nullptr, nullptr, wc.hInstance, nullptr); // дескриптор батька і меню - 0
	

	ShowWindow(hwnd, nCmdShow); //показ вікна
	UpdateWindow(hwnd);//перемалювати наше вікно

	while (GetMessage(&msg, nullptr, 0, 0)) //обробка повідомлень 1 - вказівник на нашу структуру, 2 - hwnd вікна, 3 - фільтри
	{
		TranslateMessage(&msg);//розшифровує наше повідомлення
		DispatchMessageW(&msg);//передає повідолмення у віконну процедуру на обробку
	}
	return  static_cast<int>(msg.wParam);//повернути значення точки входу 
}
