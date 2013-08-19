#include "stdafx.h"
#include <Windows.h>

struct res {
	int x, y, bpp;
};

void changeResolution(int x, int y, int bpp) {
	DEVMODE devmode;
	devmode.dmSize = sizeof(devmode);
	devmode.dmPelsWidth = x;
	devmode.dmPelsHeight = y;
	devmode.dmBitsPerPel = bpp;
	devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	auto result  = ChangeDisplaySettings(&devmode, 0);
}

res getCurrentResolution() {
	auto hDC = CreateDC(L"DISPLAY", L"", L"", 0);

	auto bpp = GetDeviceCaps(hDC, 12);
	auto x = GetDeviceCaps(hDC, 8);
	auto y = GetDeviceCaps(hDC, 10);

	res r = {x, y, bpp};
	return r;
}

res getRequestedResolution() {
	//TODO: Read from config
	res r = {1920, 1080, 32};
	return r;
}

int _tmain(int argc, _TCHAR* argv[])
{
	auto current = getCurrentResolution();
	auto requested = getRequestedResolution();

	if(current.x != requested.x ||
		current.y != requested.y ||
		current.bpp != requested.bpp) {
		changeResolution(requested.x, requested.y, requested.bpp);
	}

	return 0;
}

