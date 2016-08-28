#include <Windows.h>
#include <ImageHlp.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ImageHlp.lib")

bool Flag(LPCSTR path, bool ASLR, bool DEP)
{
	LOADED_IMAGE PE;
	if (MapAndLoad(path, 0, &PE, 0, 0))
	{
		if (ASLR) // Enable address space layout randomization
			PE.FileHeader->OptionalHeader.DllCharacteristics = IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;
		else // Disable address space layout randomization
			PE.FileHeader->OptionalHeader.DllCharacteristics = NULL;

		if (DEP) // Enable data execution prevention
			PE.FileHeader->OptionalHeader.DllCharacteristics = IMAGE_DLLCHARACTERISTICS_NX_COMPAT;
		else // Disable data execution prevention
			PE.FileHeader->OptionalHeader.DllCharacteristics = NULL;
		UnMapAndLoad(&PE);
		return true;
	}
	return false;
}

int main()
{
	Flag("test.exe", false, false);
}