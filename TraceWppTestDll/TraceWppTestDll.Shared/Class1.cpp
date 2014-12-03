#include "pch.h"
#include "Class1.h"

#include "TraceWpp\Class1.cpp.tmh"

using namespace TraceWppTestDll;
using namespace Platform;

Class1::Class1()
{
    Trace(L"@%p", (void*)this);
}
