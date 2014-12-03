WPP Tracing for C++ Universal Store apps
========

High-performance tracing for C++ Windows/Windows Phone Store apps

WPP: reduces app package size by storing all format strings in PDB symbol files instead of binaries
high-performance, meant to be enabled on Debug and Release build, no need for debugger attached
dynamic enabling/disabling via logman/fieldmedic

## Initial setup

Start by installing the [WPP Tracing](https://www.nuget.org/packages/MMaitre.TraceWpp/) NuGet package. The package adds a header to the VS project (TraceWpp\TraceWpp.h) and an MSBuild target to generate .tmh trace headers during the build.

Create a GUID identifying the event provider. In VS go to 'Tools > Create GUID' and select 'Copy'. This will give something like '{B5DBB673-AB73-48A3-B004-B8902FA191C3}'.

Then in the pch.h precompiled header add:

```cpp
// {B5DBB673-AB73-48A3-B004-B8902FA191C3}
#define TraceWpp_Guid (B5DBB673,AB73,48A3,B004,B8902FA191C3)

#define WPP_CONTROL_GUIDS \
    WPP_DEFINE_CONTROL_GUID(TraceWpp_CtrlGuid, TraceWpp_Guid, \
    WPP_DEFINE_BIT(TF_Default) \
    WPP_DEFINE_BIT(TF_EntryExit))

#include "TraceWpp\TraceWpp.h"
```
   
defines a set of preprocessor macros [list]

add '*.tmh' to .gitignore

in each cpp file foo.cpp, add as last include

```cpp
#include "TraceWpp\foo.cpp.tmh"   
```

When creating a Store app, add [where?] (replacing 'AppName' with some appropriate value)

```cpp
#include "TraceWpp\App.xaml.cpp.tmh"

App::App()
{
    WPP_INIT_TRACING(L"AppName");
    Trace(L"@%p Starting", (void*)this);

	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

void App::OnSuspending(Object^ /*sender*/, SuspendingEventArgs^ /*e*/)
{
    Trace(L"@%p Stopping", (void*)this);
    WPP_CLEANUP();
}
```

When creating a Windows Runtime Component DLL, add a file called module.cpp with the following content (replacing 'DllName' with some appropriate value):

```cpp
#include "TraceWpp\module.cpp.tmh"

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(instance);
        WPP_INIT_TRACING(L"DllName");
        Trace(L"@ DLL_PROCESS_ATTACH");
        break;

    case DLL_PROCESS_DETACH:
        Trace(L"@ DLL_PROCESS_DETACH");
        WPP_CLEANUP();
        break;
    }

    return TRUE;
}
```

add Advapi32.lib as import static lib in Windows Store VS projects, under 'Configuration Properties > Linker > Input > Additional Dependencies'. In Windows Phone VS projects the required static libs are already properly imported.

Disable 'Edit and Continue' used in Debug builds as this breaks WPP trace macro generation: under 'Configuration Properties > C/C++ > General > Debug Information Format' replace 'Program Database for Edit And Continue (/ZI)' by 'Program Database (/Zi)'.

## Adding traces

similar to printf():

```cpp
Trace(L"@%p Starting", this);
```

If the object traced is a C++/CX one, the $this$ pointer needs to be cast to $void*$.

## Recording traces

### Windows

run elevated:

```
logman.exe create trace mytrace -p {B5DBB673-AB73-48A3-B004-B8902FA191C3} 0xff 5 -ets -o trace.etl
```

where {B5DBB673-AB73-48A3-B004-B8902FA191C3} needs to be replaced by the GUID of the event provider. The '-pf' option allows passing a list of providers stored in a config file with one set of 'GUID flags level' per line.

```
logman.exe stop mytrace -ets
```

logman.exe is located under %windir%\system32 and typically already in the path.

### Windows Phone

Field Medic [blog]({{ site.url }}/2014/12/01/field-medic-custom-logging.html)
[profile]

## Formatting traces

Once recorded, traces need to be formatted to convert binary trace files (.etl) to text files (.log). The process is the same whether traces were recorded on Windows or Windows Phone.

Extract .tmf trace format files from .pdb symbol files:

```
tracepdb.exe -f *.pdb -p c:\Symbols\TraceFormat
```

Format .etl binary traces into text traces:

```
set TRACE_FORMAT_SEARCH_PATH=c:\Symbols\TraceFormat
set TRACE_FORMAT_PREFIX=[%9!d!]%8!04X!.%3!04X! %4!s! %!FUNC!
tracefmt.exe -f trace.etl -o trace.log
```

The tools are available in the Windows SDK, under '%ProgramFiles%\Windows Kits\8.1\bin\x86' on 32b machines and '%ProgramFiles(x86)%\Windows Kits\8.1\bin\x64' on 64b machines.

TRACE_FORMAT_PREFIX can be customized using the format specifiers documented [here](http://msdn.microsoft.com/en-us/library/windows/hardware/ff553941(v=vs.85).aspx). The format used above is '[CpuNumber]ProcessID.ThreadID Time FunctionName'.

## Analysing traces

[TextAnalysisTool.NET](http://dlaa.me/blog/post/3450647) , [MF](http://blogs.msdn.com/b/mf/archive/2010/09/09/analyzing-media-foundation-traces.aspx)
