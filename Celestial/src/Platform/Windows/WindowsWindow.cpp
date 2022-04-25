/*****************************************************************************/
/*!
\file   WindowsWindow.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the class definition for the Windows-specific window,
		it also defines the static Create function declared in Window.h

		Functions include:

			 + GLFWErrorCallback

			 + Create
			 + WindowsWindow
			 + ~WindowsWindow
			 + Init
			 + Shutdown
			 + OnUpdate
			 + SetVSync
			 + IsVSync
*!/
/*****************************************************************************/
#include "clpch.h"
#include "WindowsWindow.h"
#include "Celestial/Core.h"

#include "Celestial/Events/ApplicationEvent.h"
#include "Celestial/Events/MouseEvent.h"
#include "Celestial/Events/KeyEvent.h"

#include "Glad/glad.h"

namespace Celestial
{
	static bool s_GLFWInitialized = false;


	/*****************************************************************************/
    /*!
      \brief
        The callback function for a GLFW error

			\param error
				The integer code for the GLFW error

			\param desc
				The description for the error
    */
	/*****************************************************************************/
  static void GLFWErrorCallback(int error, const char* desc)
	{
		CL_CORE_ERROR("GLFW Error {{0}}: {1}", error, desc);
	}

	/*****************************************************************************/
    /*!
      \brief
        Creates a window context using properties, sets as current

			\param props
				The structure containing window properties

			\return
				Returns a pointer to the GLFWwindow
    */
	/*****************************************************************************/
  Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	/*****************************************************************************/
	/*!
		\brief
			Conversion Constructor

		\param props
			The structure containing window properties
	*/
	/*****************************************************************************/
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	/*****************************************************************************/
	/*!
		\brief
			Destructor
	*/
	/*****************************************************************************/
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	/*****************************************************************************/
	/*!
		\brief
			Initalizes window with property data, sets event callbacks

		\param props
			The structure containing window properties
	*/
	/*****************************************************************************/
	void WindowsWindow::Init(const WindowProps& props)
	{
		// Set Window Properties
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		CL_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			CL_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		//! Create Window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		//! Initialize Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CL_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data); //!< Stores parameter data in OpenGL buffer storage
		SetVSync(true);

		// Set Window Event Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int w, int h)
			{
				//! Get window data from OpenGL buffer storafe
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//! Create resize event
				WindowResizeEvent event(w, h);
				data.Width = w;
				data.Height = h;

				//! Call event callback with resize event
				data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		// Set Key Event Callbacks
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);

						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}

			});

		// Set Mouse Event Callbacks
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x_offset, double y_offset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)x_offset, (float)y_offset);
				data.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x_pos, double y_pos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)x_pos, (float)y_pos);
				data.EventCallback(event);
			});
	}
	
	/*****************************************************************************/
	/*!
		\brief
			Destroys window
	*/
	/*****************************************************************************/
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	/*****************************************************************************/
	/*!
		\brief
			Polls events, swaps frame buffers
	*/
	/*****************************************************************************/
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	/*****************************************************************************/
	/*!
		\brief
			Sets VSync, since we can't get that info through OpenGL

		\param enabled
			The boolean to set to VSync
	*/
	/*****************************************************************************/
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	/*****************************************************************************/
	/*!
		\brief
			Getter for VSync

		\return
			Returns if VSync is active
	*/
	/*****************************************************************************/
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}