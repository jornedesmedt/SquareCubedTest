#include "Player.h"

#include "Agents.h"

#include <ClientBase/INetwork.h>
#include <ClientBase/INetworkFactory.h>
#include <ClientBase/IPlayerDispatcher.h>
#include <ClientBase/IPacketHandler.h>
#include <ClientBase/IInput.h>
#include <ClientBase/ICamera.h>

namespace GameState {
	// Initialization/Uninitialization
	Player::Player(Utils::Logger logger, Agents &agents, Network::INetwork &network, Input::IInput &input, Graphics::ICamera &camera) :
		m_Logger(logger),
		m_Dispatcher(network.GetFactory().CreatePlayerDispatcher()),
		m_Agents(agents),
		m_Agent(nullptr),
		m_Network(network),
		m_PacketHandler(m_Network.GetFactory().CreatePlayerHandler(*this)),
		m_Input(input),
		m_Camera(camera),
		m_CameraPosition(camera.GetPosition()),
		m_CameraSize(camera.GetSize()),
		m_Deadzone(0.4f),

		m_Speed(2)
	{
		m_Network.Attach(*m_PacketHandler);
	}

	// Because of the unique_ptr being defined with an incomplete type
	// the destructor has to be implemented in the .cpp file.
	Player::~Player() {
		m_Network.Detach(*m_PacketHandler);
	}

	// Network Callback Functions

	void Player::ReceivedSpawnPlayer(unsigned int agentId) {
		m_Agent = new PlayerAgent(agentId);
		m_Agents.AddAgent(m_Agent);
		m_Logger.LogInfo("Player Spawned");
	}

	// Game Loop

	void Player::Update(float delta) {
		if (m_Agent != nullptr) {
			Input::AxisDesc inpVal = m_Input.GetMovementAxis();
			if (inpVal.Any) {		
				// Change Character Position
				m_Agent->Position.X += inpVal.Scaled.X * delta * m_Speed;
				m_Agent->Position.Y += inpVal.Scaled.Y * delta * m_Speed;

				// Rotate Character
				m_Agent->Rotation = inpVal.Angle;

				// Send Position To Server
				m_Dispatcher->SendPlayerPos(m_Agent->Position.X, m_Agent->Position.Y, m_Agent->Rotation.Radians);			

				double xOffset = m_CameraSize.X / 2 * m_Deadzone;
				double yOffset = m_CameraSize.Y / 2 * m_Deadzone;
				double leftMax = m_Agent->Position.X - xOffset;
				double rightMax = m_Agent->Position.X + xOffset;
				double downMax = m_Agent->Position.Y - yOffset;
				double upMax = m_Agent->Position.Y + yOffset;

				if (m_CameraPosition.X < leftMax)
					m_CameraPosition.X = leftMax;
				if (m_CameraPosition.X > rightMax)
					m_CameraPosition.X = rightMax;
				if (m_CameraPosition.Y < downMax)
					m_CameraPosition.Y = downMax;
				if (m_CameraPosition.Y > upMax)
					m_CameraPosition.Y = upMax;
			}
		}
	}
}