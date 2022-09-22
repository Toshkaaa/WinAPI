#include <windows.h> // заголовочный файл,  який має у собі функції API
#include <string>

#define is_delim(c) (isspace((c)) || ispunct((c)))

#define BUF_SIZE 4096

HWND hwnd{};
HWND hEdbox{};
HWND hEdbox1{};
HWND hEdbox3{};

void WriteData(HANDLE hFile,LPWSTR path)
{
	WIN32_FIND_DATA wfd = { 0 }; //структура що містить різні метаданні для пошуку файлів
	SetCurrentDirectory(path);

	HANDLE hfind = FindFirstFile(L"*", &wfd);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		MessageBox(hwnd, L"Ошибка при поиске!", L"Системное предупреждение", MB_ICONHAND);
	}
	do
	{
		LPWSTR strTmp = (LPWSTR)calloc(BUF_SIZE + 1, sizeof(WCHAR));// строка для зберігання даних про путь, тип файлу
		
		GetCurrentDirectory(BUF_SIZE, strTmp);//отримуємо поточну директорію
		wcscat_s(strTmp, BUF_SIZE, L"\\");//конкантенація слеша
		wcscat_s(strTmp, BUF_SIZE, wfd.cFileName);//конкантенація назви файлу
	
	    LPWSTR strTmp_ = (LPWSTR)calloc(wcslen(strTmp) + 1, sizeof(WCHAR));//робимо нову строку яка містить повний і чистий шлях
	    wcscpy_s(strTmp_, wcslen(strTmp) + 1, strTmp);//копіюємо в неї наші данні
		if (wcscmp(wfd.cFileName, L".") && wcscmp(wfd.cFileName, L".."))//якщо міститься крапка або дві крапки
		{//Форматування для запису у файл
			
			wcscat_s(strTmp, BUF_SIZE, L"\t\t\t");//перенос на слідуючу строку
		
			if (((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) && (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)))//якщо це папка
			{
				//wcscat_s(strTmp, BUF_SIZE, L"DIR");//допишемо слово папка
				wcscat_s(strTmp, BUF_SIZE, L"\r\n");//перенос на слідуючу строку
				DWORD iCount = 0;
				WriteFile(hFile, strTmp, wcslen(strTmp) * sizeof(WCHAR), &iCount, NULL);//Записуємо наші данні у файл
				WriteData(hFile, strTmp_);
				SetCurrentDirectory(path);
			}
			else
			{
				//wcscat_s(strTmp, BUF_SIZE, L"FILE");//допишемо слово файл
				wcscat_s(strTmp, BUF_SIZE, L"\r\n");// перенос на слідуючу строку
				DWORD iCount = 0;
				WriteFile(hFile, strTmp, wcslen(strTmp) * sizeof(WCHAR), &iCount, NULL);//запис у файл
			}
			}
		free(strTmp);
		free(strTmp_);
	} while (FindNextFile(hfind, &wfd));
	FindClose(hfind);//закриваємо дескриптор пошуку
}

