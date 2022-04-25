/*****************************************************************************/
/*!
\file   Layer.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/24/2022
\brief
		This file contains the declaration for Celestial's layer class

		Functions include:

			 + Layer
			 + ~Layer

			 + OnAttach
			 + OnDetach
			 + OnUpdate
			 + OnEvent

			 + GetName
*!/
/*****************************************************************************/
#pragma once
#include "clpch.h"
#include "Celestial/Core.h"
#include "Events/Event.h"

namespace Celestial
{
	class CELESTIAL_API Layer
	{
	public:
		Layer(const std::string& name = "Default Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}