#pragma once

#include "IAgent.h"

namespace Agents {
	class BasicAgent : public IAgent {
		Vector2d m_Position;
		float m_Rotation;

	public:
		virtual ~BasicAgent() {}

		Vector2d& GetPosition() { return m_Position; }
		void SetPosition(Vector2d position) {
			m_Position = position;
		}
		void SetPosition(double x, double y) {
			m_Position.X = x;
			m_Position.Y = y;
		}

		float GetRotation() { return m_Rotation; }
		void SetRotation(float rot) { m_Rotation = rot; }
	};
}