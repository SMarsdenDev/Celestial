#pragma once

#include "Celestial/Input.h"

namespace Celestial
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		inline virtual bool IsMouseButtonPressedImpl(int button) override;
		inline virtual float GetMouseXImpl() override;
		inline virtual float GetMouseYImpl() override;
		inline virtual std::pair<float, float> GetMousePositionImpl() override;
	};

}