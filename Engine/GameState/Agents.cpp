#include "Agents.h"

#include <ClientBase/INetwork.h>
#include <ClientBase/INetworkFactory.h>
#include <ClientBase/IPacketHandler.h>

#include <CommonLib/Exception.h>

namespace GameState {
	// Initialization/Uninitialization

	Agents::Agents(Network::INetwork &network) :
		m_Network(network),
		m_Handler(m_Network.GetFactory().CreateAgentsHandler(*this))
	{
		m_Network.Attach(*m_Handler);
	}

	Agents::~Agents() {
		m_Network.Detach(*m_Handler);
	}

	// Agents Management Utility Functions

	void Agents::AddAgent(Agent *agent) {
		m_Agents.push_front(std::unique_ptr<Agent>(agent));
	}

	void Agents::RemoveAgent(AgentID agentId) {
		std::list<std::unique_ptr<Agent>>::iterator it = m_Agents.begin();
		while (it != m_Agents.end()) {
			if ((*it)->ID == agentId) {
				// Found it!
				it = m_Agents.erase(it);
				return;
			}
			else
				++it;
		}
	}

	void Agents::UpdateAgent(AgentID agentId) {
		for (std::unique_ptr<Agent> &agent : m_Agents) {
			if (agent->ID == agentId) {
				/* Update.... stufff... here I guess? */
				return;
			}
		}

		// Not found, throw Exception
		throw Exception("Agent not Found");
	}

	bool Agents::AgentExists(AgentID agentId) {
		for (std::unique_ptr<Agent> &agent : m_Agents) {
			if (agent->ID == agentId)
				return true;
		}

		// Not found, return false
		return false;
	}

	// Game Loop

	void Agents::Render(RenderFunc func) {
		for (std::unique_ptr<Agent> &agent : m_Agents) {
			func(
				agent->Position.X,
				agent->Position.Y,
				agent->Rotation.GetDegrees()
			);
		}
	}

	// Callback Functions

	void Agents::ReceivedUpdateAgentPosition(unsigned int agentId, double x, double y, float rot) {
		for (std::unique_ptr<Agent> &agent : m_Agents) {
			if (agent->ID == agentId) {
				// Update the Agent's Position
				agent->UpdatePosition(x, y, rot);
				return;
			}
		}
	}

	void Agents::ReceivedAgentDesc(unsigned int agentId) {
		// Add new Agent if it doesn't exist
		if (!AgentExists(agentId))
			AddAgent(new Agent(agentId));

		// Update the (newly created?) Agent
		UpdateAgent(agentId);
	}

	void Agents::ReceivedRemoveAgent(unsigned int agentId) {
		// Remove the Agent
		RemoveAgent(agentId);
	}
}