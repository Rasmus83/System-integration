#include <iostream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <winhttp.h>
#include <conio.h>
#include <codecvt>

#include "WstringToInt.h"

#pragma comment(lib, "winhttp.lib")

using namespace std::chrono_literals;

int wmain(int argc, wchar_t* argv[])
{
	HANDLE hComm = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, nullptr, 
		OPEN_EXISTING, 0, nullptr);
	
	if (hComm == INVALID_HANDLE_VALUE)
	{
		#ifdef _DEBUG
		std::cerr << "Couldn't open serial port" << std::endl;
		_getch();
		#endif
		return 1;
	}

	HINTERNET hSession = WinHttpOpen(L"TemperatureGauge", WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);
	HINTERNET hConnect = WinHttpConnect(hSession, argv[2], atoi(argv[3]), 0);

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

	auto startTime = std::chrono::steady_clock::now();
	while (true)
	{
		auto endTime = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
		if (duration >= 3s)
		{
			if (readBuffer[bytesRead - 1] == '\n')
			{
				if (readBuffer[0] != '\n')
				{
					std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

					std::wstring postData = L"/sensor/add?sensor_value=" + conv.from_bytes(readBuffer);
					HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", postData.c_str(), NULL, WINHTTP_NO_REFERER,
						WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
					BOOL results = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
					if (results)
						results = WinHttpReceiveResponse(hRequest, nullptr);
					if (results)
					{
						DWORD dwSize = 0;
						DWORD dwBytesRead = 0;
						LPVOID lpBuffer;
						do
						{
							dwSize = 0;
							if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
								break;

							lpBuffer = new char[dwSize + 1];
							ZeroMemory(lpBuffer, dwSize + 1);

							if (!WinHttpReadData(hRequest, lpBuffer, dwSize, &dwBytesRead))
								break;
							#ifdef _DEBUG
							std::cout << lpBuffer << std::endl;
							#endif
							delete[] lpBuffer;
						} while (dwSize > 0);
					}
					WinHttpCloseHandle(hRequest);
				}

				bytesRead = 1;
				readBuffer[0] = '\n';
				readBuffer[1] = '\0';
				WriteFile(hComm, "TempRequest\n", strlen("TempRequest\n"), nullptr, nullptr);
				startTime = std::chrono::steady_clock::now();
			}
			if (ReadFile(hComm, readBuffer, 99, &bytesRead, nullptr) && bytesRead > 0)
			{
				readBuffer[bytesRead] = '\0';
				#ifdef _DEBUG
				std::cout << readBuffer;
				#endif
			}
		}
	}
	CloseHandle(hComm);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);
	return 0;
}