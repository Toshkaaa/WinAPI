#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <string>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <iostream>
#define BUF_SIZE 4096
using namespace std;

HWND hButton, hButton1, hButton2, hButton3 , hButton4, hButton5, hLogo, hEdbox, hEdbox2, hEdbox3, hEdbox4, hwnd{};
HBITMAP hLogoImage, hBmpOld;

class Button 
{
	bool state;
public:
	void SetState(int x) 
	{
		state = x;
	};
	bool GetState()
	{
		return state;
	}
};

class Display
{
	string resolution;
	float diagonal;
	void show_on_display()
	{
		SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
	};
public:
	Display()
	{
		resolution = "1080p";
		diagonal = 60;
	}
	void get_game_signal()
	{
		show_on_display();
	}
	void get_signal()
	{
		SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP,NULL);
	}
};

class Game
{
	string game_name;
	char buffer[BUF_SIZE];
public:
	void SetGame()
	{
		buffer[BUF_SIZE] = {0};
		GetWindowTextA(hEdbox4, buffer, MAX_PATH);
		game_name = string(buffer);
	}
	string GetGame()
	{
		return game_name;
	}
};

class Libraries
{
	string lib;
public:
	Libraries()
	{
		lib = "Lib32";
	}
	string GetLib()
	{
		return lib;
	}
};

class Socket
{
	int wire_long;
public:
	Socket()
	{
		wire_long = 5;
	}
	bool get_power()
	{
		if (wire_long > 3)
		{
			return 1;
		}
		else
		{
			MessageBox(hwnd, L"Please connect longer wire!", L"Socket!", MB_ICONHAND);
			return 0;
		}
	};
};

class Transformation
{
	int electricity_out;
	int electricity_in;
public:
	int Set_electricity()
	{
		char buffer[100];
		GetWindowTextA(hEdbox, buffer, MAX_PATH);
		return electricity_in = stoi(string(buffer));
	}
	int convert_energy()
	{
		electricity_out = Set_electricity() / 2;
		if (electricity_out > 120 and electricity_out < 320)
		{
			return electricity_out;
		}
		else
		{
			MessageBox(hwnd, L"Please give normal electricity on the input!", L"Transformation", MB_ICONHAND);
			return 0;
		}
	};
};

class CoolingSystem
{
	Button button_cool_state;
	int temperature;
	int speed;
public:
	void cool_state_change(int sp)
	{
		if (sp == 0 and button_cool_state.GetState()!= 0)
		{
			MessageBox(hwnd, L"Fans stoped!", L"CoolingSystem", MB_ICONINFORMATION);
			button_cool_state.SetState(0);
		}
		else
		{
			if (button_cool_state.GetState() != 1)
			{
				button_cool_state.SetState(1);
				MessageBoxA(hwnd, ("Fans started! Temperature = " + to_string(temperature) + " °C").c_str(), "CoolingSystem", MB_ICONINFORMATION);
			}
			else
			{
				string message = "Fans is working!";
				MessageBoxA(hwnd, message.c_str(), "CoolingSystem", MB_ICONINFORMATION);
			}
		}
	};

	void temperature_check()
	{
		srand(time(0));
		temperature = 10 + rand() % 80;
		if (temperature >= 80)
		{
			cool_state_change(200);
			MessageBoxA(hwnd, ("Please reduce your activity because of high temperature = " + to_string(temperature) + "°C").c_str(), "CoolingSystem", MB_ICONEXCLAMATION);
		}
		else if (temperature >= 40 and temperature < 80)
		{
			cool_state_change(150);
		}
		else
		{
			cool_state_change(0);
		}
	};
};

class Memory
{
	char buffer0[BUF_SIZE];
	char buffer[BUF_SIZE] = { 0 };
	string memory_type;
	HANDLE hFileMemory;
	int size;
public:
	Memory()
	{
		memory_type = "GDDR6";
		size = 16;
	}

