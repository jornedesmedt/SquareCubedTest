#pragma once

#include <ClientBase/IStateEngine.h>

#include <CommonLib/Exception.h>

#include <memory>

namespace Core { class Engine; }

namespace DefaultStateEngine {
	class DefaultStateEngine final : public StateEngine::IStateEngine {
		Core::Engine &m_Engine;

	public: // Initialization/Uninitialization
		DefaultStateEngine(Core::Engine &engine);
		~DefaultStateEngine();

	private: // State Managing Internal
		StateEngine::IState *m_CurrentState;

	private: // State Switching Internal
		bool m_Loading;
		bool m_Empty;
		std::unique_ptr<StateEngine::IStateFactory> m_QueuedFactory;
		void SwitchState(StateEngine::IStateFactory *stateFactory);
		void ExecuteSwitch();

	public: // Game Loop
		void Update(float delta);
		void Render(float delta);
	};
}