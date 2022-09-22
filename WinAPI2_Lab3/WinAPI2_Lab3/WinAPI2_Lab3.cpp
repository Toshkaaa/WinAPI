#include <iostream>
#pragma comment(lib,"ws2_32.lib")// для отримання доступу до певних функцій
#include <winsock2.h> // бібліотека для роботи з мережею
#include <windows.h>
#include <Ws2tcpip.h>
#include <string>
using namespace std;

#pragma warning(disable:4996) 

struct PARAMETERS
{
    string bufferString;
    int number;
    string foundstring;
};

PARAMETERS param;

DWORD WINAPI ThreadFun(void* par)
{
    PARAMETERS* params = (PARAMETERS*)par;
    HANDLE hFile = CreateFileA((params->bufferString.c_str()), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, 0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        cout << "Error during opening file!" << endl;
    }
    else
    {
        DWORD NumRead = 0;
        char filebuff[1000] = { 0 };
        if (ReadFile(hFile, filebuff, sizeof(filebuff), &NumRead, NULL))
        {
            int number = param.number;
            int counter = 1;
            string foudnstr;
            for (int i = 0; i < sizeof(filebuff); i++)
            {
                if (counter == number)
                {
                    while (filebuff[i] != '\n')
                    {
                        foudnstr.push_back(filebuff[i]);
                        i++;
                    }
                    param.foundstring = foudnstr;
                    break;
                }
                else
                {
                    if (filebuff[i] == '\n')
                    {
                        counter += 1;
                    }
                }
            }
            
            string thisNumber = "";
            for (int i = 0; i < sizeof(filebuff); i++)
            {
                if (filebuff[i] == '\n')
                {
                    cout << stoi(thisNumber) + number << "   ";
                    thisNumber = "";
                }
                else 
                {
                    thisNumber.push_back(filebuff[i]);
                }

            }
        }
        cout << endl;
    }
    return 0;
}



int main()
{
    //Creates a WORD value by concatenating the specified values
    WORD WinSockVersion = MAKEWORD(2, 2);
    cout << endl << " ----- This is server side -----" << endl << endl;
    WSADATA wsaData;
    //ініціалізація DLL WinSock 1) wVersionRequired 2) contains information about the Windows Sockets implementation.
    if (WSAStartup(WinSockVersion, &wsaData) != 0)
    {
        cout << "Error during WINsock initializing :" << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }
    SOCKADDR_IN addr; //describes a socket for working with IP protocols.
    int portValue = 8080;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(portValue);//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian)
    addr.sin_family = AF_INET;

    int sizeoffaddr = sizeof(addr);


    // creates a socket that is bound to a specific transport-service provider.
    //1) address family 2)type specification for the new socket. 3) The protocol to be used. 3)A pointer to a WSAPROTOCOL_INFO 
    //4)g - set to zero, Windows files will not accept socket groups. 5) A set of flags
    SOCKET ServerSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (ServerSock == INVALID_SOCKET)
    {
        cout << "Error during creating Socket = " << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }
    else { cout << "Socket was created succesfully! " << endl; }


    //associates a local address with a socket. 2)A pointer to a sockaddr structure
    if (bind(ServerSock, (SOCKADDR*)&addr, sizeoffaddr) == 0)
    {
        cout << "Associating a local address with a socket successful! " << endl;
    }
    else { cout << "Associating Error :" << WSAGetLastError() << endl; exit(EXIT_FAILURE); }

    //places a socket in a state in which it is listening for an incoming connection.
    if (listen(ServerSock, 1) == 0)
    {
        cout << "Starting liestening on port: " << portValue << endl;
    }
    else { cout << "LIstening Error :" << WSAGetLastError() << endl; exit(EXIT_FAILURE); }


    // WSAAccept function conditionally accepts a connection
    //1)a socket that is listening for connections 2) pointer to an sockaddr structure that receives the address of the connecting entity
    //4)application-specified condition function 5) This parameter is only applicable if the lpfnCondition parameter is not NULL.
    SOCKET SererConnection = WSAAccept(ServerSock, (SOCKADDR*)&addr, &sizeoffaddr, NULL, 0);

    if (SererConnection == INVALID_SOCKET)
    {
        cout << "Error during accepting connection  = " << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }
    else { cout << "Client has been connected!" << endl; }


    char buffer[50] = { 0 };
    WSABUF wsaBuf;
    wsaBuf.len = sizeof(buffer);
    wsaBuf.buf = buffer;
    DWORD ReceivedData = 0, Flags = 0;
    //receives data from a connected socket 1)  connected socket 2)WSABUF structure contains a pointer to a buffer and the length
    //3) The number of WSABUF structures 4)A pointer to the number, in bytes, of data received by this call if the receive operation completes immediately
    //5)A pointer to flags 6)A pointer to a WSAOVERLAPPED structure 7) A pointer to the completion function
    WSARecv(SererConnection, &wsaBuf, 1, &ReceivedData, &Flags, NULL, NULL) == 0 ? cout << "Data has been received!" << endl :
        cout << "Error during receiving data = " << WSAGetLastError() << endl;
    param.bufferString = buffer;


    buffer[2] = { 0 };

    WSARecv(SererConnection, &wsaBuf, 1, &ReceivedData, &Flags, NULL, NULL) == 0 ? cout << "Data has been received!" << endl :
        cout << "Error during receiving data = " << WSAGetLastError() << endl;
    param.number = stoi(buffer);

    DWORD ThreadID;
    //1)A pointer to a SECURITY_ATTRIBUTES 2)The initial size of the stack, in bytes (default size for the executable)
    //3)A pointer to the application-defined function to be executed by the thread 4)A pointer to a variable to be passed to the thread.
    //5)The flags 6)A pointer to a variable that receives the thread identifier. 
    HANDLE hTreandHandle = CreateThread(NULL, 0, ThreadFun, &param, 0, &ThreadID);
    if (hTreandHandle != NULL)
    {
        WaitForSingleObject(hTreandHandle, INFINITE);
        cout << " | ID of the thread-> " << ThreadID << " |" << endl;
        CloseHandle(hTreandHandle);
    }
    
    buffer[param.foundstring.length()] = {0};
    strcpy(buffer, param.foundstring.c_str());
    wsaBuf.len = sizeof(buffer);
    wsaBuf.buf = buffer;

    //1)connected socket 2)A pointer to an array of WSABUF structures 3) The number of WSABUF structures
    //4)A pointer to the number, in bytes, sent by this call 5)The flags 6)A pointer to a WSAOVERLAPPED structure
    //7)A pointer to the completion function
    WSASend(SererConnection, &wsaBuf, 1, &wsaBuf.len, 0, NULL, NULL) == 0 ? cout << "Data has been sent!" << endl :
        cout << "Error during sending data = " << WSAGetLastError() << endl;

    //cout << param.foundstring << endl;

      //disables sends and receives on a socket.
    shutdown(SererConnection, 2);
    closesocket(SererConnection);
    //terminates use of the Winsock 2 
    WSACleanup();
}

