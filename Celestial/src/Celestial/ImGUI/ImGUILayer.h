/*****************************************************************************/
/*!
\file   ImGUILayer.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/26/2022
\brief
		This file contains the declaration for the Celestial-specific ImGUI Layer

		Functions include:

			 + ImGUILayer
			 + ~ImGUILayer

			 + OnUpdate
			 + OnAttach
			 + OnDetach
			 + OnEvent

			 + OnMouseMovedEvent
			 + OnMouseScrolledEvent

			 + OnWindowResizeEvent
			 + OnWindowCloseEvent

			 + OnKeyPressedEvent
			 + OnKeyReleasedEvent
			 + OnKeyTypedEvent

*!/
/*****************************************************************************/
#pragma once
#include "Celestial/Layer.h"

#include "Celestial/Events/Event.h"
#include "Celestial/Events/ApplicationEvent.h"
#include "Celestial/Events/MouseEvent.h"
#include "Celestial/Events/KeyEvent.h"

namespace Celestial
{
	class CELESTIAL_API ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		~ImGUILayer();

		void OnUpdate();
		void OnAttach();
		void OnDetach();
		void OnEvent(Event& e);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnWindowCloseEvent(WindowCloseEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);

		bool OnKeyTypedEvent(KeyTypedEvent& e);
		
	private:
		float m_Time = 0.f;
	};
}