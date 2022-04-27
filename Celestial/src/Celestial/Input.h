/*****************************************************************************/
/*!
\file   Input.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the declaration of the static Input Polling system

		Functions include:

			 + IsKeyPressed

			 + IsMouseButtonPressed
			 + GetMousePosition
			 + GetMouseX
			 + GetMouseY

			 + IsKeyPressedImpl
			 + IsMouseButtonPressedImpl
			 + GetMouseXImpl
			 + GetMouseYImpl
			 + GetMousePositionImpl
*!/
/*****************************************************************************/
#pragma once
#include "Celestial/Core.h"

namespace Celestial
{
	class CELESTIAL_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }


	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0; //!< Implemented per-platform

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
	private:
		static Input* s_Instance;
	};
}