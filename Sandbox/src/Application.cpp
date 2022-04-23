#include "src/Celestial.h"

class Sandbox : public Celestial::Application
{
public:
	Sandbox()
	{

	}
	
	~Sandbox()
	{

	}
private:


};

Celestial::Application* Celestial::CreateApplication()
{
	return new Sandbox();
}