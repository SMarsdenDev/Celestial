/*****************************************************************************/
/*!
\file   OpenGLContext.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/29/2022
\brief
		This file contains the declaration of the OpenGL Context Abstraction

		Functions include:

			 + OpenGLContext
			 + Init
			 + SwapBuffers
*!/
/*****************************************************************************/
#pragma once
#include "Celestial/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Celestial
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandel);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}