#include "GameState.h"
#include "GameStateSwitcher.h"

#include <ClientBase/Engine.h>
#include <ClientBase/IContent.h>
#include <ClientBase/IGraphics.h>
#include <ClientBase/IGraphicsFactory.h>
#include <ClientBase/ITexture2D.h>
#include <ClientBase/ITileArray.h>
#include <ClientBase/ICamera.h>
#include <ClientBase/IStateEngine.h>
#include <ClientBase/INetwork.h>
#include <ClientBase/INetworkFactory.h>
#include <ClientBase/IGameDispatcher.h>

#include <CommonLib/LoggingManager.h>

#include <string>

namespace GameState {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	void SwitchToState(StateEngine::IStateEngine &stateEngine) { stateEngine.SwitchState<GameState>(); }
	void ImmediateSwitchToState(StateEngine::IStateEngine &stateEngine) { stateEngine.ImmediateSwitchState<GameState>(); }

	GameState::GameState(Core::Engine &engine) :
		m_Engine(engine),
		m_Dispatcher(m_Engine.GetNetwork().GetFactory().CreateGameDispatcher()),
		
		m_World(engine.GetGraphics().GetFactory()),
		m_Agents(m_Engine.GetNetwork()),
		m_Player(m_Engine.GetLoggingManager().CreateLogger("Player"), m_Agents, m_Engine.GetNetwork(), m_Engine.GetInput(), m_Engine.GetGraphics().GetMainCamera()),
		
		m_AgentTexture(m_Engine.GetGraphics().GetFactory().GetTexture2D("../Content/player.png")),
		m_TileTextures(m_Engine.GetGraphics().GetFactory().GetTileArray("../Content/Tiles/tiles.scta"))
	{
		// Set Camera Size
		m_Engine.GetGraphics().GetMainCamera().SetHeight(14);

		// Done Loading, Spawn the Player
		m_Dispatcher->SpawnPlayer();
	}

	GameState::~GameState() {
		// Free all Content
		m_Engine.GetContent().ClearContent();
	}

	void GameState::Update(float delta) {
		m_Player.Update(delta);
	}

	void GameState::Render(float delta) {
		// Data for placeholder lambdas
		Graphics::IGraphics &graphics = m_Engine.GetGraphics();
		Graphics::ITexture2D &agentTexture = m_AgentTexture;
		Graphics::ITileArray &tileTextures = m_TileTextures;

		// Render Tiles
		m_World.RenderTiles([&graphics, &tileTextures](int x, int y, unsigned int id) {
			graphics.Push();
			graphics.Translate(x, y);
			tileTextures.GetTexture(id).Render(0, 0, 1, 1);
			graphics.Pop();
		});

		// Render Objects
		m_World.RenderObjects();

		// Render Agents
		m_Agents.Render([&graphics, &agentTexture](double x, double y, float rot) {
			graphics.Push();
			graphics.Translate(x, y);
			graphics.Rotate(rot);
			agentTexture.Render(-0.4, -0.4, 0.8, 0.8);
			graphics.Pop();
		});

		// Render Walls
		m_World.RenderWalls();
	}
}