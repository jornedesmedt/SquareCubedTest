#include "DefaultInput.h"
#include "DefaultInputLoader.h"

#include <ClientBase/IContext.h>
#include <ClientBase/IWindow.h>

namespace DefaultInput {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	Input::IInput* LoadInput(Context::IContext &context) { return new DefaultInput(context); }

	// Key Accessors

	bool DefaultInput::GetForwardKey() { return m_Keys[m_ForwardKey]; }
	bool DefaultInput::GetBackwardKey() { return m_Keys[m_BackwardKey]; }
	bool DefaultInput::GetLeftKey() { return m_Keys[m_LeftKey]; }
	bool DefaultInput::GetRightKey() { return m_Keys[m_RightKey]; }

	// Key Accessors

	Input::AxisDesc DefaultInput::GetMovementAxis() {
		// Get Raw Values from Keys
		Input::AxisDesc retVal;
		if (GetRightKey())
			retVal.RawValues.X += 1;
		if (GetLeftKey())
			retVal.RawValues.X -= 1;
		if (GetForwardKey())
			retVal.RawValues.Y += 1;
		if (GetBackwardKey())
			retVal.RawValues.Y -= 1;

		// Check if there was some input
		if (retVal.RawValues.X == 0 && retVal.RawValues.Y == 0) {
			// No input, make sure the caller knows
			retVal.Any = false;
		}
		else {
			// Hurray, Input! Calculate Angle
			Anglef angle = atan2f(retVal.RawValues.X, retVal.RawValues.Y);

			// Scale Input
			retVal.Scaled.X = angle.GetSin() * fabs(retVal.RawValues.X);
			retVal.Scaled.Y = angle.GetCos() * fabs(retVal.RawValues.Y);

			// And Set the Angle
			retVal.Angle.Radians = -angle.Radians;
		}

		return retVal;
	}

	// Initialization/Uninitialization

	DefaultInput::DefaultInput(Context::IContext &context) :
		m_Context(context),
		m_ForwardKey(m_Context.GetKeyId('W')),
		m_BackwardKey(m_Context.GetKeyId('S')),
		m_LeftKey(m_Context.GetKeyId('A')),
		m_RightKey(m_Context.GetKeyId('D')),
#pragma warning( disable : 4351 ) // New behavior warning
		m_Keys()
	{
		// Bind Key Callback
		m_Context.GetMainWindow().SetKeyCallback(std::bind(
			&DefaultInput::KeyCallback,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4));
	}

	DefaultInput::~DefaultInput() {
	}

	// Key Callback

	void DefaultInput::KeyCallback(int key, int scancode, int action, int mods) {
		// Filter out Function Keys
		if (key < 100) {
			if (action == 0)
				m_Keys[key] = false;
			else if (action == 1)
				m_Keys[key] = true;
		}
	}
}