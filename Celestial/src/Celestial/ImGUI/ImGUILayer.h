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

			 + OnImGUIRender
			 + OnAttach
			 + OnDetach

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

		virtual void OnImGUIRender();
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
				
	private:
		float m_Time = 0.f;
	};
}