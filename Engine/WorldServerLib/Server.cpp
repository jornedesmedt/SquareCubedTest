#include "Server.h"

#include <stdio.h>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>

#include <Windows.h>

namespace Core {
	Server::Server() :
		m_TickInterval(50),
		m_MaxPlayers(20),
		m_NetworkManager(*this, 6789, m_MaxPlayers),
		m_AgentManager(*this),
		m_PlayerManager(*this)
	{
	}

	int Server::Run() {
		// Server Loop
		while (true)
		{
			// Handle all Packets
			m_NetworkManager.HandlePackets();

			/* Do some work here */

			// Send all Packets that have to be sent at the end of the loop
			m_AgentManager.SendPackets();

			// Make sure the server isn't keeping the CPU busy
			Sleep(m_TickInterval);
		}

		return true;
	}
}