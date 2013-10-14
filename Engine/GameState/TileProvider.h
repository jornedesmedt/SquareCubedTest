#pragma once

#include "Chunk.h"

#include <list>

namespace GameState {
	class TileProvider final {
		std::list<Chunk> m_LoadedChunks;

	public:
		TileProvider();

		std::list<Chunk>& GetChunks();
		void TestSetTile(int cx, int cy, int x, int y, unsigned int id);
	};
}