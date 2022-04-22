#pragma once


#ifdef CL_PLATFORM_WINDOWS

	extern Celestial::Application* Celestial::CreateApplication();
	
	int main(int argc, char** argv)
	{
		Celestial::Log::Init();

		CL_CORE_WARN("Help I'm Warning {1} {0}", 3.0f, 1.5f);

		Celestial::Application* app = Celestial::CreateApplication();
		app->Run();
		delete app;
	}

#endif