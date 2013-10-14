#pragma once

namespace Network { class INetwork; }

namespace RakNetNetwork {
	// Use this function to create a new GLFWGraphics object without
	// including GLFWGraphics.h (and the includes that come with it)
	Network::INetwork* LoadNetwork(Utils::Logger logger);
}