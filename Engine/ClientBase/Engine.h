#pragma once

#include <CommonLib/Logger.h>

#include <memory>

namespace Content { class IContent; }
namespace Context { class IContext; }
namespace Graphics { class IGraphics; }
namespace Input { class IInput; }
namespace Network { class INetwork; }
namespace StateEngine { class IStateEngine; }
namespace Utils { class ILoggingManager; }

namespace Core {
	class Engine final {
		Utils::Logger m_Logger;

	public: // Initialization/Uninitialization
		Engine(Utils::ILoggingManager *loggingManager);

	private: // Modules
		std::unique_ptr<Utils::ILoggingManager> m_LoggingManager;
		std::unique_ptr<Content::IContent> m_Content;
		std::unique_ptr<Context::IContext> m_Context;
		std::unique_ptr<Graphics::IGraphics> m_Graphics;
		std::unique_ptr<Input::IInput> m_Input;
		std::unique_ptr<Network::INetwork> m_Network;
		std::unique_ptr<StateEngine::IStateEngine> m_StateEngine;

	public: // Module Setters
		/// <summary>Sets the Content Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="content">The Content Module</param>
		void SetContent(Content::IContent *content);

		/// <summary>Sets the Context Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="context">The Context Module</param>
		void SetContext(Context::IContext *context);

		/// <summary>Sets the Graphics Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="graphics">The Graphics Module</param>
		void SetGraphics(Graphics::IGraphics *graphics);

		/// <summary>Sets the Input Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="input">The Input Module</param>
		void SetInput(Input::IInput *input);

		/// <summary>Sets the Network Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="network">The Network Module</param>
		void SetNetwork(Network::INetwork *network);

		/// <summary>Sets the State Engine Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="stateEngine">The State Engine Module</param>
		void SetStateEngine(StateEngine::IStateEngine *stateEngine);

	public: // Module Accessors
		/// <summary>Gets the Logging Manager</summary>
		/// <returns>The Logging Manager</returns>
		Utils::ILoggingManager& GetLoggingManager();

		/// <summary>Gets the Content Module</summary>
		/// <returns>The Content Module</returns>
		Content::IContent& GetContent();

		/// <summary>Gets the Context Module</summary>
		/// <returns>The Context Module</returns>
		Context::IContext& GetContext();

		/// <summary>Gets the Graphics Module</summary>
		/// <returns>The Graphics Module</returns>
		Graphics::IGraphics& GetGraphics();

		/// <summary>Gets the Input Module</summary>
		/// <returns>The Input Module</returns>
		Input::IInput& GetInput();

		/// <summary>Gets the Network Module</summary>
		/// <returns>The Network Module</returns>
		Network::INetwork& GetNetwork();

		/// <summary>Gets the State Engine Module</summary>
		/// <returns>The State Engine Module</returns>
		StateEngine::IStateEngine& GetStateEngine();

	public: // Game Loop
		/// <summary>Executes this Instance</summary>
		void Execute();
	};
}