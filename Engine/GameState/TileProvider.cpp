#include "TileProvider.h"

namespace GameState {
	TileProvider::TileProvider() :
		m_LoadedChunks()
	{
		m_LoadedChunks.push_back(Chunk(0, 0));
		m_LoadedChunks.push_back(Chunk(-1, 0));
		m_LoadedChunks.push_back(Chunk(0, -1));
		m_LoadedChunks.push_back(Chunk(-1, -1));

		TestSetTile(0, 0, 0, 0, 1);
		TestSetTile(0, 0, 1, 1, 1);
	}

	std::list<Chunk>& TileProvider::GetChunks() {
		return m_LoadedChunks;
	}

	void TileProvider::TestSetTile(int cx, int cy, int x, int y, unsigned int id) {
		for (Chunk& chunk : m_LoadedChunks) {
			if (chunk.X == cx && chunk.Y == cy) {
				chunk.Terrain[x][y] = id;
				return;
			}
		}
	}
}