#include <stdlib.h>
#include <intrin.h>
#include <windows.h>
#include <iostream>


BOOL isHyperVisor(VOID)
{
	int CPUinfo[4] = { -1 };
	__cpuid(CPUinfo, 1);
	if ((CPUinfo[2] >> 31) & 1)
	{
		return 1;
	}
	return 0;
}

int main()
{
	if (isHyperVisor())
	{
		MessageBox(NULL, L"Hello kitty!", L"Programm", MB_ICONASTERISK);
	}
}

