/*****************************************************************************/
/*!
\file   clpch.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the headers part of external libraries, or finalized
		Celestial libraries, to be precompiled
*!/
/*****************************************************************************/
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "Celestial/Log.h"

#ifdef CL_PLATFORM_WINDOWS
	#include <Windows.h>
#endif