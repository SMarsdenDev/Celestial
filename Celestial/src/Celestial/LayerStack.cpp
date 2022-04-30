/*****************************************************************************/
/*!
\file   LayerStack.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/24/2022
\brief
		This file contains the definition for Celestial's Layer Stack, a container
		storing loaded layers and overlays

		Functions include:

			 + LayerStack
			 + ~LayerStack

			 + PushLayer
			 + PushOverlay
			 + PopLayer
			 + PopOverlay
*!/
/*****************************************************************************/
#include "clpch.h"
#include "LayerStack.h"

namespace Celestial
{
	
	/*****************************************************************************/
	/*!
		\brief
			Default Constructor
	*/
	/*****************************************************************************/
	LayerStack::LayerStack()
	{
	}

	
	/*****************************************************************************/
	/*!
		\brief
			Destructor
	*/
	/*****************************************************************************/
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	
	/*****************************************************************************/
	/*!
		\brief
			Adds a layer to the proper section of the layer stack

		\param layer
			The layer to push
	*/
	/*****************************************************************************/
	void LayerStack::PushLayer(Layer* layer)
	{
		//! Pushes layer to the end of the layer section of the layer/overlay stack
		//! and updates pointer
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	
	/*****************************************************************************/
	/*!
		\brief
			Adds an overlay to the proper section of the layer stack

		\param overlay
			The overlay to push
	*/
	/*****************************************************************************/
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	/*****************************************************************************/
	/*!
		\brief
			Removes a layer from the stack

		\param layer
			The layer to remove
	*/
	/*****************************************************************************/
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			(*it)->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	/*****************************************************************************/
	/*!
		\brief
			Removes an overlay from the stack

		\param overlay
			The overlay to remove
	*/
	/*****************************************************************************/
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			(*it)->OnDetach();
			m_Layers.erase(it);
		}
	}

}