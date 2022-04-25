#pragma once
#include "Celestial/Layer.h"

namespace Celestial
{
	class CELESTIAL_API ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		~ImGUILayer();

		void OnUpdate();
		void OnAttach();
		void OnDettach();
		void OnEvent(Event& e);
	private:
		float m_Time = 0.f;
	};
}