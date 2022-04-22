#pragma once
#include "Core.h"

namespace Celestial
{
	class CELESTIAL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	// Will be defined in the client
	Application* CreateApplication();
}