/*****************************************************************************/
/*!
\file   Window.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the declaration for the abstract Window class, which
		will store window data and event callback

		Functions include:

			 + WindowProps

			 + ~Window
			 + OnUpdate
			 + GetWidth
			 + GetHeight
			 + SetEventCallback
			 + SetVSync
			 + IsVSync
			 + Create
*!/
/*****************************************************************************/
#pragma once
#include "clpch.h"

#include "Celestial/Core.h"
#include "Celestial/Events/Event.h"

namespace Celestial
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		/*****************************************************************************/
		/*!
			\brief
				Conversion Constructor

			\param title
				The title to set the window to

			\param width
				An width of the window

			\param height
				An width of the height
		*/
		/*****************************************************************************/
		WindowProps(const std::string& title = "Celestial Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class CELESTIAL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}