/*****************************************************************************/
/*!
\file   Layer.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/24/2022
\brief
		This file contains the definition for Celestial's layer class

		Functions include:

			 + Layer
			 + ~Layer
*!/
/*****************************************************************************/
#include "clpch.h"
#include "Layer.h"


/*****************************************************************************/
/*!
	\brief
		Conversion Constructor

	\param name
		The name of the layer, defaulted to "Default Layer"
*/
/*****************************************************************************/
Celestial::Layer::Layer(const std::string& name)
	: m_DebugName(name)
{
}


/*****************************************************************************/
/*!
	\brief
		Destructor
*/
/*****************************************************************************/
Celestial::Layer::~Layer()
{
}
