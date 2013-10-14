#include "PlayerPacketHandler.h"

#include <BitStream.h>

namespace Players {
	PlayerPacketHandler::PlayerPacketHandler(IPlayerManager& playerManager, Network::INetworkManager& networkManager) :
		m_PlayerManager(playerManager),
		m_NetworkManager(networkManager)
	{}

	bool PlayerPacketHandler::HandlePacket(RakNet::Packet* packet) {
		switch (packet->data[0]) {
		case ID_DISCONNECTION_NOTIFICATION:
		case ID_CONNECTION_LOST: {
			// Make sure the client isn't doing something weird
			if (!m_PlayerManager.PlayerExists(packet->guid))
				return true;

			// Remove Player from Server
			m_PlayerManager.RemovePlayer(packet->guid);

			} return true;
		case (int) GamePacketIDType::PlayerSpawn:
			// Associate a new Player with the client that connected
			m_PlayerManager.JoinPlayer(packet->guid);

			return true;
		case (int) GamePacketIDType::PlayerPosUpdate: {
			// Make sure the client isn't doing something weird
			if (!m_PlayerManager.PlayerExists(packet->guid)) {
				return true;
			}

			// Retrieve the Player Object by GUID
			Player& player = m_PlayerManager.GetPlayer(packet->guid);

			// Set up BitStream
			RakNet::BitStream bs(packet->data, packet->length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			double x, y;
			bs.Read(x);
			bs.Read(y);
			float rot;
			bool s = bs.Read(rot);

			// Make sure the packet is correctly received
			if (!s) {
				m_NetworkManager.ReportProtocolError(packet->guid);
				return true;
			}

			// Change the Position of the Player Agent
			player.Agent.SetPosition(x, y);
			player.Agent.SetRotation(rot);

			} return true;
		}

		return false;
	}
}