#pragma once

namespace Network {
	class IAgentsCallback {
	public: // Initialization/Uninitialization
		virtual ~IAgentsCallback() {}

	public: // Callback Functions
		virtual void ReceivedUpdateAgentPosition(unsigned int agentId, double x, double y, float rot) = 0;
		virtual void ReceivedAgentDesc(unsigned int agentId) = 0;
		virtual void ReceivedRemoveAgent(unsigned int agentId) = 0;
	};
}