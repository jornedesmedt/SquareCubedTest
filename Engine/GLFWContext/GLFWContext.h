#pragma once

#include <ClientBase/IContext.h>

#include <memory>

namespace GLFWContext {
	class GLFWWindow;

	class GLFWContext final : public Context::IContext {
	public: // Initialization/Uninitialization
		GLFWContext();
		~GLFWContext();

	private: // Properties
		std::unique_ptr<GLFWWindow> m_Window;

	public: // Property Accessors
		Context::IWindow& GetMainWindow();

	public: // Input Handling
		Input::KeyID GetKeyId(unsigned char key);

	public: // Game Loop
		void PollEvents();
	};
}