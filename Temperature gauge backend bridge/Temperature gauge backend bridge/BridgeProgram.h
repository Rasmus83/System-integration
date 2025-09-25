#pragma once

#ifdef _DEBUG
#include <iostream>
#endif
#include <chrono>
#include <Windows.h>
#include <winhttp.h>
#include <stdint.h>

#pragma comment(lib, "winhttp.lib")

class BridgeProgram
{
private:
	HANDLE hComm;
	HINTERNET hSession;
	HINTERNET hConnect;
	HINTERNET hRequest;
	DCB serialParams;
	COMMTIMEOUTS timeouts;
	char readBuffer[100];
	DWORD bytesRead;
	DWORD bytesWritten;
	uint8_t bufferSize;
	std::chrono::steady_clock::time_point startTime;
public:
	BridgeProgram(const wchar_t* comPort, const wchar_t* serverName, int serverPort);
	~BridgeProgram();

	bool CommConnectionSuccess();
	void run();
};