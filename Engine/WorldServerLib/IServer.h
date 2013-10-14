#pragma once

#include "INetworkManager.h"
#include "IAgentManager.h"
#include "IPlayerManager.h"

namespace Core {
	class IServer {
	public:
		virtual ~IServer() {}

		virtual const int GetMaxPlayers() = 0;

		virtual Network::INetworkManager& GetNetworkManager() = 0;
		virtual Agents::IAgentManager& GetAgentManager() = 0;
		virtual Players::IPlayerManager& GetPlayerManager() = 0;
	};
}