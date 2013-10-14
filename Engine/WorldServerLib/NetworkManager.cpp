#include "NetworkManager.h"

#include "IServer.h"

#include <BitStream.h>

#include <stdio.h>
#include <cstdint>

#include "gdefines.h"
#include <Exception.h>

namespace Network {
	NetworkManager::NetworkManager(Core::IServer &server, const int port, const int maxClients) :
		m_Server(server),
		m_Peer(RakNet::RakPeerInterface::GetInstance())
	{
		// Start Server
		RakNet::SocketDescriptor sd(port, 0);
		RakNet::StartupResult result = m_Peer->Startup(maxClients, &sd, 1);

		// Check if RakNet correctly started
		if (result != RakNet::RAKNET_STARTED) {
			// Placeholder exception
			throw Exception("RakNet failed to start");
		}
		m_Peer->SetMaximumIncomingConnections(maxClients);
	}

	NetworkManager::~NetworkManager() {
		RakNet::RakPeerInterface::DestroyInstance(m_Peer);
	}

	void NetworkManager::BroadcastAgentPosition(unsigned int agentId, double x, double y, float rot) {
		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::AgentPosUpdate);
		bs.Write(agentId);
		bs.Write(x);
		bs.Write(y);
		bs.Write(rot);

		// Send the Packet to all Clients
		m_Peer->Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}

	void NetworkManager::BroadcastAgentDesc(unsigned int agentId) {
		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::AgentDesc);
		bs.Write(agentId);

		// Send the Packet to all Clients
		m_Peer->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}

	void NetworkManager::BroadcastAgentRemove(unsigned int agentId) {
		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::AgentRemove);
		bs.Write(agentId);

		// Send the Packet to all Clients
		m_Peer->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}

	void NetworkManager::SendAgentDesc(RakNet::RakNetGUID clientGuid, unsigned int agentId) {
		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::AgentDesc);
		bs.Write(agentId);

		// Send the Packet to the Client
		m_Peer->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientGuid, false);
	}

	void NetworkManager::SendPlayerDesc(RakNet::RakNetGUID clientGuid, unsigned int agentId) {
		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::PlayerDesc);
		bs.Write(agentId);

		// Send the Packet to the Client
		m_Peer->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientGuid, false);
	}

	void NetworkManager::DropClient(RakNet::RakNetGUID clientGuid, bool notify) {
		m_Peer->CloseConnection(clientGuid, notify);
	}

	void NetworkManager::ReportProtocolError(RakNet::RakNetGUID clientGuid) {
		// Burn the witch!
		DropClient(clientGuid);
		printf("Client (%s) failed to conform to protocol!\n", clientGuid.ToString());
	}

	void NetworkManager::RegisterHandler(IPacketHandler& handler) {
		m_Handlers.push_front(&handler);
	}

	void NetworkManager::ClearHandlers() {
		m_Handlers.clear();
	}

	void NetworkManager::HandlePackets() {
		RakNet::Packet *packet;
		for (packet = m_Peer->Receive(); packet != nullptr; m_Peer->DeallocatePacket(packet), packet = m_Peer->Receive()) {
			bool valid = true;

			switch (packet->data[0]) {
			case ID_NEW_INCOMING_CONNECTION: {
				printf("New Client Connected\n");

				// Send Server Name and Version to Client
				RakNet::BitStream bs;
				bs.Write(GamePacketIDType::ClientLog);
				bs.Write((std::uint8_t)1);
				bs.Write("\n ==== "APP_NAME" ==== \n"
						 "Version:   "APP_VERSION"\n"
						 "Author:    "APP_AUTHOR"\n"
						 STR_SUPPORT);
				m_Peer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, packet->guid, false);

				} break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				printf("A client has disconnected.\n");
				break;
			case ID_CONNECTION_LOST:
				printf("A client has lost the connection.\n");
				break;
			default:
				// Packet not found, gonna mark it invalid for now
				valid = false;
				break;
			}

			// Send Packet to Packet Handlers
			for (IPacketHandler* packetHandler : m_Handlers)
				valid |= packetHandler->HandlePacket(packet);

			if (!valid) {
				// Invalid Packet, Log it
				printf("Message with invalid identifier %i has arrived.\n", packet->data[0]);
			}
		}
	}
}