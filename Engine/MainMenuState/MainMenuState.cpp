#include "MainMenuState.h"
#include "MainMenuStateSwitcher.h"

#include <ClientBase/Engine.h>
#include <ClientBase/IContent.h>
#include <ClientBase/IStateEngine.h>
#include <ClientBase/INetwork.h>
#include <ClientBase/INetworkFactory.h>
#include <ClientBase/IPacketHandler.h>

#include <GameState/GameStateSwitcher.h>

namespace MainMenuState {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	void SwitchToState(StateEngine::IStateEngine &stateEngine) { stateEngine.SwitchState<MainMenuState>(); }
	void ImmediateSwitchToState(StateEngine::IStateEngine &stateEngine) { stateEngine.ImmediateSwitchState<MainMenuState>(); }

	// Initialization/Uninitialization

	MainMenuState::MainMenuState(Core::Engine &engine) :
		m_Engine(engine),
		m_PacketHandler(m_Engine.GetNetwork().GetFactory().CreateMainMenuHandler(*this))
	{
		m_Engine.GetNetwork().Attach(*m_PacketHandler);
		m_Engine.GetNetwork().Connect("127.0.0.1", 6789);
	}

	MainMenuState::~MainMenuState() {
		// Detach Packet Handlers
		m_Engine.GetNetwork().Detach(*m_PacketHandler);

		// Free all Content
		m_Engine.GetContent().ClearContent();
	}

	// Network Callback Functions

	void MainMenuState::ReceivedRequestAccepted() {
		GameState::SwitchToState(m_Engine.GetStateEngine());
	}

	// Game Loop

	void MainMenuState::Update(float delta) {
	}

	void MainMenuState::Render(float delta) {
	}
}