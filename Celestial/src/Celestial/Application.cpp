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

namespace Celestial
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
  
  
/*****************************************************************************/
    /*!
      \brief
        Default Constructor
    */
/*****************************************************************************/
  Application::Application()
  {
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
      m_Window->OnUpdate();
    }
  }

  
/*****************************************************************************/
    /*!
      \brief
        Defines a Window Close Event that will be called by OpenGL
      
      \param e
        The event to dispatch
    */
/*****************************************************************************/
  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    CL_CORE_TRACE("{0}", e);
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