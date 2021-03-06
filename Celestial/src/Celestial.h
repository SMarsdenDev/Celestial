/*****************************************************************************/
/*!
\file   Celestial.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the client-facing includes necessary to run the 
		Celestial Engine.

		The goal is to have this file be the only file included in the 
		client application
*!/
/*****************************************************************************/
#pragma once

// For use by Celestial applications
#include "src/Celestial/Application.h"
#include "src/Celestial/Log.h"
#include "Celestial/Layer.h"

#include "Celestial/CLKeycodes.h"
#include "Celestial/MouseButtonCodes.h"
#include "Celestial/Input.h"

#include "Celestial/ImGUI/ImGUILayer.h"

//! Entry Point *********************
#include "src/Celestial/EntryPoint.h"
//! *********************************
