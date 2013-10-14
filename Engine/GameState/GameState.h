#pragma once

#include <ClientBase/IState.h>

#include "Agents.h"
#include "Player.h"
#include "World.h"

namespace Network {
	class IPacketHandler;
	class IGameDispatcher;
}

namespace Graphics {
	class ITexture2D;
	class ITileArray;
}

namespace GameState {
	class GameState final : public StateEngine::IState {
		Core::Engine &m_Engine;
		std::unique_ptr<Network::IGameDispatcher> m_Dispatcher;

		World m_World;
		Agents m_Agents;
		Player m_Player;

		Graphics::ITexture2D &m_AgentTexture;
		Graphics::ITileArray &m_TileTextures;

	public: // Initialization/Uninitialization
		GameState(Core::Engine &engine);
		~GameState();

	public: // Game Loop
		void Update(float delta);
		void Render(float delta);
	};
}