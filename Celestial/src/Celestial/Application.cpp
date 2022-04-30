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

#include "Celestial/ImGUI/ImGUILayer.h"

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

    m_ImGUILayer = new ImGUILayer;
    PushOverlay(m_ImGUILayer);

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    float vertices[3 * 3] =
    {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    unsigned int indices[3] = { 0, 1, 2 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

      glBindVertexArray(m_VertexArray); //!< Unnecessary, VAO isn't unbound on creation
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
      
      // Update the layer stack
      for (Layer* layer : m_LayerStack)
        layer->OnUpdate();

      m_ImGUILayer->Begin();
      for (Layer* layer : m_LayerStack)
        layer->OnImGUIRender();
      m_ImGUILayer->End();

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