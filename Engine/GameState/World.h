#pragma once

#include "TileProvider.h"

#include <memory>
#include <functional>

namespace Graphics {
	class IGraphicsFactory;
	class ITileRenderer;
}

namespace GameState {
	class World final {
	public: // Data Providers
		TileProvider m_TileProvider;
		std::unique_ptr<Graphics::ITileRenderer> m_TileRenderer;

	public: // Initialization/Uninitialization
		World(Graphics::IGraphicsFactory &factory);
		~World();

	public: // Rendering Functions
		typedef std::function<void(int, int, unsigned int)> TileRenderFunc;
		void RenderTiles(TileRenderFunc func);
		void RenderObjects();
		void RenderWalls();
	};
}