#pragma once

#include "IAgent.h"

#include <RakNetTypes.h>
#include <memory>

namespace Agents {
	class IAgentManager {
	public:
		virtual ~IAgentManager() {}

		/// <summary>Registers the agent. Passes pointer ownership to the Agent Manager.</summary>
		/// <param name="agent">The agent.</param>
		virtual void RegisterAgent(std::unique_ptr<IAgent> agent) = 0;

		virtual void RemoveAgent(unsigned int agentId) = 0;

		/// <summary>Sends all agent descriptors to the client.</summary>
		/// <param name="guid">The unique identifier.</param>
		virtual void SendAllAgentDescs(RakNet::RakNetGUID guid) = 0;
	};
}