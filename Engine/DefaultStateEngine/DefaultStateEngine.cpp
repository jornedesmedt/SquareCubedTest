#include "DefaultStateEngine.h"
#include "DefaultStateEngineLoader.h"

namespace DefaultStateEngine {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	StateEngine::IStateEngine* LoadStateEngine(Core::Engine &engine) { return new DefaultStateEngine(engine); }

	DefaultStateEngine::DefaultStateEngine(Core::Engine &engine) :
		m_Engine(engine),

		m_CurrentState(nullptr),

		m_Loading(false),
		m_Empty(true),
		m_QueuedFactory()
	{
	}

	DefaultStateEngine::~DefaultStateEngine() {
	}

	void DefaultStateEngine::ExecuteSwitch() {
		// Unload old State
		if (m_CurrentState != nullptr)
			delete m_CurrentState;

		// Load new State
		m_CurrentState = m_QueuedFactory->New(m_Engine);

		// Clean up and Finish
		m_QueuedFactory.reset();
		m_Loading = false;
	}

	void DefaultStateEngine::SwitchState(StateEngine::IStateFactory *stateFactory) {
		if (m_Loading)
			throw Exception("State switch attempt made during existing state switch!");

		// Queue State Switch
		m_Loading = true;
		m_Empty = false;
		m_QueuedFactory = std::unique_ptr<StateEngine::IStateFactory>(stateFactory);
	}

	// Game Loop
	void DefaultStateEngine::Update(float delta) {
		if (!m_Loading && !m_Empty)
			m_CurrentState->Update(delta);
		else if (m_QueuedFactory) {
			// Executed Queued state switch
			ExecuteSwitch();
		}
	}

	void DefaultStateEngine::Render(float delta) {
		if (!m_Loading && !m_Empty)
			m_CurrentState->Render(delta);
	}
}