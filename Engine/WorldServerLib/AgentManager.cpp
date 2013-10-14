#include "AgentManager.h"

#include "IServer.h"

#include <BitStream.h>

namespace Agents {
	AgentManager::AgentManager(Core::IServer& server) :
		m_Server(server)
	{
	}

	void AgentManager::RegisterAgent(std::unique_ptr<IAgent> agent) {
		m_Server.GetNetworkManager().BroadcastAgentDesc(agent->ID);
		m_Agents.push_front(std::move(agent));
	}

	void AgentManager::RemoveAgent(unsigned int agentId) {
		std::list<std::unique_ptr<IAgent>>::iterator it = m_Agents.begin();
		while (it != m_Agents.end()) {
			if ((*it)->ID == agentId) {
				// Found it!
				it = m_Agents.erase(it);
				 
				// Oh and tell the client
				m_Server.GetNetworkManager().BroadcastAgentRemove(agentId);

				// Done!
				return;
			} else
				++it;
		}
	}

	void AgentManager::SendAllAgentDescs(RakNet::RakNetGUID guid) {
		for (std::unique_ptr<IAgent> &agent : m_Agents) {
			m_Server.GetNetworkManager().SendAgentDesc(
				guid,
				agent->ID
			);
		}
	}

	void AgentManager::SendPackets() {
		for (std::unique_ptr<IAgent> &agent : m_Agents) {
			Vector2d &pos = agent->GetPosition();
			m_Server.GetNetworkManager().BroadcastAgentPosition(
				agent->ID,
				pos.X,
				pos.Y,
				agent->GetRotation()
			);
		}
	}
}