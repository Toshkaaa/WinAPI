#include <windows.h> // заголовочный файл,  який має у собі функції API
#include <string>

HWND hEdbox{};
HWND hEdbox1{};
HWND hEdboxS{};

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) //1 - вказівник на початок виконуваного модулю,
{                                                                                    //2 - використовувався в 16- біт Віндовс; 3 - вказівник на строку 
																					 // 4 - як буде показуватися вікно
	MSG msg{}; // структура , яка містить інфу про повідомлення
	HWND hwnd{}; // дескриптор вікна, вказівник на об'єкт ядра
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; // характеристики вікна
	wc.cbClsExtra = 0; // доп виділення пам'яті 
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//дескриптор кисті 
	wc.hCursor = LoadCursor(nullptr,IDC_ARROW);//курсор 
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);//іконка
	wc.hIconSm= LoadIcon(nullptr, IDI_APPLICATION);//маленька іконка
	wc.hInstance = hInstance;//дескриптор экземпляра приложения
	wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT //процедура , яка відповідає за обробку повідомлень
																					 // 1 - дескриптор вікна; 2 - код повідомлення; 3,4 - вказівники, 
																					 //в яких міститься необіхна інфа для повідомлення	
	{ 
		switch (uMsg) // обробка віконних повідомлень
		{	
			case  WM_CREATE:
			{
				hEdbox = CreateWindow(L"EDIT", nullptr, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 100, 150, 300, 64, hwnd, nullptr, nullptr, nullptr);
				hEdbox1 = CreateWindow(L"EDIT", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 100, 50, 300, 64, hwnd, nullptr, nullptr, nullptr);
				HWND hButton = CreateWindow(L"BUTTON", L"My Task (Var 14)", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 0, 300, 30, hwnd, reinterpret_cast<HMENU>(15), nullptr, nullptr);
				HWND hButton1 = CreateWindow(L"BUTTON", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 230, 150, 30, hwnd, reinterpret_cast<HMENU>(13), nullptr, nullptr);
				HWND hButton2 = CreateWindow(L"BUTTON", L"Cancel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 230, 150, 30, hwnd, reinterpret_cast<HMENU>(17), nullptr, nullptr);
			}
			return 0;

			case WM_COMMAND: 
			{
				switch (LOWORD(wParam))
				{
				case 13: 
				{
					SendMessageA(hEdbox, WM_SETTEXT, WPARAM(0), LPARAM(" "));
					try
					{
						std::wstring test{};// об'єкт типу wstring
						test.resize(MAX_PATH);//змінюємо розмір до константи 
						GetWindowText(hEdbox1, &test[0], MAX_PATH);// передає через вказівник текст в буфер
						int test2 = std::stoi(test);// конвертуємо в інт
						switch (test2 / 100)
						{
							case 1: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Сто ")); break;
							case 2: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Двісті ")); break;
							case 3: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Триста ")); break;
							case 4: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Чотириста ")); break;
							case 5: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("П'ятстот ")); break;
							case 6: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Шістсот ")); break;
							case 7: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Сімсот ")); break;
							case 8: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Вісімсот ")); break;
							case 9: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Дев'ятсот ")); break;
						}
						switch ((test2 % 100) / 10)
						{
							case 2: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("двадцять ")); break;
							case 3: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("тридцять ")); break;
							case 4: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("сорок ")); break;
							case 5: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("п'ятдесят ")); break;
							case 6: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("шістдесят ")); break;
							case 7: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("сімдесят ")); break;
							case 8: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("вісімдесят ")); break;
							case 9: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("дев'яносто ")); break;
						}
						if ((test2 % 100) >= 10 & (test2 % 100) < 20)
						{
							switch (test2 % 100)
							{
								case 10: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("десять ")); break;
								case 11: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("одинадцять ")); break;
								case 12: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("дванадцять ")); break;
								case 13: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("тринадцять ")); break;
								case 14: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("чотирнадцять ")); break;
								case 15: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("п'ятнадцять ")); break;
								case 16: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("шістнадцять ")); break;
								case 17: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("сімнадцять ")); break;
								case 18: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("вісімнадцять ")); break;
								case 19: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("дев'яднадцять ")); break;
							}
						}
						else
						{
							switch (test2 % 10)
							{
								case 1: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("один ")); break;
								case 2: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("два ")); break;
								case 3: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("три ")); break;
								case 4: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("чотири ")); break;
								case 5: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("п'ять ")); break;
								case 6: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("шість ")); break;
								case 7: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("сім ")); break;
								case 8: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("вісім ")); break;
								case 9: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("дев'ять ")); break;
							}
						}
						if (test2 == 0)
						{
							SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("Нуль "));
						}
					}
					catch (const std::exception&)
					{
						MessageBox(hwnd, L"Можно вводить только числа и без пробелов!\nТакже не допускайте пустого ввода! ", L"Системное предупреждение!", MB_ICONEXCLAMATION);
					}
				}
				break;

				case 15: 
				{
					MessageBox(hwnd,L"test",L"test",MB_ICONEXCLAMATION);
				}
				break;

				case 17: 
				{
					SendMessageA(hEdbox, WM_SETTEXT, WPARAM(0), LPARAM(" "));
				}

				break;
				}
			}
			return 0;
			
			case WM_PAINT: 
			{

				PAINTSTRUCT ps;// струткура , містить інфу, що малювати на вікні
				HDC Canvas = BeginPaint(hwnd, &ps);// дескриптор дисплея , який буде використовуватися для малювання
				SetTextColor(Canvas, RGB(255, 0, 0));// встановлюємо колір
				TextOut(Canvas,10, 320, L"System Directory: ", 19);
				TextOut(Canvas,10, 340, L"Computer Name: ", 18);
				TextOut(Canvas,10, 360, L"User Name: ", 12);

				wchar_t buffer[MAX_PATH];
				GetSystemDirectory(buffer, MAX_PATH);// 1 вказівник на буфер, який отримує дані 2 - його розмір

				TextOut(Canvas,135,320, buffer,20);

				DWORD size;
				size = sizeof(buffer);
				GetComputerName(buffer, &size);

				TextOut(Canvas,125,340, buffer, 16);

				DWORD bufCharCount[MAX_PATH];

				GetUserName(buffer, bufCharCount);
				TextOut(Canvas,90, 360, buffer, 4);

				EndPaint(hwnd, &ps);
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
	if (hwnd = CreateWindow(wc.lpszClassName, L"Laba1", WS_OVERLAPPEDWINDOW, //створення вікна WS_OVERLAPPEDWINDOW - стилі вікна
		0, 0, 500, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)// дескриптор батька і меню - 0
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow); //показ вікна
	UpdateWindow(hwnd);//перемалювати наше вікно

	while (GetMessage(&msg,nullptr,0,0)) //обробка повідомлень 1 - вказівник на нашу структуру, 2 - hwnd вікна, 3 - фільтри
	{
		TranslateMessage(&msg);//розшифровує наше повідомлення
		DispatchMessageW(&msg);//передає повідолмення у віконну процедуру на обробку
	}
	return  static_cast<int>(msg.wParam);//повернути значення точки входу 
}
