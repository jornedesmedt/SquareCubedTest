#include "World.h"

#include <ClientBase/IGraphicsFactory.h>
#include <ClientBase/ITileRenderer.h>

namespace GameState {
	// Initialization/Uninitialization

	World::World(Graphics::IGraphicsFactory &factory) :
		m_TileProvider(),
		m_TileRenderer(factory.CreateTileRenderer())
	{
	}

	World::~World() {}

	// Rendering Functions

	void World::RenderTiles(TileRenderFunc func) {
		std::list<Chunk>& tiles = m_TileProvider.GetChunks();
		for(Chunk& chunk : tiles) {
			for (unsigned int x = 0; x < Chunk::CHUNK_MAX_SIZE; x++) {
				for (unsigned int y = 0; y < Chunk::CHUNK_MAX_SIZE; y++) {
					func(
						chunk.X * Chunk::CHUNK_MAX_SIZE + x,
						chunk.Y * Chunk::CHUNK_MAX_SIZE + y,
						chunk.Terrain[x][y]
					);
				}
			}
		}
	}

	void World::RenderObjects() {}
	void World::RenderWalls() {}
}