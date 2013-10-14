#pragma once

#include <CommonLib/postypes.h>

namespace GameState {
	typedef unsigned int AgentID;

	struct Agent {
		const AgentID ID;
		Vector2d Position;
		Anglef Rotation;

		Agent(AgentID id) : ID(id) {}
		virtual ~Agent() {}

		/// <summary>
		/// Sets the position of this Agent object.
		/// This function is used to make sure the player agent doesn't get
		/// affected by agent position packets and to smooth agent movement.
		/// </summary>
		/// <param name="x">The X position.</param>
		/// <param name="y">The Y position.</param>
		/// <param name="rot">The rotation angle in radians.</param>
		virtual void UpdatePosition(double x, double y, float rot);
	};

	struct PlayerAgent final : public Agent {
		PlayerAgent(AgentID id) : Agent(id) {}
		void UpdatePosition(double x, double y, float rot);
	};
}