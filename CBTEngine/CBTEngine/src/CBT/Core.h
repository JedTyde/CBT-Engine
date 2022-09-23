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

#define BIT(x) (1 << x)