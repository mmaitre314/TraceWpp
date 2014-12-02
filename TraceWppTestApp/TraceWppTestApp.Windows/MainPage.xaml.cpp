//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

#include "TraceWpp\MainPage.xaml.cpp.tmh"

using namespace TraceWppTestApp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
    WPP_INIT_TRACING(L"TraceWppTestApp.Windows");

    Trace(L"@%p Starting", (void*)this);

    InitializeComponent();

    auto obj = ref new TraceWppTestDll::Class1();

    Trace(L"@%p Stopping", (void*)this);

    WPP_CLEANUP();
}
