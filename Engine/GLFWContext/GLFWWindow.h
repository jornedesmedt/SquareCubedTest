#pragma once

#include <ClientBase/IWindow.h>

// Front-Declare GLFW Stuff
struct GLFWwindow;

namespace GLFWContext {
	class GLFWWindow final : public Context::IWindow {
	private: // Static Callback Functions
		static std::function<void(int, int, int, int)> sm_CallbackFunc;
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	public: // Initialization/Uninitialization
		GLFWWindow(int x, int y);
		~GLFWWindow();

	private: // Properties
		GLFWwindow* m_Window;

	public: // Property Accessors
		bool HasCloseRequest();

	public: // Utility Functions
		void MakeContexCurrent();
		void SwapBuffer();

		void SetKeyCallback(std::function<void(int, int, int, int)> callback);
	};
}