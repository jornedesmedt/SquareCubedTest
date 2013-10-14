#include "AgentsPacketHandler.h"

#include <ClientBase/INetwork.h>
#include <ClientBase/IAgentsCallback.h>

#include <CommonLib/PacketTypes.h>

#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	AgentsPacketHandler::AgentsPacketHandler(Network::INetwork &network, Network::IAgentsCallback &callback) :
		m_Network(network),
		m_Callback(callback)
	{
	}

	// Game Loop

	bool AgentsPacketHandler::HandlePacket(RakNet::Packet &packet) {
		switch (packet.data[0]) {
		case (int) GamePacketIDType::AgentPosUpdate: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int agentId;
			bs.Read(agentId);

			double x, y;
			bs.Read(x);
			bs.Read(y);
			float rot;
			bool s = bs.Read(rot);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedUpdateAgentPosition(agentId, x, y, rot);
			} return true;
		case (int) GamePacketIDType::AgentDesc: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int agentId;
			bool s = bs.Read(agentId);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedAgentDesc(agentId);
			} return true;
		case (int) GamePacketIDType::AgentRemove: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int agentId;
			bool s = bs.Read(agentId);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedRemoveAgent(agentId);
			} return true;
		}

		return false;
	}
}