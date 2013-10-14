#include "PlayerManager.h"

#include <Exception.h>

#include "IServer.h"
#include "AgentTypes.h"

#include <algorithm>

namespace Players {
	PlayerManager::PlayerManager(Core::IServer& server) :
		m_Server(server),
		m_PacketHandler(*this, m_Server.GetNetworkManager()),
		m_Players()
	{
		// Reserve max size of the Player Vector
		m_Players.reserve(m_Server.GetMaxPlayers());

		// Register the packet handler
		server.GetNetworkManager().RegisterHandler(m_PacketHandler);
	}

	bool PlayerManager::PlayerExists(RakNet::RakNetGUID guid) {
		// TODO: Cache result for use in GetPlayer
		
		for (std::unique_ptr<Player> &player : m_Players)
			if (player->GUID == guid)
				return true;
		
		// Not found :C
		return false;
	}

	Player& PlayerManager::GetPlayer(RakNet::RakNetGUID guid) {
		for (std::unique_ptr<Player> &player : m_Players)
			if (player->GUID == guid)
				return *player;

		// NOT FOUND AAAAAAAAA! SCREAM PANIC THROW EXCEPTIONS!
		throw Exception("GetPlayer called with invalid player GUID");
	}

	void PlayerManager::JoinPlayer(RakNet::RakNetGUID guid) {
		// Send all Agent descs to the Player
		m_Server.GetAgentManager().SendAllAgentDescs(guid);

		// Create a new dummy Agent for the Player to use
		std::unique_ptr<Agents::IAgent> agent(new Agents::BasicAgent());

		// Add Player to the Vector
		Player *player = new Player(
			guid,
			*agent
		);
		m_Players.push_back(std::unique_ptr<Player>(player));

		// Send the Player a Player Desc packet
		// Has to be before registering the agent
		m_Server.GetNetworkManager().SendPlayerDesc(
			player->GUID,
			player->Agent.ID
		);

		// Pass the Agent to the Agent Manager
		m_Server.GetAgentManager().RegisterAgent(std::move(agent));

		// And Log it
		printf_s("New Player (%s) Joined World\n", guid.ToString());
	}

	void PlayerManager::RemovePlayer(RakNet::RakNetGUID guid) {
		// Find and Remove Player
		unsigned int agentId = 0;
		std::vector<std::unique_ptr<Player>>::iterator it = m_Players.begin();
		while(it != m_Players.end()) {
			if ((*it)->GUID == guid) {
				// Found it!
				agentId = (*it)->Agent.ID;
				it = m_Players.erase(it);
				break;
			} else
				++it;
		}

		// Remove Player Agent
		m_Server.GetAgentManager().RemoveAgent(agentId);

		// And Log it
		printf_s("Player (%s) Parted World\n", guid.ToString());
	}
}