#include "libxl.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <string> 

using namespace libxl;
using namespace std;

vector<int> SelectNumbers(string str)
{
    vector <int> validatedVector;
    string filStr = "";
    for (int i = 0; i < str.size(); i++)
    {
        while (str[i] >= 0x30 and str[i] <= 0x39)
        {
            filStr = filStr + str[i];
            i++;
        }
        if (filStr != "")
        {
            validatedVector.push_back(atoi(filStr.c_str()));
            filStr = "";
        }
    }
    cout << "Your numbers: ";
    for (int i = 0; i < validatedVector.size(); i++)
    {
        cout << validatedVector[i] << ' ';
    }
    cout << endl;
    return validatedVector;
}


int** CreateMatrix(vector<int>vec, int m, int n)
{
    cout << endl;
    int** Matr = new int* [m];

    for (int i = 0; i < m; i++)
    {
        Matr[i] = new int[n];
    }
    int y = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Matr[i][j] = vec[y];
            y++;
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << Matr[i][j] << "\t";
        }
        cout << endl;
    }
    return Matr;
}


void ClearArray(int** arr, int m)
{
    for (int i = 0; i < m; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

int main()
{
    string filename;
    cout << "Enter your filename: ";
    cin >> filename;
    HANDLE hFile1 = CreateFileA(filename.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, 0);
    if (hFile1 == INVALID_HANDLE_VALUE)
    {
        cout << "Error during opening file, please try again!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "File " << filename << " was been opened!" << endl;
    }

    char buff[1000] = { 0 };
    DWORD NumRead;
    if (BOOL RFile = ReadFile(hFile1, buff, sizeof(buff), &NumRead, NULL))
    {
        cout << "Data was succesfully read!" << endl;
    }
    else { cout << "Error ooccured!" << endl; exit(EXIT_FAILURE); }

    vector<int>numbersFromFile = SelectNumbers(buff);

    int M, N;
    while (true)
    {
        cout << "Enter your M (rows):  " << endl;
        cin >> M;
        cout << "Enter your N (columns):  " << endl;
        cin >> N;
        if (numbersFromFile.size() >= (M * N))
        {
            break;
        }
        cout << "M and N not suitable! Please try again!" << endl;
    }

    int** Matrix = CreateMatrix(numbersFromFile, M, N);

    int numberOfRow;
    Book* book = xlCreateBook(); //Create a binary book instance for xls format.
    if (book)
    {
        Sheet* sheet = book->addSheet(L"Sheet");//Adds a new sheet to this book, returns the sheet pointer. 
        if (sheet)
        {
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    sheet->writeNum(i + 1, j, Matrix[i][j]);//Writes a number or date/time into the cell with the specified format.
                }
            }
        }

        while (true)
        {
            cout << "Enter number of row to replace with 0: ";
            cin >> numberOfRow;
            if (numberOfRow <= sheet->lastRow() - 1)//Returns the zero-based index of the row
            {
                for (int j = 0; j < N; j++)
                {
                    sheet->writeNum(numberOfRow, j, 0);
                }
                cout << "Row " << numberOfRow << " has been replaced with 0!" << endl;
                break;
            }
            cout << "There is no " << numberOfRow << " row in your mass int the file! Please try again!" << endl;
        }

        for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
        {
            for (int col = sheet->firstCol(); col < sheet->lastCol(); ++col)
            {
                Matrix[row - 1][col] = wcstol(sheet->readStr(row, col), 0, 10);//Reads a string and its format from the cell. 
                                                                               //Convert strings to a long integer value.
            }
        }

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << Matrix[i][j] << "\t";
            }
            cout << endl;
        }
        book->save(L"report.xls");//Saves current workbook into the file.
        book->release();//Deletes this object and free resources.
        cout << "Microsoft Excel report was succesfully generated!" << endl;
    }

    HANDLE hFile2 = CreateFileA("report.doc", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, 0);
    if (hFile2 == INVALID_HANDLE_VALUE)
    {
        cout << "Error during opening file, please try again!" << endl;
    }

    string Buffer = "\t\t\t\t\tThis is my report!\n\nBy Snigur Anton FB-91\n\n\nDuring executing this program the " + to_string(numberOfRow)
        + string(" row of array was replaced with 0 and my final result is:\n\n");
    DWORD NumBuffer = strlen(Buffer.c_str());
    DWORD NumBytesWritten = 0;
    BOOL WFile = WriteFile(hFile2, Buffer.c_str(), NumBuffer, &NumBytesWritten, NULL);

    string data;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            data = to_string(Matrix[i][j]) + ("\t");
            WriteFile(hFile2, data.c_str(), data.length(), &NumBytesWritten, NULL);
        }
        data = "\n";
        WriteFile(hFile2, data.c_str(), data.length(), &NumBytesWritten, NULL);
    }

    cout << "Microsoft Word report was succesfully generated!" << endl;
    ClearArray(Matrix, M);
    CloseHandle(hFile1);
    CloseHandle(hFile2);
    return 0;
}