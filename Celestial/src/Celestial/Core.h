/*****************************************************************************/
/*!
\file   Core.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains preprocessor defines necessarily by core features of 
		the Celestial Engine
*!/
/*****************************************************************************/
#pragma once

#ifdef CL_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
	#ifdef CL_BUILD_DLL
		#define CELESTIAL_API _declspec(dllexport)
	#else
		#define CELESTIAL_API _declspec(dllimport)
	#endif
#else
	#define CELESTIAL_API
#endif
#else 
	#error Celestial Only Supports Windows!
#endif

#define BIT(x) (1 << x)

#ifdef CL_ENABLE_ASSERTS
	#define CL_ASSERT(x, ...) { if(!(x)) { CL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CL_CORE_ASSERT(x, ...) { if(!(x)) { CL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CL_ASSERT(x, ...)
	#define CL_CORE_ASSERT(c, ...)
#endif

#define CL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)