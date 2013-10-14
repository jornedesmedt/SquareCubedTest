#pragma once

#include <ClientBase/IInput.h>

namespace Context { class IContext; }

namespace DefaultInput {
	class DefaultInput final : public Input::IInput {
		Context::IContext &m_Context;

	public: // Initialization/Uninitialization
		DefaultInput(Context::IContext &context);
		~DefaultInput();

	private: // Stored Key Configs
		Input::KeyID m_ForwardKey;
		Input::KeyID m_BackwardKey;
		Input::KeyID m_LeftKey;
		Input::KeyID m_RightKey;

	public: // Key Accessors
		bool GetForwardKey();
		bool GetBackwardKey();
		bool GetLeftKey();
		bool GetRightKey();

	public: // Complex Input Accessors
		Input::AxisDesc GetMovementAxis();

	private: // Input Storing
		bool m_Keys[100];

	public: // Key Callback
		void KeyCallback(int key, int scancode, int action, int mods);
	};
}