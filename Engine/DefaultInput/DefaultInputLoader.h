#pragma once

namespace Input { class IInput; }
namespace Context { class IContext; }

namespace DefaultInput {
	// Use this function to create a new DefaultInput object without
	// including DefaultInput.h (and the includes that come with it)
	Input::IInput* LoadInput(Context::IContext &context);
}