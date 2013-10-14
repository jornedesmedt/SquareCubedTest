#pragma once

#include "INetworkManager.h"

#include <forward_list>

namespace Core { class IServer; }

namespace Network {
	class NetworkManager final : public INetworkManager {
		Core::IServer &m_Server;
		RakNet::RakPeerInterface* m_Peer;

		std::forward_list<IPacketHandler*> m_Handlers;

	public:
		NetworkManager(Core::IServer &server, const int port, const int maxClients);
		~NetworkManager();

		// Send Packets
		void BroadcastAgentPosition(unsigned int agentId, double x, double y, float rot);
		void BroadcastAgentDesc(unsigned int agentId);
		void BroadcastAgentRemove(unsigned int agentId);
		void SendAgentDesc(RakNet::RakNetGUID clientGuid, unsigned int agentId);
		void SendPlayerDesc(RakNet::RakNetGUID clientGuid, unsigned int agentId);

		// Manage Client Connections
		void DropClient(RakNet::RakNetGUID clientGuid, bool notify = true);

		// Report Network-Related Problems
		void ReportProtocolError(RakNet::RakNetGUID clientGuid);

		// Handle Handlers
		void RegisterHandler(IPacketHandler& handler);
		void ClearHandlers();

		// Game Loop
		void HandlePackets();
	};
}