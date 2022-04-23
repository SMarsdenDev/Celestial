#pragma once

#ifdef CL_PLATFORM_WINDOWS

	extern Celestial::Application* Celestial::CreateApplication();
	
	int main(int argc, char** argv)
	{
		Celestial::Log::Init();

		Celestial::Application* app = Celestial::CreateApplication();
		app->Run();
		delete app;
	}

#endif