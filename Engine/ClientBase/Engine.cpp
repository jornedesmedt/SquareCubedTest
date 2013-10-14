#include "Engine.h"

#include "IContent.h"
#include "IContext.h"
#include "IGraphics.h"
#include "IWindow.h"
#include "IInput.h"
#include "INetwork.h"
#include "IStateEngine.h"

#include <CommonLib/Exception.h>
#include <CommonLib/ILoggingManager.h>

#include <thread>

namespace Core {
	// Initialization/Uninitialization

	Engine::Engine(Utils::ILoggingManager *loggingManager) :
		m_Logger(loggingManager->CreateLogger("Engine")),
		m_LoggingManager(loggingManager)
	{
		m_Logger.LogInfo("Core::Engine Initialized");
	}

	// Module Setters

	void Engine::SetContent(Content::IContent *content) {
		if (m_Context)
			throw Exception("Content Module Already Assigned");
		m_Content = std::unique_ptr<Content::IContent>(content);
	}

	void Engine::SetContext(Context::IContext *context) {
		if (m_Context)
			throw Exception("Context Module Already Assigned");
		m_Context = std::unique_ptr<Context::IContext>(context);
	}

	void Engine::SetGraphics(Graphics::IGraphics *graphics) {
		if (m_Graphics)
			throw Exception("Graphics Module Already Assigned");
		m_Graphics = std::unique_ptr<Graphics::IGraphics>(graphics);
	}

	void Engine::SetInput(Input::IInput *input) {
		if (m_Input)
			throw Exception("Input Module Already Assigned");
		m_Input = std::unique_ptr<Input::IInput>(input);
	}

	void Engine::SetNetwork(Network::INetwork *network) {
		if (m_Network)
			throw Exception("Network Module Already Assigned");
		m_Network = std::unique_ptr<Network::INetwork>(network);
	}

	void Engine::SetStateEngine(StateEngine::IStateEngine *stateEngine) {
		if (m_StateEngine)
			throw Exception("State Engine Module Already Assigned");
		m_StateEngine = std::unique_ptr<StateEngine::IStateEngine>(stateEngine);
	}

	// Module Accessors

	Utils::ILoggingManager& Engine::GetLoggingManager() { return *m_LoggingManager; }
	Content::IContent& Engine::GetContent() { return *m_Content; }
	Context::IContext& Engine::GetContext() { return *m_Context; }
	Graphics::IGraphics& Engine::GetGraphics() { return *m_Graphics; }
	Input::IInput& Engine::GetInput() { return *m_Input; }
	Network::INetwork& Engine::GetNetwork() { return *m_Network; }
	StateEngine::IStateEngine& Engine::GetStateEngine() { return *m_StateEngine; }

	// Game Loop

	void Engine::Execute() {
		while (!m_Context->GetMainWindow().HasCloseRequest()) {
			// Handle all Packets
			m_Network->HandlePackets();

			// Poll Window Events
			m_Context->PollEvents();

			// Update Everything
			m_StateEngine->Update(0.016f);

			// Render Everything
			m_Graphics->BeginRender();
			m_StateEngine->Render(0.016f);
			m_Graphics->EndRender();

			// Hardcoded Sleep for now
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	}
}