int count_words(char* s) {
	char vs[] = "Oo";
	int n = 0, i = 0;
	do 
	{
		if (!*s || is_delim(*s)) 
		{
			if ((i > 0) && (strchr(vs, *(s - 1)) != NULL))
				++n;
			i = 0;
		}
		else
		{
			++i;
		}
			
	} 
	while (*s++ != '\0');
	return n;
}

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) //1 - вказівник на початок виконуваного модулю,
{                                                                                    //2 - використовувався в 16- біт Віндовс; 3 - вказівник на строку 
																					 //4 - як буде показуватися вікно
	MSG msg{}; // структура , яка містить інфу про повідомлення
	 // дескриптор вікна, вказівник на об'єкт ядра
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
			hEdbox = CreateWindow(L"EDIT", L"Path of the dir", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 50, 20, 250, 30, hwnd, nullptr, nullptr, nullptr);
			hEdbox1 = CreateWindow(L"EDIT", L"Path of the file", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 50, 120, 250, 30, hwnd, nullptr, nullptr, nullptr);
			hEdbox3 = CreateWindow(L"EDIT", L"Text from file...", WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 350, 20, 350, 200, hwnd, nullptr, nullptr, nullptr);
			HWND hButton1 = CreateWindow(L"BUTTON", L"Create dir", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 70, 250, 30, hwnd, reinterpret_cast<HMENU>(17), nullptr, nullptr);
			HWND hButton2 = CreateWindow(L"BUTTON", L"Create file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 170, 250, 30, hwnd, reinterpret_cast<HMENU>(18), nullptr, nullptr);
			HWND hButton3 = CreateWindow(L"BUTTON", L"Copy files", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 220, 250, 30, hwnd, reinterpret_cast<HMENU>(19), nullptr, nullptr);
			HWND hButton4 = CreateWindow(L"BUTTON", L"Find file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 320, 250, 30, hwnd, reinterpret_cast<HMENU>(20), nullptr, nullptr);
			HWND hButton5 = CreateWindow(L"BUTTON", L"Read file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 370, 250, 30, hwnd, reinterpret_cast<HMENU>(21), nullptr, nullptr);
			HWND hButton6 = CreateWindow(L"BUTTON", L"Write file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 420, 250, 30, hwnd, reinterpret_cast<HMENU>(22), nullptr, nullptr);
			HWND hButton7 = CreateWindow(L"BUTTON", L"Recursive  bypass", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 470, 250, 30, hwnd, reinterpret_cast<HMENU>(23), nullptr, nullptr);
			HWND hButton8 = CreateWindow(L"BUTTON", L"Block file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 520, 250, 30, hwnd, reinterpret_cast<HMENU>(24), nullptr, nullptr);
			HWND hButton9= CreateWindow(L"BUTTON", L"Change creation data", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 350, 270, 250, 30, hwnd, reinterpret_cast<HMENU>(25), nullptr, nullptr);
			HWND hButton10 = CreateWindow(L"BUTTON", L"Count words", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 350, 320, 250, 30, hwnd, reinterpret_cast<HMENU>(26), nullptr, nullptr);
			HWND hButton11 = CreateWindow(L"BUTTON", L"Delete file", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 270, 250, 30, hwnd, reinterpret_cast<HMENU>(27), nullptr, nullptr);
		}
		return 0;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{

			/*Створення папки*/
			case 17:
			{
				TCHAR buffer[40];
				GetWindowText(hEdbox, buffer, 100);// передаємо через вказівник текст в буфер
				if (CreateDirectory((LPCWSTR)buffer, NULL))//вказівник на структуру SECURITY_ATTRIBUTES , так як 0 - то дефолтний дескриптор безпеки
				{
					MessageBox(hwnd, L"Папка создана успешно! ", L"Системное предупреждение", MB_ICONASTERISK);
				}
				else
				{
					MessageBox(hwnd, L"Ошибка при создании папки! ", L"Системное предупреждение", MB_ICONSTOP);
				}
			}
			break;

			/*Створення файлу*/
			case 18:
			{
				TCHAR buffer[40];
				GetWindowText(hEdbox1, buffer, 100);// передаємо через вказівник текст в буфер
				HANDLE FileHandle = CreateFile((LPCWSTR)buffer, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_NEW, NULL, 0);//3 - режим загального доступу
				if (INVALID_HANDLE_VALUE == FileHandle)																										 //6 - атрибут файла
																																							 //7 десскриптор файл шаблона
				{
					MessageBox(hwnd, L"Ошибка при создании файла!", L"Системное предупреждение", MB_ICONHAND);
				}
				else
				{
					MessageBox(hwnd, L"Файл создан успешно! ", L"Системное предупреждение!", MB_ICONASTERISK);
					CloseHandle(FileHandle);
				}
			}
			break;

			/*Копіювання файлів*/
			case 19:
			{
				TCHAR buffer[100];
				GetWindowText(hEdbox, buffer, 100);

				WIN32_FIND_DATA FileData;// описує знайдений файл
				TCHAR szDirPath[] = TEXT("c:\\FILE11\\");
				TCHAR szNewPath[MAX_PATH];
				BOOL fFinished = FALSE;

				SetCurrentDirectory(buffer);

				HANDLE hSearch = FindFirstFile(L"*.txt", &FileData);

				if (hSearch == INVALID_HANDLE_VALUE)
				{
					MessageBox(hwnd, L"Ошибка при поиске!", L"Системное предупреждение", MB_ICONHAND);
				}
				else
				{
					while (!fFinished)
					{
						lstrcpy(szNewPath, szDirPath);// копіює з 2 в 1
						lstrcat(szNewPath, FileData.cFileName);// додає в кінець першого друге
						if (!CopyFile(FileData.cFileName, szNewPath, FALSE))// 3 - операція , якщо файл існує
						{
							MessageBox(hwnd, L"Невозможно скопировать! ", L"Системное предупреждение", MB_ICONHAND);
							break;
						}
						if (!FindNextFile(hSearch, &FileData))
						{
							if (GetLastError() == ERROR_NO_MORE_FILES)
							{
								MessageBox(hwnd, L"Все файлы скопированы! ", L"Системное предупреждение", MB_ICONASTERISK);
								fFinished = TRUE;
							}
						}
					}
				}
				FindClose(hSearch);
			}
			break;

			/*Пошук файлу*/
			case 20:
			{
				WIN32_FIND_DATA FindFileData;
				TCHAR buffer2[40];
				GetWindowText(hEdbox1, buffer2, 100);
				HANDLE hfind = FindFirstFile(buffer2, &FindFileData);
				if (hfind == INVALID_HANDLE_VALUE)
				{
					MessageBox(hwnd, L"Ошибка при поиске!", L"Системное предупреждение", MB_ICONHAND);
				}
				else
				{
					MessageBox(hwnd, L"Файл успешно найден!", L"Системное предупреждение", MB_ICONASTERISK);
					FindClose(hfind);
				}
			}
			break;

			/*Читання файлу*/
			case 21:
			{
				TCHAR buffer[100];
				GetWindowText(hEdbox1, buffer, 100);// передаємо через вказівник текст в буфер
				HANDLE FileHandle = CreateFile(buffer, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				if (FileHandle==INVALID_HANDLE_VALUE)
				{
					MessageBox(hwnd, L"Ошибка при открытии файла!", L"Системное предупреждение", MB_ICONHAND);
				}
				else
				{
					DWORD NumRead = 0;
					LPVOID Buf = (CHAR*)calloc(BUF_SIZE + 1, sizeof(CHAR));//масив нулів 1 - клк ел. 2 - розмір одного ел
					BOOL RFile = ReadFile(FileHandle, Buf, BUF_SIZE, &NumRead, NULL);
					if (RFile == FALSE)
					{
						MessageBox(hwnd, L"Не удалось прочитать текст!", L"Системное предупреждение", MB_ICONHAND);
					}
					else
					{
						SendMessageA(hEdbox3, WM_SETTEXT, WPARAM(0), (LPARAM)Buf);
					}
					CloseHandle(FileHandle);
				}
				
			}
			break;

			/*Запис у файл*/
			case 22:
			{
				char Buffer[] = "РОБОТА З ФАЙЛАМИ для WIN32.Variant 14\r\n";
				DWORD NumBuffer = strlen(Buffer);

				TCHAR File_buffer[200];
				GetWindowText(hEdbox1, File_buffer, 300);// передаємо через вказівник текст в буфер
				HANDLE FileHandle = CreateFile(File_buffer, GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

				if (FileHandle == INVALID_HANDLE_VALUE)
				{
					MessageBox(hwnd, L"Ошибка при открытии файла!", L"Системное предупреждение", MB_ICONHAND);
				}
				else
				{
					DWORD NumBytesWritten = SetFilePointer(FileHandle, NULL, NULL, FILE_END);// 2, 3 - байти переміення вказівника
					BOOL WFile = WriteFile(FileHandle, Buffer, NumBuffer, &NumBytesWritten, NULL);
					if (WFile == FALSE)
					{
						MessageBox(hwnd, L"Не удалось записать текст!", L"Системное предупреждение", MB_ICONHAND);
					}
					else
					{
						MessageBox(hwnd, L"Текст успешно записан в файл!", L"Системное предупреждение", MB_ICONASTERISK);
					}
					CloseHandle(FileHandle);
				}
			}
			break;

			/*Рекурсивний обхід*/
			case 23:
			{
				HANDLE hFile = CreateFile(L"D:\\ert\\log.txt", GENERIC_WRITE,	FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				TCHAR buffer[40];
				GetWindowText(hEdbox, buffer, 100);
				WriteData(hFile,buffer);
				CloseHandle(hFile);
			}
			break;

			/*Блокування файлу*/
			case 24:
			{
				TCHAR File_buffer[200];
				GetWindowText(hEdbox1, File_buffer, 300);// передаємо через вказівник текст в буфер
				HANDLE FileHandle = CreateFile(File_buffer, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				OVERLAPPED overlapvar = { 0 };
				BOOL LFile = LockFileEx(FileHandle, LOCKFILE_EXCLUSIVE_LOCK, NULL, MAXDWORD, MAXDWORD, &overlapvar);//3 - зарезервовано
				if (LFile == FALSE)																					//4, 5 - довжина 
				{																									// 6 - структура 
					MessageBox(hwnd, L"Ошибка при блокировке!", L"Системное предупреждение", MB_ICONHAND);
				}
				else
				{
					MessageBox(hwnd, L"Файл заблокировано успешно! ", L"Системное предупреждение!", MB_ICONASTERISK);
				}
			}
			break;

			/*Зміна дати створення*/
			case 25:
			{
				TCHAR File_buffer[200];
				GetWindowText(hEdbox1, File_buffer, 300);// передаємо через вказівник текст в буфер
				HANDLE hFile = CreateFile(File_buffer, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

				FILETIME FileTime;
				//nYear = ((011244 / 512) & 255) + 1980;    //9-15  bits
				//int nMonth = (011244 / 32) & 15;                //5-8   bits
				//int nDay = 011244 & 31;                    //0-4   bits
				DosDateTimeToFileTime(WORD(011244), WORD(787511), &FileTime);// перетворює час в файловий час
				BOOL Tfile = SetFileTime(hFile, &FileTime, NULL, NULL);// встановлює час
				if (Tfile == true)
				{
					MessageBox(hwnd, L"Дата успешно изменена!", L"Системное предупреждение", MB_ICONINFORMATION);
				}
				else
				{
					MessageBox(hwnd, L"Ошибка при изменении даты!", L"Системное предупреждение", MB_ICONERROR);
				}

				BOOL AFile = SetFileAttributes(File_buffer, FILE_ATTRIBUTE_READONLY);
				if (AFile==FALSE)
				{
					MessageBox(hwnd, L"Ошибка при изменении атрибута!", L"Системное предупреждение", MB_ICONERROR);
				}
				else 
				{
					MessageBox(hwnd, L"Атрибут успешно изменен!", L"Системное предупреждение", MB_ICONINFORMATION);
				}
				CloseHandle(hFile);
			}
			break;

			/*Підрахунок слів*/
			case 26: 
			{
				OVERLAPPED Overlapped = { 0 };
				Overlapped.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);//1 - вказівник на структуру SECURITY_ATTRIBUTES  2 - автомат. скидання стану події на несигнальний 
				TCHAR File_buffer[200];								   //3 - не сигналізується початковий стан об'єкта  4 - і'м об'єкта
				GetWindowText(hEdbox1, File_buffer, 300);// передаємо через вказівник текст в буфер
				HANDLE FileHandle = CreateFile(File_buffer, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED | FILE_ATTRIBUTE_NORMAL, NULL);
				if (FileHandle == INVALID_HANDLE_VALUE)
				{
					MessageBox(hwnd, L"Ошибка при открытии файла!", L"Системное предупреждение", MB_ICONHAND);
				}
				else
				{
					char buff[1000] = { 0 };
					BOOL RFile = ReadFileEx(FileHandle, buff, sizeof(buff), &Overlapped, NULL);
					if (RFile == FALSE)
					{
						MessageBox(hwnd, L"Не удалось прочитать текст!", L"Системное предупреждение", MB_ICONHAND);
					}
					else
					{
						std::string str = std::to_string(count_words(buff));
						SendMessageA(hEdbox3, WM_SETTEXT, WPARAM(0), LPARAM(str.c_str()));
					}
				}

			}
			break;

			/*Видалення файлу*/
			case 27:
			{
				TCHAR buffer[100];
				GetWindowText(hEdbox1, buffer, 100);// передаємо через вказівник текст в буфер
				BOOL RFile = DeleteFile(buffer);
				if (RFile)
				{
					MessageBox(hwnd, L"Файл успешно удален!", L"Системное предупреждение", MB_ICONINFORMATION);
				}
				else
				{
					MessageBox(hwnd, L"Ошибка при удалении файла!", L"Системное предупреждение", MB_ICONERROR);
				}
			}
			break;
			}
		}
		return 0;

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
	if (hwnd = CreateWindow(wc.lpszClassName, L"Laba2", WS_OVERLAPPEDWINDOW, //створення вікна WS_OVERLAPPEDWINDOW - стилі вікна
		0, 0, 800, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)// дескриптор батька і меню - 0
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow); //показ вікна
	UpdateWindow(hwnd);//перемалювати наше вікно

	while (GetMessage(&msg, nullptr, 0, 0)) //обробка повідомлень 1 - вказівник на нашу структуру, 2 - hwnd вікна, 3 - фільтри
	{
		TranslateMessage(&msg);//розшифровує наше повідомлення
		DispatchMessageW(&msg);//передає повідолмення у віконну процедуру на обробку
	}
	return  static_cast<int>(msg.wParam);//повернути значення точки входу 
}
