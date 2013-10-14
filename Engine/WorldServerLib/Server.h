#pragma once

#include "IServer.h"

#include "NetworkManager.h"
#include "AgentManager.h"
#include "PlayerManager.h"

namespace Core {
	class Server final : public IServer {
		const int m_TickInterval;
		const int m_MaxPlayers;
		
	public: // Property Accessors
		const int GetMaxPlayers() { return m_MaxPlayers; }

	private: // Managers
		Network::NetworkManager m_NetworkManager;
		Agents::AgentManager m_AgentManager;
		Players::PlayerManager m_PlayerManager;

	public: // Managers Accessors
		Network::INetworkManager& GetNetworkManager() { return m_NetworkManager; }
		Agents::IAgentManager& GetAgentManager() { return m_AgentManager; }
		Players::IPlayerManager& GetPlayerManager() { return m_PlayerManager; }

	public: // Loop
		Server();

		int Run();
	};
}