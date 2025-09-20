#include <iostream>
#include <string>
#include <Windows.h>
#include <winhttp.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	HANDLE handle = CreateFile((WCHAR*)argv[0], GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0,
		nullptr);

	if (handle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Couldn't open serial port" << std::endl;
		_getch();

		return 1;
	}

	DCB serialParams;
	serialParams.DCBlength = sizeof(serialParams);
	GetCommState(handle, &serialParams);
	serialParams.BaudRate = CBR_9600;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	SetCommState(handle, &serialParams);

	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	SetCommTimeouts(handle, &timeouts);

	PurgeComm(handle, PURGE_RXCLEAR | PURGE_TXCLEAR);

	char buffer[100];
	char writeBuffer[] = "";
	DWORD bytesRead;
	DWORD bytesWritten;
	uint8_t bufferSize = 0;
	char key = _getch();
	while (key != '\r')
	{
		std::cout << key;
		writeBuffer[bufferSize++] = key;
		key = _getch();
	}
	std::cout << std::endl;
	writeBuffer[bufferSize] = '\n';
	writeBuffer[bufferSize + 1] = '\0';
	WriteFile(handle, &writeBuffer, strlen(writeBuffer), &bytesWritten, nullptr);
	while (true)
	{
		if (ReadFile(handle, buffer, 99, &bytesRead, nullptr) && bytesRead > 0)
		{
			buffer[bytesRead] = '\0';
			std::cout << buffer;
		}
	}
	CloseHandle(handle);
	return 0;
}