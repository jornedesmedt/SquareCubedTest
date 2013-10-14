#pragma once

namespace StateEngine { class IStateEngine; }

namespace MainMenuState {
	void SwitchToState(StateEngine::IStateEngine &stateEngine);
	void ImmediateSwitchToState(StateEngine::IStateEngine &stateEngine);
}