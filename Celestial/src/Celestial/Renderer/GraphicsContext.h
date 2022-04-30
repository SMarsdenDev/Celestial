/*****************************************************************************/
/*!
\file   GraphicsContext.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/29/2022
\brief
		This file contains the definition of the base Graphics Context, which
		specific API will derive

		Functions include:

			 + Init
			 + SwapBuffers
*!/
/*****************************************************************************/
#pragma once

namespace Celestial
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}