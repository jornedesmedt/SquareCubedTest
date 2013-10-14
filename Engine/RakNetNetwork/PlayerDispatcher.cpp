#include "PlayerDispatcher.h"

#include "RakNetNetwork.h"

#include <CommonLib/PacketTypes.h>

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	PlayerDispatcher::PlayerDispatcher(RakNetNetwork &network) :
		m_Network(network)
	{
	}

	// Send Functions

	void PlayerDispatcher::SendPlayerPos(double x, double y, float rotation) {

		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::PlayerPosUpdate);
		bs.Write(x);
		bs.Write(y);
		bs.Write(rotation);

		// Send the Packet to the World Server
		m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, m_Network.GetWorldServer(), false);
	}
}