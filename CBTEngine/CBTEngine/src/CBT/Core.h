#pragma once

#ifdef CBT_PLATFORM_WINDOWS
	#ifdef CBT_BUILD_DLL
		#define CBTE_API __declspec(dllexport)
	#else
		#define CBTE_API __declspec(dllimport)
	#endif // CBT_BUILD_DLL
#else
	#error CBT only support Windows
#endif

#ifdef CBT_ENABLE_ASSERTS
	#define CBT_ASSERT(x,...) { if(!(x)) {CBT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CBT_CORE_ASSERT(x,...) { if(!(x)) {CBT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CBT_ASSERT(x,...)
	#define CBT_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)