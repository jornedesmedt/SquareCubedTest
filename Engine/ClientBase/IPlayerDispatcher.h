#pragma once

namespace Network {
	class IPlayerDispatcher {
	public: // Initialization/Uninitialization
		virtual ~IPlayerDispatcher() {}

	public: // Send Functions
		virtual void SendPlayerPos(double x, double y, float rotation) = 0;
	};
}