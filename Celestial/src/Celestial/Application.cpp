#include "Application.h"

#include "Celestial/Events/Event.h"
#include "Celestial/Events/ApplicationEvent.h"
#include "Celestial/Log.h"

namespace Celestial
{
  Application::Application()
  {

  }

  Application::~Application()
  {

  }

  void Application::Run()
  {
    WindowResizeEvent e(1200, 720);
    if (e.IsInCategory(EventCategoryApplication))
      CL_TRACE(e);
    else if (e.IsInCategory(EventCategoryInput))
      CL_TRACE(e);

    while (true);
  }

}