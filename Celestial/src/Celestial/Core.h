#pragma once

#ifdef CL_PLATFORM_WINDOWS
	#ifdef CL_BUILD_DLL
		#define CELESTIAL_API _declspec(dllexport)
	#else
		#define CELESTIAL_API _declspec(dllimport)
	#endif
#else 
	#error Celestial Only Supports Windows!
#endif

#define BIT(x) (1 << x)
