#pragma once

namespace Network {
	class IPlayerCallback {
	public: // Initialization/Uninitialization
		virtual ~IPlayerCallback() {}

	public: // Callback Functions
		virtual void ReceivedSpawnPlayer(unsigned int agentId) = 0;
	};
}