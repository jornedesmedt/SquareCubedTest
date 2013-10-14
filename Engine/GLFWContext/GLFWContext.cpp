#include "GLFWContext.h"
#include "GLFWContextLoader.h"

#include "GLFWWindow.h"

#include <CommonLib/Exception.h>

#include <GLFW/glfw3.h>

namespace GLFWContext {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	Context::IContext* LoadContext() { return new GLFWContext(); }

	// Initialization/Uninitialization

	GLFWContext::GLFWContext() {
		// Initialize GLFW
		if (!glfwInit())
			throw Exception("GLFW failed to initialize.");

		// Create Window
		m_Window = std::unique_ptr<GLFWWindow>(new GLFWWindow(1024, 768));
		
		// Set OpenGL Context
		m_Window->MakeContexCurrent();
	}

	GLFWContext::~GLFWContext() {
		// This has to be done before glfwTerminate
		m_Window.reset();

		glfwTerminate();
	}

	// Property Accessors

	Context::IWindow& GLFWContext::GetMainWindow() { return *m_Window; }

	// Input Handling

	Input::KeyID GLFWContext::GetKeyId(unsigned char key) {
		// Make sure it's lowercase
		if (key >= 'A' || key <= 'Z')
			key -= ('A' - 'a');

		if (key >= 'a' && key <= 'z') {
			static const int diff = 'a' - GLFW_KEY_A;
			return key - diff;
		}
		else
			throw Exception("Cannot resolve invalid key character.");
	}

	// Game Loop

	void GLFWContext::PollEvents() {
		glfwPollEvents();
	}
}