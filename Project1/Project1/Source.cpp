#include <windows.h> // ������������ ����,  ���� �� � ��� ������� API
#include <string>

HWND hEdbox{};
HWND hEdbox1{};
HWND hEdboxS{};

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) //1 - �������� �� ������� ������������ ������,
{                                                                                    //2 - ���������������� � 16- �� ³�����; 3 - �������� �� ������ 
																					 // 4 - �� ���� ������������ ����
	MSG msg{}; // ��������� , ��� ������ ���� ��� �����������
	HWND hwnd{}; // ���������� ����, �������� �� ��'��� ����
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; // �������������� ����
	wc.cbClsExtra = 0; // ��� �������� ���'�� 
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//���������� ���� 
	wc.hCursor = LoadCursor(nullptr,IDC_ARROW);//������ 
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);//������
	wc.hIconSm= LoadIcon(nullptr, IDI_APPLICATION);//�������� ������
	wc.hInstance = hInstance;//���������� ���������� ����������
	wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT //��������� , ��� ������� �� ������� ����������
																					 // 1 - ���������� ����; 2 - ��� �����������; 3,4 - ���������, 
																					 //� ���� �������� ������� ���� ��� �����������	
	{ 
		switch (uMsg) // ������� ������� ����������
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
						std::wstring test{};// ��'��� ���� wstring
						test.resize(MAX_PATH);//������� ����� �� ��������� 
						GetWindowText(hEdbox1, &test[0], MAX_PATH);// ������ ����� �������� ����� � �����
						int test2 = std::stoi(test);// ���������� � ���
						switch (test2 / 100)
						{
							case 1: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("��� ")); break;
							case 2: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���� ")); break;
							case 3: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("������ ")); break;
							case 4: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("��������� ")); break;
							case 5: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("�'������ ")); break;
							case 6: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("س����� ")); break;
							case 7: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("ѳ���� ")); break;
							case 8: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("³����� ")); break;
							case 9: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���'����� ")); break;
						}
						switch ((test2 % 100) / 10)
						{
							case 2: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("�������� ")); break;
							case 3: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("�������� ")); break;
							case 4: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("����� ")); break;
							case 5: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("�'������� ")); break;
							case 6: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("��������� ")); break;
							case 7: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("������� ")); break;
							case 8: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("�������� ")); break;
							case 9: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���'������ ")); break;
						}
						if ((test2 % 100) >= 10 & (test2 % 100) < 20)
						{
							switch (test2 % 100)
							{
								case 10: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("������ ")); break;
								case 11: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���������� ")); break;
								case 12: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���������� ")); break;
								case 13: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���������� ")); break;
								case 14: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("������������ ")); break;
								case 15: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("�'��������� ")); break;
								case 16: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("����������� ")); break;
								case 17: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("��������� ")); break;
								case 18: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���������� ")); break;
								case 19: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���'��������� ")); break;
							}
						}
						else
						{
							switch (test2 % 10)
							{
								case 1: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���� ")); break;
								case 2: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("��� ")); break;
								case 3: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("��� ")); break;
								case 4: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("������ ")); break;
								case 5: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("�'��� ")); break;
								case 6: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("����� ")); break;
								case 7: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("�� ")); break;
								case 8: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("��� ")); break;
								case 9: SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���'��� ")); break;
							}
						}
						if (test2 == 0)
						{
							SendMessageA(hEdbox, EM_REPLACESEL, WPARAM(0), LPARAM("���� "));
						}
					}
					catch (const std::exception&)
					{
						MessageBox(hwnd, L"����� ������� ������ ����� � ��� ��������!\n����� �� ���������� ������� �����! ", L"��������� ��������������!", MB_ICONEXCLAMATION);
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

				PAINTSTRUCT ps;// ��������� , ������ ����, �� �������� �� ���
				HDC Canvas = BeginPaint(hwnd, &ps);// ���������� ������� , ���� ���� ����������������� ��� ���������
				SetTextColor(Canvas, RGB(255, 0, 0));// ������������ ����
				TextOut(Canvas,10, 320, L"System Directory: ", 19);
				TextOut(Canvas,10, 340, L"Computer Name: ", 18);
				TextOut(Canvas,10, 360, L"User Name: ", 12);

				wchar_t buffer[MAX_PATH];
				GetSystemDirectory(buffer, MAX_PATH);// 1 �������� �� �����, ���� ������ ��� 2 - ���� �����

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
	if (hwnd = CreateWindow(wc.lpszClassName, L"Laba1", WS_OVERLAPPEDWINDOW, //��������� ���� WS_OVERLAPPEDWINDOW - ���� ����
		0, 0, 500, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)// ���������� ������ � ���� - 0
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow); //����� ����
	UpdateWindow(hwnd);//������������ ���� ����

	while (GetMessage(&msg,nullptr,0,0)) //������� ���������� 1 - �������� �� ���� ���������, 2 - hwnd ����, 3 - �������
	{
		TranslateMessage(&msg);//���������� ���� �����������
		DispatchMessageW(&msg);//������ ����������� � ������ ��������� �� �������
	}
	return  static_cast<int>(msg.wParam);//��������� �������� ����� ����� 
}
