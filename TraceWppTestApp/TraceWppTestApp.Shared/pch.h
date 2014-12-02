//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <collection.h>
#include <ppltasks.h>

// {B5DBB673-AB73-48A3-B004-B8902FA191C3}
#define TraceWpp_Guid (B5DBB673,AB73,48A3,B004,B8902FA191C3)

#define WPP_CONTROL_GUIDS \
        WPP_DEFINE_CONTROL_GUID(TraceWpp_CtrlGuid, TraceWpp_Guid, \
        WPP_DEFINE_BIT(TF_Default) \
        WPP_DEFINE_BIT(TF_EntryExit))

#include "TraceWpp\TraceWpp.h"

#include "App.xaml.h"
