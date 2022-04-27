/*****************************************************************************/
/*!
\file   Application.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
    This file contains the definition of the Celestial Application base class.
    It is currently responsible for creating a window and dispatiching 
    window close events

    Functions include:

       + Application
       + ~Application
       + Run
       + OnEvent
       + OnWindowClose
*!/
/*****************************************************************************/
#include "clpch.h"
#include "Application.h"

#include "Celestial/Events/Event.h"
#include "Celestial/Log.h"

#include "glad/glad.h"

#include "Input.h"

namespace Celestial
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
  
  Application* Application::s_Instance = nullptr;
  
/*****************************************************************************/
    /*!
      \brief
        Default Constructor
    */
/*****************************************************************************/
  Application::Application()
  {
    CL_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
  }
  
  
/*****************************************************************************/
    /*!
      \brief
        Destructor
    */
/*****************************************************************************/
  Application::~Application()
  {

  }
  
/*****************************************************************************/
    /*!
      \brief
        Runs the client application, currently updates the window
    */
/*****************************************************************************/
  void Application::Run()
  {

    while (m_Running)
    {
      glClearColor(113.f / 255.f, 74.f / 255.f, 138.f / 255.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT);
      
      // Update the layer stack
      for (Layer* layer : m_LayerStack)
        layer->OnUpdate();

      // Update the window
      m_Window->OnUpdate();
    }
  }

  
/*****************************************************************************/
    /*!
      \brief
        Processed events received by glfw
      
      \param e
        The event to process
    */
/*****************************************************************************/
  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
    {
      (*--it)->OnEvent(e);
      if (e.Handled)
        break;
    }
  }

  /*****************************************************************************/
    /*!
      \brief
        Pushes a layer into the application's layer stack

      \param layer
        The layer to push
    */
    /*****************************************************************************/
  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  /*****************************************************************************/
     /*!
       \brief
         Pushes a overlay into the application's layer stack

       \param overlay
         The overlay to push
     */
  /*****************************************************************************/
  void Application::PushOverlay(Layer* overlay)
  {
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
  }

  
/*****************************************************************************/
    /*!
      \brief
        The function to pass to the event dispatcher, sets window to 
        not running
      
      \param e
        The WindowCloseEvent, currently unused
    */
/*****************************************************************************/
  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    m_Running = false;

    return true;
  }

}