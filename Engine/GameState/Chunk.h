#pragma once

namespace GameState {
	struct Chunk final {
		const static int CHUNK_MAX_SIZE = 32; // int instead of usigned int to avoid problems with calculations
		int X, Y;
		unsigned int Terrain[CHUNK_MAX_SIZE][CHUNK_MAX_SIZE];

		Chunk(int x, int y);
	};
}