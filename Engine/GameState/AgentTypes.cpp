#include "AgentTypes.h"

namespace GameState {
	// Agent Position Update

	void Agent::UpdatePosition(double x, double y, float rot) {
		Position.X = x;
		Position.Y = y;
		Rotation.Radians = rot;
	}

	void PlayerAgent::UpdatePosition(double x, double y, float rot) {
		/* Nothing, player agent doesn't listen to packets */
	}
}