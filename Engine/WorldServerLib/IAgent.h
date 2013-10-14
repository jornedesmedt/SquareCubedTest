#pragma once

#include <postypes.h>

namespace Agents {
	class IAgent {
		static unsigned int nextId;
	public:
		const int ID;

		IAgent() : ID(nextId) { nextId++; }
		virtual ~IAgent() {}

		virtual Vector2d& GetPosition() = 0;
		virtual void SetPosition(Vector2d position) = 0;
		virtual void SetPosition(double x, double y) = 0;

		virtual float GetRotation() = 0;
		virtual void SetRotation(float rot) = 0;
	};
}