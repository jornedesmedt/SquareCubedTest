#pragma once

#include <PacketTypes.h>
#include <RakPeerInterface.h>

namespace Network {
	class IPacketHandler {
	public:
		virtual ~IPacketHandler() {}
		virtual bool HandlePacket(RakNet::Packet* packet) = 0;
	};

	class INetworkManager {
	public:
		~INetworkManager() {}

		/// <summary>Sends the agent position to all clients.</summary>
		/// <param name="agentId">The agent unique identifier.</param>
		/// <param name="x">The X position.</param>
		/// <param name="y">The Y position.</param>
		virtual void BroadcastAgentPosition(unsigned int agentId, double x, double y, float rot) = 0;

		virtual void BroadcastAgentDesc(unsigned int agentId) = 0;

		virtual void BroadcastAgentRemove(unsigned int agentId) = 0;

		/// <summary>Sends the agent description.</summary>
		/// <param name="agentId">The agent unique identifier.</param>
		virtual void SendAgentDesc(RakNet::RakNetGUID clientGuid, unsigned int agentId) = 0;

		virtual void SendPlayerDesc(RakNet::RakNetGUID clientGuid, unsigned int agentId) = 0;

		/// <summary>Drops a client's connection.</summary>
		/// <param name="clientGuid">The client unique identifier.</param>
		/// <param name="notify">Notify the client of the dropped connection?</param>
		virtual void DropClient(RakNet::RakNetGUID clientGuid, bool notify = true) = 0;

		/// <summary>
		/// Reports a protocol error. Will drop the client as a result.
		/// </summary>
		/// <param name="clientGuid">The client unique identifier.</param>
		virtual void ReportProtocolError(RakNet::RakNetGUID clientGuid) = 0;

		virtual void RegisterHandler(IPacketHandler& handler) = 0;
		virtual void ClearHandlers() = 0;
	};
}