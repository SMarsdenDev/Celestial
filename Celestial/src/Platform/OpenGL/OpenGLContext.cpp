/*****************************************************************************/
/*!
\file   OpenGLContext.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/29/2022
\brief
		This file contains the definition of the OpenGL Context Abstraction

		Functions include:

			 + OpenGLContext
			 + Init
			 + SwapBuffers
*!/
/*****************************************************************************/
#include "clpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Celestial
{
/*****************************************************************************/
    /*!
      \brief
        Conversion Constructor
      
      \param windowHandle
				The GLFW window to create a context out of
    */
/*****************************************************************************/
 OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		CL_CORE_ASSERT(windowHandle, "Window Handle NULL")
	}

/*****************************************************************************/
    /*!
      \brief
				Initializes the OpenGL Context & Glad, logs OpenGL information
    */
/*****************************************************************************/
 void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		//! Initialize Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CL_CORE_ASSERT(status, "Failed to initialize Glad!");

		CL_CORE_INFO("OpenGL Renderer: ");
		CL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

/*****************************************************************************/
    /*!
      \brief
				Handles swapping window buffers
    */
/*****************************************************************************/
 void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}