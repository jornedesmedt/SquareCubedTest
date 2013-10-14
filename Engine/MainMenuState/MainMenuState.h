#pragma once

#include <ClientBase/IState.h>
#include <ClientBase/IMainMenuCallback.h>

#include <CommonLib/Events.h>

#include <memory>

namespace Network { class IPacketHandler; }

namespace MainMenuState {
	class MainMenuState final : public StateEngine::IState, public Network::IMainMenuCallback {
		Core::Engine &m_Engine;
		std::unique_ptr<Network::IPacketHandler> m_PacketHandler;

	public: // Initialization/Uninitialization
		MainMenuState(Core::Engine &engine);
		~MainMenuState();

	public: // Network Callback Functions
		void ReceivedRequestAccepted();

	public: // Game Loop
		void Update(float delta);
		void Render(float delta);
	};
}