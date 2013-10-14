#pragma once

#include "IState.h"

namespace StateEngine {
	class IStateEngine {
	public: // Initialization/Uninitialization
		virtual ~IStateEngine() {}

	public: // State Switching
		template<class T> void SwitchState() { SwitchState(new StateFactory<T>()); }
		template<class T> void ImmediateSwitchState() {
			SwitchState(new StateFactory<T>);
			ExecuteSwitch();
		}
	private:
		virtual void SwitchState(IStateFactory* stateFactory) = 0;
		virtual void ExecuteSwitch() = 0;

	public: // Game Loop
		virtual void Update(float delta) = 0;
		virtual void Render(float delta) = 0;
	};
}