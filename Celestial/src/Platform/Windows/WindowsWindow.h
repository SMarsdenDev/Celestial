/*****************************************************************************/
/*!
\file   WindowsWindow.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the class declaration for the Windows-specific window

		Functions include:

			 + GLFWErrorCallback

			 + WindowsWindow
			 + ~WindowsWindow
			 + Init
			 + Shutdown
			 + OnUpdate
			 + SetVSync
			 + IsVSync
*!/
/*****************************************************************************/
#pragma once

#include "Celestial/Window.h"
#include "GLFW/glfw3.h"

namespace Celestial
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}