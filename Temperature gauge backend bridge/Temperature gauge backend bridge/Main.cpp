#include <conio.h>

#include "BridgeProgram.h"
#include "WstringToInt.h"

int wmain(int argc, wchar_t* argv[])
{
	BridgeProgram bridgeProgram((const wchar_t*)argv[1], (const wchar_t*)argv[2], atoi((const wchar_t*)argv[3]));
	
	if (!bridgeProgram.CommConnectionSuccess())
	{
		#ifdef _DEBUG
		std::cerr << "Couldn't open serial port" << std::endl;
		_getch();
		#endif
		return 1;
	}

	while (true)
	{
		bridgeProgram.run();
	}
	return 0;
}