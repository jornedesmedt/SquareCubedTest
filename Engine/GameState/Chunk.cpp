#include "Chunk.h"

namespace GameState {
	Chunk::Chunk(int x, int y) :
		X(x),
		Y(y),
#pragma warning( disable : 4351 ) // New behavior warning
		Terrain()
	{}
}