#pragma once

#include "IPlayerManager.h"
#include "INetworkManager.h"

namespace Core { class IServer; }

namespace Players {
	class PlayerPacketHandler final : public Network::IPacketHandler {
		IPlayerManager& m_PlayerManager;
		Network::INetworkManager& m_NetworkManager;

	public:
		PlayerPacketHandler(IPlayerManager& playerManager, Network::INetworkManager& networkManager);

		bool HandlePacket(RakNet::Packet* packet);
	};
}