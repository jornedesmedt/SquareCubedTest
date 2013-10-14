#include "GLFWWindow.h"

#include <CommonLib/Exception.h>

#include <GLFW/glfw3.h>

namespace GLFWContext {
	// Static Callback Functions

	std::function<void(int, int, int, int)> GLFWWindow::sm_CallbackFunc;

	void GLFWWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		sm_CallbackFunc(key, scancode, action, mods);
	}

	// Initialization/Uninitialization

	GLFWWindow::GLFWWindow(int x, int y) {
		// Set Window Hints
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		// Create Window
		m_Window = glfwCreateWindow(
			x, y,
			"SquareCubed Client",
			NULL,
			NULL);
		if (!m_Window)
			throw Exception("Failed to create window.");
	}

	GLFWWindow::~GLFWWindow() {
		glfwDestroyWindow(m_Window);
	}

	// Property Accessors

	bool GLFWWindow::HasCloseRequest() { return (glfwWindowShouldClose(m_Window) & 1); }

	// Utility Functions

	void GLFWWindow::MakeContexCurrent() { glfwMakeContextCurrent(m_Window); }
	void GLFWWindow::SwapBuffer() { glfwSwapBuffers(m_Window); }

	void GLFWWindow::SetKeyCallback(std::function<void(int, int, int, int)> callback) {
		sm_CallbackFunc = callback;
		glfwSetKeyCallback(m_Window, KeyCallback);
	}
}