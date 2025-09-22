#include <iostream>
#include <string>
#include <Windows.h>
#include <winhttp.h>
#include <conio.h>

#pragma comment(lib, "winhttp.lib")

int wmain(int argc, wchar_t* argv[])
{
	HANDLE hComm = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0,
		nullptr);

	if (hComm == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Couldn't open serial port" << std::endl;
		_getch();

		return 1;
	}

	DCB serialParams;
	serialParams.DCBlength = sizeof(serialParams);
	GetCommState(hComm, &serialParams);
	serialParams.BaudRate = CBR_9600;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	SetCommState(hComm, &serialParams);

	char readBuffer[100] = "\n";
	DWORD bytesRead = 1;
	DWORD bytesWritten;
	uint8_t bufferSize = 0;
	char key = '\0';
	
	while (true)
	{
		if (readBuffer[bytesRead - 1] == '\n')
		{
			bytesRead = 1;
			readBuffer[0] = '\n';
			readBuffer[1] = '\0';
			key = '\0';
			std::cout << "Press enter to request temperature value" << std::endl;
			while (key != '\r')
				key = _getch();
			WriteFile(hComm, "TempReq\n", strlen("TempReq\n"), nullptr, nullptr);
		}
		if (ReadFile(hComm, readBuffer, 99, &bytesRead, nullptr) && bytesRead > 0)
		{
			readBuffer[bytesRead] = '\0';
			std::cout << readBuffer;
		}
	}
	CloseHandle(hComm);
	return 0;
}