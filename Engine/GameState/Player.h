#pragma once

#include "AgentTypes.h"

#include <ClientBase/IPlayerCallback.h>
#include <CommonLib/Logger.h>


#include <memory>

namespace Network {
	class INetwork;
	class IPacketHandler;
	class IPlayerDispatcher;
}

namespace Input {
	class IInput;
}

namespace Graphics {
	class ICamera;
}

namespace GameState {
	class Agents;

	class Player final : Network::IPlayerCallback {
		// Logger
		Utils::Logger m_Logger;

		// Internal Components
		Agents &m_Agents;
		Agent *m_Agent;		

		Network::INetwork &m_Network;
		std::unique_ptr<Network::IPacketHandler> m_PacketHandler;
		std::unique_ptr<Network::IPlayerDispatcher> m_Dispatcher;

		Input::IInput &m_Input;
		Graphics::ICamera &m_Camera;

	private: // Player Properties
		float m_Speed;
		float m_Deadzone;

	private: // Camera Properties
		Vector3d& m_CameraPosition;
		Vector2d& m_CameraSize;

	public: // Initialization/Uninitialization
		Player(Utils::Logger logger, Agents &agents, Network::INetwork &factory, Input::IInput &input, Graphics::ICamera &maincam);
		~Player();

	public: // Network Callback Functions
		void ReceivedSpawnPlayer(unsigned int agentId);
		
	public: // Game Loop
		void Update(float delta);
	};
}