	string find_data_in_RAM()
	{
		DWORD iCount = 0;
		char buff[BUF_SIZE] = {0};
		HANDLE RAMhFile = CreateFile(L"RAM_Memory.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, 0);
		ReadFile(RAMhFile, buff, BUF_SIZE, &iCount, NULL);
		CloseHandle(RAMhFile);
		return string(buff);
	};

	bool get_data(string x)
	{
		DWORD iCount = 0;
		hFileMemory = CreateFile(L"Memory.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, 0);
		buffer0[BUF_SIZE] = { 0 };
		if (!ReadFile(hFileMemory, buffer0, BUF_SIZE, &iCount, NULL))
		{
			MessageBox(hwnd, L"Error during reading memory!", L"Memory!", MB_ICONERROR);
		}
		else
		{
			for (int i = 0; i < BUF_SIZE; i++)
			{
				if (buffer0[i] == x[0] and buffer0[i + 1] == x[1])
				{
					i += x.length() + 2;
					CloseHandle(hFileMemory);
					for (int j = 0; j < BUF_SIZE; j++)
					{
						if (buffer0[i] != '\n')
						{
							buffer[j] = buffer0[i];
							i++;
						}
						else
						{
							break;
						}
					}
					MessageBoxA(hwnd, buffer, "Memory", NULL);
					save_data_to_RAM(buffer);
					return 1;
				}
			}
			MessageBox(hwnd, L"This game is not in memory!", L"Memory!", MB_ICONERROR);
			return 0;
		}
		
	};

	void save_data_to_RAM(string x)
	{
		HANDLE RAMhFile = CreateFile(L"RAM_Memory.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, 0);
		DWORD NumBytesWritten = 0;
		find_data_in_RAM();
		WriteFile(RAMhFile, x.c_str(), x.length(), &NumBytesWritten, NULL);
		CloseHandle(RAMhFile);
	};

	void clear_data_from_RAM()
	{
		HANDLE RAMhFile = CreateFile(L"RAM_Memory.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, 0);
		CloseHandle(RAMhFile);
	}

	string send_data()
	{
		return (string)buffer;
	};
};

class Processing
{
	int number_of_cores;
	float frequency;
public:
	Processing()
	{
		number_of_cores = 8;
		frequency = 3500000000;
	}

	string Process_game(string x)
	{
		x.erase(remove_if(x.begin(), x.end(), isspace), x.end());
		return x;
	}

	void Send_result(string x)
	{
		hLogoImage = (HBITMAP)LoadImageA(NULL, x.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
};

class ControlSystem
{
protected:
	string os_model;
	Libraries Library;
	Game game;
public:
	Display display;
	void connect_library()
	{
		string phrase = "Library " + Library.GetLib() + " connected!";
		MessageBoxA(hwnd, phrase.c_str(), "ControlSystem", MB_ICONINFORMATION);
	}

	void game_start(Memory memory, Processing Proc)
	{
		game.SetGame();
		if (memory.get_data(game.GetGame()))
		{
			Proc.Send_result(Proc.Process_game(memory.send_data()));
			display.get_game_signal();
			EnableWindow(hButton3, FALSE);
			EnableWindow(hEdbox4, FALSE);
		}
	}

	void cancel_game(Memory memory)
	{
		memory.clear_data_from_RAM();
		display.get_signal();
		EnableWindow(hButton3, TRUE);
		EnableWindow(hEdbox4, TRUE);
	}

	void check_saved_game(Memory memory,Processing Proc)
	{
		if (memory.find_data_in_RAM()!="")
		{
			MessageBoxA(hwnd, "U have unsafed game! Restoring...", "ControlSystem", MB_ICONINFORMATION);
			Proc.Send_result(Proc.Process_game(memory.find_data_in_RAM()));
			display.get_game_signal();
			EnableWindow(hButton3, FALSE);
			EnableWindow(hEdbox4, FALSE);
		}
	}
};

class PowerSystem
{
private:
	Socket socket;
	Transformation transformator;
public:
	Button button_power;
	PowerSystem()
	{
		button_power.SetState(0);
	};

	bool supply()
	{
		if (socket.get_power() and transformator.convert_energy() and button_power.GetState()!=1)
		{
			MessageBox(hwnd, L"Power on!", L"PowerSystem", MB_ICONASTERISK);
			button_power.SetState(1);
			return button_power.GetState();
		}
		else
		{
			MessageBox(hwnd, L"PlaySation is working now!", L"PowerSystem", MB_ICONASTERISK);
			return 0;
		}
	};

	bool finish(ControlSystem ControlSys)
	{
		if (button_power.GetState()!=0)
		{
			ControlSys.display.get_signal();
			EnableWindow(hButton3, FALSE);
			EnableWindow(hButton4, FALSE);
			EnableWindow(hEdbox4, FALSE);
			MessageBox(hwnd, L"Power off!", L"PowerSystem", MB_ICONASTERISK);
			button_power.SetState(0);
		}
		return button_power.GetState();
	}
};

class Periphery
{
protected:
	string name;
	string connector;
public:
	char buffer[100] = {0};
	char buffer1[100] = {0};

	void SetPeriphery()
	{
		
		GetWindowTextA(hEdbox2, buffer, MAX_PATH);
		name = string(buffer);

		
		GetWindowTextA(hEdbox3, buffer1, MAX_PATH);
		connector = string(buffer1);
	}

	bool insert_to_table(HANDLE hFile)
	{
		string to_write = "Name: " + name + "\nVersion: " + connector +"\n";
		DWORD NumBytesWritten = SetFilePointer(hFile, 0, NULL, FILE_END);
		if (!WriteFile(hFile, to_write.c_str(), to_write.length(), &NumBytesWritten, NULL))
		{
			MessageBox(hwnd, L"Error during inserting table!", L"RadioModule!", MB_ICONHAND);
			return 0;
		}
		else
		{
			EnableWindow(hButton4, TRUE);
			EnableWindow(hButton3, TRUE);
			EnableWindow(hEdbox4, TRUE);
			return 1;
		}
	};
};

class RadioModule : public Periphery
{
	class Internet
	{
		int speed;
		wstring dns_server;
	public:
		Internet()
		{
			srand(time(0));
			speed = 50 + rand() % 50;
		};

		bool ping_server()
		{
			dns_server = L"8.8.8.8";
			SetEnvironmentVariable(L"Internet", dns_server.c_str());
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));
			if (CreateProcess(L"D:\\source\\repos\\SysEngineering\\Debug\\SysEngineering.exe", NULL,
				NULL,
				NULL,
				TRUE,
				NULL,
				NULL,
				NULL,
				&si,
				&pi))
			{

				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				return 1;
			}
		}

		string Get_data()
		{
			string info = "Speed = " + to_string(speed) + ". Connection sucess!\n";
			return info;
		}
	};
public:
	Internet Internet_connect;
	RadioModule()
	{
		name = "RadioModule RTP-507";
		connector = "V 2.3";
	};

	bool connect_network()
	{
		if (!Internet_connect.ping_server())
		{
			MessageBox(hwnd,L"Please check your internet connection!" , L"RadioModule!", MB_ICONHAND);
			return 0;
		}
		else
		{
			MessageBoxA(hwnd, Internet_connect.Get_data().c_str(), "RadioModule!", MB_ICONASTERISK);
			return 1;
		}
	};
};

class BIOS : public ControlSystem
{
	string version;
	HANDLE hFile;
public:
	bool load_OS()
	{	
		os_model = "Orbis OS";
		version ="5.0";
		MessageBoxA(hwnd, ("Bios version: " + version).c_str(),("OS: " + os_model).c_str(),NULL);
		return 1;
	}

	void connect_device_table(RadioModule RadioMod,Periphery Per)
	{
		hFile = CreateFile(L"Data.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, 0);
		if (hFile)
		{
			RadioMod.insert_to_table(hFile);
			Per.SetPeriphery();
			Per.insert_to_table(hFile);
		}
	}

	bool check_device(RadioModule RadioMod,Periphery Per)
	{
		if (RadioMod.connect_network())
		{
			connect_device_table(RadioMod,Per);
			return 1;
		}
	};
};

class PlaySation
{
public:
	CoolingSystem CoolSys;
	PowerSystem PowerSys;
	RadioModule radioModul;
	ControlSystem ControlSys;
	Processing Process;
	Periphery Per;
	Memory mem;
	BIOS bios;
	bool working()
	{
		if (PowerSys.button_power.GetState())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};

PlaySation PS;
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	RECT rect;
	MSG msg{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));//дескриптор кисті 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);//курсор 
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);//іконка
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);//маленька іконка
	wc.hInstance = hInstance;//дескриптор экземпляра приложения
	wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (uMsg) // обробка віконних повідомлень
		{
			case  WM_CREATE:
			{
				hLogo = CreateWindow(L"Static", NULL,  WS_CHILD | WS_VISIBLE| SS_BITMAP , 500,20, 0, 0, hwnd, nullptr, nullptr, nullptr);
				hButton = CreateWindow(L"BUTTON", L"Power on", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 0, 300, 30, hwnd, reinterpret_cast<HMENU>(15), nullptr, nullptr);
				hButton1 = CreateWindow(L"BUTTON", L"Connect your periphery ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100,130, 300, 30, hwnd, reinterpret_cast<HMENU>(16), nullptr, nullptr);
				hButton2 = CreateWindow(L"BUTTON", L"Check temperature", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 320, 300, 30, hwnd, reinterpret_cast<HMENU>(17), nullptr, nullptr);
				hButton3 = CreateWindow(L"BUTTON", L"Start game!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 825, 505, 300, 30, hwnd, reinterpret_cast<HMENU>(18), nullptr, nullptr);
				EnableWindow(hButton3, FALSE);
				hButton4 = CreateWindow(L"BUTTON", L"Cancel and save game!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 825, 605, 300, 30, hwnd, reinterpret_cast<HMENU>(19), nullptr, nullptr);
				EnableWindow(hButton4, FALSE);
				hButton5 = CreateWindow(L"BUTTON", L"Power off!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 360, 300, 30, hwnd, reinterpret_cast<HMENU>(20), nullptr, nullptr);
				hEdbox = CreateWindow(L"EDIT", L"Enter your electricity", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE, 100, 80, 300, 30, hwnd, nullptr, nullptr, nullptr);
				hEdbox2 = CreateWindow(L"EDIT", L"Name of Periphery", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE, 100, 200, 140, 100, hwnd, nullptr, nullptr, nullptr);
				hEdbox3 = CreateWindow(L"EDIT", L"Version of Periphery", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE, 260, 200, 140, 100, hwnd, nullptr, nullptr, nullptr);
				hEdbox4 = CreateWindow(L"EDIT", L"Name of your game", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE, 825, 550, 300, 30, hwnd, nullptr, nullptr, nullptr);
				EnableWindow(hEdbox4, FALSE);
			}
			return 0;

			case WM_COMMAND:
			{
				switch (LOWORD(wParam))
				{
					case 15:
					{	
						if (PS.PowerSys.supply())
						{
							PS.bios.load_OS();
						}
					}
					break;

					case 16:
					{
						
						if (PS.working())
						{
							PS.bios.check_device(PS.radioModul, PS.Per);
							PS.ControlSys.check_saved_game(PS.mem,PS.Process);
						}
						else
						{
							MessageBox(hwnd, L"Please turn on your PlayStation!", L"PlayStation!", MB_ICONERROR);
						}
					}
					break;

					case 17:
					{
						//EM_LINELENGTH
						//int size = SendMessage(hLogo, EM_GETLINECOUNT, -1, 0);
						//MessageBoxA(hwnd, to_string(size).c_str(), "dawd", NULL);
						if (PS.working())
						{
							PS.CoolSys.temperature_check();
						}
						else
						{
							MessageBox(hwnd, L"Please turn on your PlayStation!", L"PlayStation!", MB_ICONERROR);
						}
					}
					break;
					
					case 18:
					{
						if (PS.working())
						{
							PS.ControlSys.connect_library();
							PS.ControlSys.game_start(PS.mem, PS.Process);
						}
						else
						{
							MessageBox(hwnd, L"Please turn on your PlayStation!", L"PlayStation!", MB_ICONERROR);
						}
					}
					break;

					case 19:
					{
						if (PS.working())
						{
							PS.ControlSys.cancel_game(PS.mem);
						}
						else
						{
							MessageBox(hwnd,L"Please turn on your PlayStation!",L"PlayStation!",MB_ICONERROR);
						}
					}
					break;

					case 20:
					{
						PS.PowerSys.finish(PS.ControlSys);
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
				string text = "Connect your electricity: ";
				TextOutA(Canvas, 170, 50, text.c_str(), text.length());
				text = "Enter periphery name and version to connect: ";
				TextOutA(Canvas, 110, 170, text.c_str(), text.length());
				Rectangle(Canvas,800, 500, 1150, 650);
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
	if (hwnd = CreateWindow(wc.lpszClassName, L"PlayStation", WS_OVERLAPPEDWINDOW, //створення вікна WS_OVERLAPPEDWINDOW - стилі вікна
		0, 0, 1200, 700, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)// дескриптор батька і меню - 0
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
