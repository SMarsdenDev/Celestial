/*****************************************************************************/
/*!
\file   Application.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the declaration of the Celestial Application base class.

		Functions include:

			 + Application
			 + ~Application
			 + Run
			 + OnEvent
			 + OnWindowClose
			 + CreateApplication
*!/
/*****************************************************************************/
#pragma once
#include "Core.h"
#include "Window.h"

#include "Celestial/Events/ApplicationEvent.h"

namespace Celestial
{
	class CELESTIAL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// Will be defined in the client
	Application* CreateApplication();
}