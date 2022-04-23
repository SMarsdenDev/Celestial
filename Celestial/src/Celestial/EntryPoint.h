/*****************************************************************************/
/*!
\file   EntryPoint.h
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the definition of the application's starting point.
		Currently it just creates and runs the client-defined application

		Functions include:

			 + CreateApplication
			 + main
*!/
/*****************************************************************************/
#pragma once

#ifdef CL_PLATFORM_WINDOWS

	extern Celestial::Application* Celestial::CreateApplication();
	
/*****************************************************************************/
    /*!
      \brief
        main function
      
      \param argc
        The number of command line arguments
      
      \param argv
        An array of strings containing command line parameters
        
      \return
        Returns success code
    */
/*****************************************************************************/
	int main(int argc, char** argv)
	{
		Celestial::Log::Init();

		Celestial::Application* app = Celestial::CreateApplication();
		app->Run();
		delete app;
	}

#endif