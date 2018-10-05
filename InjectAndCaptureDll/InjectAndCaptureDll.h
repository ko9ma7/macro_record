#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the INJECTANDCAPTUREDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// INJECTANDCAPTUREDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef INJECTANDCAPTUREDLL_EXPORTS
#define INJECTANDCAPTUREDLL_API __declspec(dllexport)
#else
#define INJECTANDCAPTUREDLL_API __declspec(dllimport)
#endif

#include "Common/Event.h"
#include <memory>
#include <Windows.h>
#include <vector>

namespace iac_dll {
	INJECTANDCAPTUREDLL_API void HandleMouseEventCapture(RAWMOUSE data);
} //TODO: exporting for tests - and I don't like it - isn't there other way?

namespace iac_dll {
	using error_callback_t = void(*)(const std::string& error);
	INJECTANDCAPTUREDLL_API void init_with_error_cb(error_callback_t);
	INJECTANDCAPTUREDLL_API void Init();

	typedef void(*capture_events_callback_t)(std::unique_ptr<Event>);
	INJECTANDCAPTUREDLL_API BOOL StartCapture(capture_events_callback_t);
	INJECTANDCAPTUREDLL_API BOOL StopCapture();
	//TODO: need to add "InjectEvent" export?
	INJECTANDCAPTUREDLL_API std::ostream &operator<<(std::ostream &outstream, Event const &event);
	INJECTANDCAPTUREDLL_API std::unique_ptr<Event> deserialize_event(std::vector<unsigned char>);
	INJECTANDCAPTUREDLL_API std::vector<std::unique_ptr<Event>> deserialize_events(std::vector<unsigned char>);
}

extern "C" {
	using iac_dll_error_callback_t = void(*)(const char* error);
	INJECTANDCAPTUREDLL_API void iac_dll_init_with_error_cb(iac_dll_error_callback_t);
	INJECTANDCAPTUREDLL_API void iac_dll_init();
	
	typedef void(*iac_dll_capture_event_cb)(const unsigned char buffer[], int buf_size);
	INJECTANDCAPTUREDLL_API void iac_dll_start_capture(iac_dll_capture_event_cb cb);
	INJECTANDCAPTUREDLL_API void iac_dll_stop_capture();
	INJECTANDCAPTUREDLL_API void iac_dll_inject_event(const unsigned char serialized_event_buf[], size_t buf_size);
	INJECTANDCAPTUREDLL_API void iac_dll_inject_events(const unsigned char serialized_event_buf[], size_t buf_size);
}