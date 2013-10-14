#pragma once

#include "IAgentManager.h"

#include <list>
#include <memory>

namespace Core { class IServer; }

namespace Agents {
	class AgentManager final : public IAgentManager {
		Core::IServer& m_Server;

		std::list<std::unique_ptr<IAgent>> m_Agents;

	public:
		AgentManager(Core::IServer& server);

		void RegisterAgent(std::unique_ptr<IAgent> agent);
		void RemoveAgent(unsigned int agentId);

		// Networking Functions
		void SendAllAgentDescs(RakNet::RakNetGUID guid);

		// Game Loop
		void SendPackets();
	};
}