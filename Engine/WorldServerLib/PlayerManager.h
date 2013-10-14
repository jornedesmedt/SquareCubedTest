#pragma once

#include "IPlayerManager.h"

#include "PlayerPacketHandler.h"

#include <vector>
#include <memory>

namespace Core { class IServer; }

namespace Players {
	class PlayerManager final : public IPlayerManager {
		Core::IServer& m_Server;
		PlayerPacketHandler m_PacketHandler;

		std::vector<std::unique_ptr<Player>> m_Players;

	public:
		PlayerManager(Core::IServer& server);

		bool PlayerExists(RakNet::RakNetGUID guid);
		Player& GetPlayer(RakNet::RakNetGUID guid);
		void JoinPlayer(RakNet::RakNetGUID guid);
		void RemovePlayer(RakNet::RakNetGUID guid);
	};
}