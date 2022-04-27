/*****************************************************************************/
/*!
\file   SandboxClient.cpp
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

class ExampleLayer : public Celestial::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Celestial::Input::IsKeyPressed(CL_KEY_TAB))
			CL_TRACE("Tab Key is Pressed! (checking every frame)");
	}

	void OnEvent(Celestial::Event& e) override
	{
		if (e.GetEventType() == Celestial::EventType::KeyPressed)
		{
			Celestial::KeyPressedEvent pressedEvent = (Celestial::KeyPressedEvent&)e;
			if(pressedEvent.GetKeyCode() == CL_KEY_TAB)
				CL_TRACE("Tab Key is Pressed! (Event)");
			CL_TRACE("{0}", (char)pressedEvent.GetKeyCode());
		}
	}
};

class Sandbox : public Celestial::Application
{
public:
	/*****************************************************************************/
	/*!
		\brief[
			Default Constructor
	*/
	/*****************************************************************************/
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Celestial::ImGUILayer);
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