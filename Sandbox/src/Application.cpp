/*****************************************************************************/
/*!
\file   Application.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/23/2022
\brief
		This file contains the definition for the client application and the 
		CreateApplication function declared in Celestial's 'Application.h'

		Functions include:

			 + Sandbox
			 + ~Sandbox

			 + CreateApplication
*!/
/*****************************************************************************/
#include "src/Celestial.h"

class Sandbox : public Celestial::Application
{
public:
	/*****************************************************************************/
	/*!
		\brief
			Default Constructor
	*/
	/*****************************************************************************/
	Sandbox()
	{

	}
	
	/*****************************************************************************/
	/*!
		\brief
			Destructor
	*/
	/*****************************************************************************/
	~Sandbox()
	{

	}
private:


};

	/*****************************************************************************/
	/*!
		\brief
			Creates a new application of the proper type

		\return
			Returns a pointer to the new application
	*/
	/*****************************************************************************/
	Celestial::Application* Celestial::CreateApplication()
{
	return new Sandbox();
}