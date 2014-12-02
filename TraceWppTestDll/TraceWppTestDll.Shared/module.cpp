#include "pch.h"
#include "TraceWpp\module.cpp.tmh"

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID lpvReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(instance);
        WPP_INIT_TRACING(L"TraceWppTestDll");
        Trace(L"@ DLL_PROCESS_ATTACH");
        break;

    case DLL_PROCESS_DETACH:
        Trace(L"@ DLL_PROCESS_DETACH");
        WPP_CLEANUP();
        break;
    }

    return TRUE;
}

