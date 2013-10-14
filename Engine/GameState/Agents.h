#pragma once

#include "AgentTypes.h"

#include <ClientBase/IAgentsCallback.h>

#include <memory>
#include <list>
#include <functional>

namespace Network {
	class INetwork;
	class IPacketHandler;
}

namespace GameState {
	class Agents final : public Network::IAgentsCallback {
		// Networking Stuff
		Network::INetwork &m_Network;
		std::unique_ptr<Network::IPacketHandler> m_Handler;
		
		// Agents Container
		std::list<std::unique_ptr<Agent>> m_Agents;

	public: // Initialization/Uninitialization
		Agents(Network::INetwork &networkFactory);
		~Agents();

	public: // Agents Management Utility Functions
		void AddAgent(Agent *agent);
		void RemoveAgent(AgentID agentId);
		void UpdateAgent(AgentID agentId);

		bool AgentExists(AgentID agentId);

	public: // Game Loop
		// Lambda callback for now until an AgentRenderer is added
		typedef std::function<void(double, double, float)> RenderFunc;
		void Render(RenderFunc func);

	public: // Callback Functions
		void ReceivedUpdateAgentPosition(unsigned int agentId, double x, double y, float rot);
		void ReceivedAgentDesc(unsigned int agentId);
		void ReceivedRemoveAgent(unsigned int agentId);
	};
}