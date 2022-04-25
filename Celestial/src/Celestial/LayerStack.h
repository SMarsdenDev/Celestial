/*****************************************************************************/
/*!
\file   LayerStack.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/24/2022
\brief
		This file contains the declaration for Celestial's Layer Stack, a container
		storing loaded layers and overlays

		Functions include:

			 + LayerStack
			 + ~LayerStack

			 + PushLayer
			 + PushOverlay
			 + PopLayer
			 + PopOverlay

			 + begin
			 + end
*!/
/*****************************************************************************/
#pragma once
#include "Celestial/Core.h"
#include "Layer.h"

#include <vector>

namespace Celestial
{
	class CELESTIAL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}