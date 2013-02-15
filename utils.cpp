/*
 * utils.cpp
 *
 * SSG PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#include "utils.h"

#include <cstdio>

#include <XPLMUtilities.h>

namespace SSG_PLUGIN {
//================================================================================================//
/*
UTILS
*/
#if APL && __MACH__
#include <Carbon/Carbon.h>
int ConvertPath(const char * inPath, char * outPath, int outPathMaxLen)
{
	CFStringRef inStr = CFStringCreateWithCString(kCFAllocatorDefault, inPath ,kCFStringEncodingMacRoman);
	if (inStr == NULL)
		return -1;
	CFURLRef url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, inStr, kCFURLHFSPathStyle,0);
	CFStringRef outStr = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
	if (!CFStringGetCString(outStr, outPath, outPathMaxLen, kCFURLPOSIXPathStyle))
		return -1;
	CFRelease(outStr);
	CFRelease(url);
	CFRelease(inStr);
	return 0;
}
#endif


#if DEBUGMODE
void debug(const char *message)
{
	XPLMDebugString(PLUGIN_NAME
					"[DEBUG MESSAGE]:\n");
	XPLMDebugString(message);
	XPLMDebugString("\n");
}

void debug(const char* message, int value)
{
	debug(message);
	char buffer[20];
	::sprintf(buffer, "<%d>", value);
	debug(buffer);
}

#endif

} // namespace SSG_PLUGIN


#if IBM
#include <windows.h>

BOOL APIENTRY DllMain( HANDLE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
#endif


