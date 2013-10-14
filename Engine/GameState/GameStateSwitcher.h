#pragma once

namespace StateEngine { class IStateEngine; }

namespace GameState {
	void SwitchToState(StateEngine::IStateEngine &stateEngine);
	void ImmediateSwitchToState(StateEngine::IStateEngine &stateEngine);
}