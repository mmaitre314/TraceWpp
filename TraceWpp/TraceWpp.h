#pragma once

// #define TRACE_LEVEL_NONE        0   // Tracing is not on
// #define TRACE_LEVEL_CRITICAL    1   // Abnormal exit or termination
// #define TRACE_LEVEL_FATAL       1   // Deprecated name for Abnormal exit or termination
// #define TRACE_LEVEL_ERROR       2   // Severe errors that need logging
// #define TRACE_LEVEL_WARNING     3   // Warnings such as allocation failure
// #define TRACE_LEVEL_INFORMATION 4   // Non-error useful information
// #define TRACE_LEVEL_VERBOSE     5   // Detailed traces from intermediate steps and function entry-exit

#define TRACE_IS_ENABLED(LEVEL, FLAGS) (WPP_LEVEL_ENABLED(FLAGS) && WPP_CONTROL(WPP_BIT_ ## FLAGS).Level >= LEVEL)

// Note: The use of MYPARAM, MYPARAM2, etc. below is to avoid name collisions for WPP_*_LOGGER macros

// MACRO: TraceScope (flags: TF_EntryExit, level: TRACE_LEVEL_VERBOSE)
//
// begin_wpp config
// USEPREFIX(TraceScope, "%!STDPREFIX!");
// FUNC TraceScope(OBJECT);
// USESUFFIX(TraceScope, "@%p exit", (_po));
// end_wpp

#define WPP_OBJECT_PRE(OBJECT) \
class TT \
    { \
    public: \
    TT(const void* po) \
    : _po(po) \
        { \
        } \
        __forceinline ~TT() \
        {
#define WPP_OBJECT_POST(OBJECT) \
    ; \
        } \
        const void *_po; \
    } _tt(OBJECT);

#define WPP_OBJECT_LOGGER(OBJECT) WPP_LEVEL_LOGGER(TF_EntryExit)
#define WPP_OBJECT_ENABLED(OBJECT) TRACE_IS_ENABLED(TRACE_LEVEL_VERBOSE, TF_EntryExit)

// MACRO: TraceScopeCx (flags: TF_EntryExit, level: TRACE_LEVEL_VERBOSE)
//
// begin_wpp config
// USEPREFIX(TraceScopeCx, "%!STDPREFIX!");
// FUNC TraceScopeCx{MYPARAM3=FOO}(OBJECT);
// USESUFFIX(TraceScopeCx, "@%p exit", (const void*)(_po));
// end_wpp

#define WPP_MYPARAM3_OBJECT_PRE(MYPARAM3, OBJECT) \
class TT \
    { \
    public: \
    TT(Platform::Object^ po) \
    : _po(po) \
        { \
        } \
        __forceinline ~TT() \
        {
#define WPP_MYPARAM3_OBJECT_POST(MYPARAM3, OBJECT) \
    ; \
        } \
        Platform::Object^ _po; \
    } _tt(OBJECT);

#define WPP_MYPARAM3_OBJECT_LOGGER(MYPARAM3, OBJECT) WPP_LEVEL_LOGGER(TF_EntryExit)
#define WPP_MYPARAM3_OBJECT_ENABLED(MYPARAM3, OBJECT) TRACE_IS_ENABLED(TRACE_LEVEL_VERBOSE, TF_EntryExit)

// MACRO: TraceScopeHr (flags: TF_EntryExit, level: TRACE_LEVEL_VERBOSE)
//
// begin_wpp config
// USEPREFIX(TraceScopeHr, "%!STDPREFIX!");
// FUNC TraceScopeHr(OBJECT, HR);
// USESUFFIX(TraceScopeHr, "@%p exit%s%!HRESULT!", (_po), ((_ph == nullptr) || SUCCEEDED(*_ph) ? " " : " failed "), (_ph == nullptr ? S_OK : *_ph));
// end_wpp

#define WPP_OBJECT_HR_PRE(OBJECT, HR) \
class TT \
    { \
    public: \
    TT(const void* po, const HRESULT* ph) \
    : _po(po) \
    , _ph(ph) \
        { \
        } \
        __forceinline ~TT() \
        {
#define WPP_OBJECT_HR_POST(OBJECT, HR) \
    ; \
        } \
        const void *_po; \
        const HRESULT *_ph; \
    } _tt(OBJECT, HR);

#define WPP_OBJECT_HR_LOGGER(OBJECT, HR) WPP_LEVEL_LOGGER(TF_EntryExit)
#define WPP_OBJECT_HR_ENABLED(OBJECT, HR) TRACE_IS_ENABLED(TRACE_LEVEL_VERBOSE, TF_EntryExit)

// MACRO: Trace (flags: TF_Default, level: TRACE_LEVEL_INFORMATION)
//
// begin_wpp config
// USEPREFIX(Trace,"%!STDPREFIX!");
// FUNC Trace{MYPARAM2=FOO}(MSG, ...);
// end_wpp
//

#define WPP_MYPARAM2_LOGGER(MYPARAM2) WPP_LEVEL_LOGGER(TF_Default)
#define WPP_MYPARAM2_ENABLED(MYPARAM2) TRACE_IS_ENABLED(TRACE_LEVEL_INFORMATION, TF_Default)

// MACRO: TraceFlag (level: TRACE_LEVEL_INFORMATION)
//
// begin_wpp config
// USEPREFIX(TraceFlag,"%!STDPREFIX!");
// FUNC TraceFlag(FLAGS, MSG, ...);
// end_wpp
//

#define WPP_FLAGS_LOGGER(FLAGS) WPP_LEVEL_LOGGER(FLAGS)
#define WPP_FLAGS_ENABLED(FLAGS) TRACE_IS_ENABLED(TRACE_LEVEL_INFORMATION, FLAGS)

// MACRO: TraceLevel
//
// begin_wpp config
// USEPREFIX(TraceLevel,"%!STDPREFIX!");
// FUNC TraceLevel(LEVEL, FLAGS, MSG, ...);
// end_wpp
//

#define WPP_LEVEL_FLAGS_LOGGER(LEVEL, FLAGS) WPP_LEVEL_LOGGER(FLAGS)
#define WPP_LEVEL_FLAGS_ENABLED(LEVEL, FLAGS) TRACE_IS_ENABLED(LEVEL, FLAGS)

// MACRO: TraceHr
//
// begin_wpp config
// USEPREFIX(TraceHr,"%!STDPREFIX!(hr=%!HRESULT!)", HR);
// FUNC TraceHr(FLAGS, HR, MSG, ...);
// end_wpp
//

#define WPP_FLAGS_HR_LOGGER(FLAGS, HR) WPP_LEVEL_LOGGER(FLAGS)
#define WPP_FLAGS_HR_ENABLED(FLAGS, HR) (WPP_LEVEL_ENABLED(FLAGS) && WPP_CONTROL(WPP_BIT_ ## FLAGS).Level >= (SUCCEEDED(HR) ? TRACE_LEVEL_VERBOSE : TRACE_LEVEL_ERROR))

// Workaround for a missing declaration in the Windows Phone 8.1 version of evntrace.h
#define WPP_REGISTER_TRACE_GUIDS  RegisterTraceGuidsW
