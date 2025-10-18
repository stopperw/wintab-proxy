/* Wintab-Interposer
 *
 * Copyright © 2021, John Chadwick <john@jchw.io>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "wintab32.h"

static HMODULE hDLL = nullptr;
static FILE *fLogFile = stderr;

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, void *reserved)
{
	if (reason == DLL_PROCESS_ATTACH) {
		if (auto szLogFilename = getenv("WINTAB_LOG"); szLogFilename != nullptr) {
			fLogFile = fopen(szLogFilename, "a");
		}
	}

    fprintf(fLogFile, "[WTP] wintab32.DllMain(%p, %lu, %p)\n", instance, reason, reserved);

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            hDLL = LoadLibraryExA("wintab32", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
			if (hDLL == nullptr || hDLL == instance) {
	            hDLL = LoadLibraryA("wintab32_real");
			}
			if (hDLL == nullptr) {
				fprintf(fLogFile, "[WTP] wintab32.DllMain: Couldn't find real wintab32.\n");
				abort();
			}
            fprintf(fLogFile, "[WTP] wintab32.DllMain: Forwarding DLL (wintab32) loaded (%p)\n", hDLL);
            DisableThreadLibraryCalls(instance);
            break;
        case DLL_PROCESS_DETACH:
            FreeLibrary(hDLL);
            fprintf(fLogFile, "[WTP] wintab32.DllMain: Forwarding DLL (wintab32) freed\n");
            break;
    }

    return TRUE;
}


extern "C" UINT __stdcall WINTAB32_WTInfoA(UINT arg0, UINT arg1, LPVOID arg2)
{
	UINT (__stdcall *pFunc)(UINT, UINT, LPVOID);
	UINT retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTInfoA"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTOpenA(HWND arg0, LPLOGCONTEXTA arg1, BOOL arg2)
{
	HCTX (__stdcall *pFunc)(HWND, LPLOGCONTEXTA, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTOpenA"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTClose(HCTX arg0)
{
	BOOL (__stdcall *pFunc)(HCTX);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTClose"));
	retVal = pFunc(arg0);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTPacketsGet(HCTX arg0, int arg1, LPVOID arg2)
{
	int (__stdcall *pFunc)(HCTX, int, LPVOID);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTPacketsGet"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTPacket(HCTX arg0, UINT arg1, LPVOID arg2)
{
	BOOL (__stdcall *pFunc)(HCTX, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTPacket"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTEnable(HCTX arg0, BOOL arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, BOOL);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTEnable"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTOverlap(HCTX arg0, BOOL arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, BOOL);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTOverlap"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTConfig(HCTX arg0, HWND arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, HWND);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTConfig"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTGetA(HCTX arg0, LPLOGCONTEXTA arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPLOGCONTEXTA);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTGetA"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTSetA(HCTX arg0, LPLOGCONTEXTA arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPLOGCONTEXTA);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTSetA"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTExtGet(HCTX arg0, UINT arg1, LPVOID arg2)
{
	BOOL (__stdcall *pFunc)(HCTX, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTExtGet"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTExtSet(HCTX arg0, UINT arg1, LPVOID arg2)
{
	BOOL (__stdcall *pFunc)(HCTX, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTExtSet"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTSave(HCTX arg0, LPVOID arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTSave"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTRestore(HWND arg0, LPVOID arg1, BOOL arg2)
{
	HCTX (__stdcall *pFunc)(HWND, LPVOID, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTRestore"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTPacketsPeek(HCTX arg0, int arg1, LPVOID arg2)
{
	int (__stdcall *pFunc)(HCTX, int, LPVOID);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTPacketsPeek"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTDataGet(HCTX arg0, UINT arg1, UINT arg2, int arg3, LPVOID arg4, LPINT arg5)
{
	int (__stdcall *pFunc)(HCTX, UINT, UINT, int, LPVOID, LPINT);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTDataGet"));
	retVal = pFunc(arg0,arg1,arg2,arg3,arg4,arg5);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTDataPeek(HCTX arg0, UINT arg1, UINT arg2, int arg3, LPVOID arg4, LPINT arg5)
{
	int (__stdcall *pFunc)(HCTX, UINT, UINT, int, LPVOID, LPINT);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTDataPeek"));
	retVal = pFunc(arg0,arg1,arg2,arg3,arg4,arg5);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTQueueSizeGet(HCTX arg0)
{
	int (__stdcall *pFunc)(HCTX);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTQueueSizeGet"));
	retVal = pFunc(arg0);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTQueueSizeSet(HCTX arg0, int arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, int);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTQueueSizeSet"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" HMGR __stdcall WINTAB32_WTMgrOpen(HWND arg0, UINT arg1)
{
	HMGR (__stdcall *pFunc)(HWND, UINT);
	HMGR retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrOpen"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrClose(HMGR arg0)
{
	BOOL (__stdcall *pFunc)(HMGR);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrClose"));
	retVal = pFunc(arg0);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrContextEnum(HMGR arg0, WTENUMPROC arg1, LPARAM arg2)
{
	BOOL (__stdcall *pFunc)(HMGR, WTENUMPROC, LPARAM);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrContextEnum"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" HWND __stdcall WINTAB32_WTMgrContextOwner(HMGR arg0, HCTX arg1)
{
	HWND (__stdcall *pFunc)(HMGR, HCTX);
	HWND retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrContextOwner"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTMgrDefContext(HMGR arg0, BOOL arg1)
{
	HCTX (__stdcall *pFunc)(HMGR, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrDefContext"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" UINT __stdcall WINTAB32_WTMgrDeviceConfig(HMGR arg0, UINT arg1, HWND arg2)
{
	UINT (__stdcall *pFunc)(HMGR, UINT, HWND);
	UINT retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrDeviceConfig"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrExt(HMGR arg0, UINT arg1, LPVOID arg2)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrExt"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrEnable(HMGR arg0, UINT arg1, BOOL arg2)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, BOOL);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrEnable"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrButtonMap(HMGR arg0, UINT arg1, LPBYTE arg2, LPBYTE arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, LPBYTE, LPBYTE);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrButtonMap"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureBtnMarks(HMGR arg0, UINT arg1, DWORD arg2, DWORD arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, DWORD, DWORD);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrPressureBtnMarks"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureResponse(HMGR arg0, UINT arg1, UINT * arg2, UINT * arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, UINT *, UINT *);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrPressureResponse"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrExt(HMGR arg0, UINT arg1, UINT arg2, LPVOID arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrExt"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTQueuePacketsEx(HCTX arg0, UINT * arg1, UINT * arg2)
{
	BOOL (__stdcall *pFunc)(HCTX, UINT *, UINT *);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTQueuePacketsEx"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureBtnMarksEx(HMGR arg0, UINT arg1, UINT * arg2, UINT * arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, UINT *, UINT *);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrPressureBtnMarksEx"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrConfigReplaceExA(HMGR arg0, BOOL arg1, LPSTR arg2, LPSTR arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, BOOL, LPSTR, LPSTR);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrConfigReplaceExA"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" HWTHOOK __stdcall WINTAB32_WTMgrPacketHookExA(HMGR arg0, int arg1, LPSTR arg2, LPSTR arg3)
{
	HWTHOOK (__stdcall *pFunc)(HMGR, int, LPSTR, LPSTR);
	HWTHOOK retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrPacketHookExA"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrPacketUnhook(HWTHOOK arg0)
{
	BOOL (__stdcall *pFunc)(HWTHOOK);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrPacketUnhook"));
	retVal = pFunc(arg0);
	return retVal;
}


extern "C" LRESULT __stdcall WINTAB32_WTMgrPacketHookNext(HWTHOOK arg0, int arg1, WPARAM arg2, LPARAM arg3)
{
	LRESULT (__stdcall *pFunc)(HWTHOOK, int, WPARAM, LPARAM);
	LRESULT retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrPacketHookNext"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTMgrDefContextEx(HMGR arg0, UINT arg1, BOOL arg2)
{
	HCTX (__stdcall *pFunc)(HMGR, UINT, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrDefContextEx"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" UINT __stdcall WINTAB32_WTInfoW(UINT arg0, UINT arg1, LPVOID arg2)
{
	UINT (__stdcall *pFunc)(UINT, UINT, LPVOID);
	UINT retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTInfoW"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTOpenW(HWND arg0, LPLOGCONTEXTW arg1, BOOL arg2)
{
	HCTX (__stdcall *pFunc)(HWND, LPLOGCONTEXTW, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTOpenW"));
	retVal = pFunc(arg0,arg1,arg2);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTGetW(HCTX arg0, LPLOGCONTEXTW arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPLOGCONTEXTW);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTGetW"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTSetW(HCTX arg0, LPLOGCONTEXTW arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPLOGCONTEXTW);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTSetW"));
	retVal = pFunc(arg0,arg1);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrConfigReplaceExW(HMGR arg0, BOOL arg1, LPWSTR arg2, LPSTR arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, BOOL, LPWSTR, LPSTR);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrConfigReplaceExW"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}


extern "C" HWTHOOK __stdcall WINTAB32_WTMgrPacketHookExW(HMGR arg0, int arg1, LPWSTR arg2, LPSTR arg3)
{
	HWTHOOK (__stdcall *pFunc)(HMGR, int, LPWSTR, LPSTR);
	HWTHOOK retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrPacketHookExW"));
	retVal = pFunc(arg0,arg1,arg2,arg3);
	return retVal;
}
