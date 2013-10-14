#pragma once

#include "IAgentManager.h"

#include <RakNetTypes.h>

namespace Players {
	struct Player final {
		RakNet::RakNetGUID GUID;
		Agents::IAgent& Agent;

		Player(RakNet::RakNetGUID guid, Agents::IAgent& agent) :
			GUID(guid),
			Agent(agent)
		{}
	};

	class IPlayerManager {
	public:
		virtual ~IPlayerManager() {}

		/// <summary>Checks if the player exists.</summary>
		/// <param name="guid">The unique identifier.</param>
		/// <returns>True if exists, false if doesn't exist.</returns>
		virtual bool PlayerExists(RakNet::RakNetGUID guid) = 0;

		/// <summary>
		/// Gets the player by GUID.
		/// Throws exception on fail, use PlayerExists to avoid this.
		/// </summary>
		/// <param name="guid">The unique identifier.</param>
		/// <returns>Player object pointer</returns>
		virtual Player& GetPlayer(RakNet::RakNetGUID guid) = 0;

		/// <summary>Adds a player to the server. Not necessarily a clean new spawn.</summary>
		/// <param name="guid">The unique identifier.</param>
		virtual void JoinPlayer(RakNet::RakNetGUID guid) = 0;

		virtual void RemovePlayer(RakNet::RakNetGUID guid) = 0;
	};
}