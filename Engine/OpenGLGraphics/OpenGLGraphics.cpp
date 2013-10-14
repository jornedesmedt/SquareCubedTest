#include "OpenGLGraphics.h"
#include "OpenGLGraphicsLoader.h"

#include <ClientBase/IWindow.h>

#include <CommonLib/Exception.h>

#include "GLheaders.h"
#include "ILheaders.h"

namespace OpenGLGraphics {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	Graphics::IGraphics* LoadGraphics(Context::IWindow &window, Content::IContent &content) { return new OpenGLGraphics(window, content); }

	OpenGLGraphics::OpenGLGraphics(Context::IWindow &window, Content::IContent &content) :
		m_Window(window),
		m_Factory(content),
		m_MainCamera(Vector2i(1024, 768))
	{
		// Default Camera Size
		m_MainCamera.SetHeight(10);

		// OpenGL Settings
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		// Activate Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLenum glError = glGetError();
		if (glError != GL_NO_ERROR) {
			std::string msg = "Error initializing OpenGL: ";
			msg += (char*) gluErrorString(glError);
			throw Exception(msg);
		}

		// Initialize DevIL
		ilInit();
		ilClearColour(255, 255, 255, 000);
		ILenum ilError = ilGetError();
		if (ilError != IL_NO_ERROR) {
			std::string msg = "Error initializing DevIL: ";
			msg += iluErrorString(ilError);
			throw Exception(msg);
		}
	}

	OpenGLGraphics::~OpenGLGraphics() {
	}

	// Property Accessors

	Graphics::ICamera& OpenGLGraphics::GetMainCamera() { return m_MainCamera; }

	// Utility Functions

	Graphics::IGraphicsFactory& OpenGLGraphics::GetFactory() { return m_Factory; }

	void OpenGLGraphics::Push() { glPushMatrix(); }
	void OpenGLGraphics::Pop() { glPopMatrix(); }
	void OpenGLGraphics::Translate(double x, double y) { glTranslated(x, y, 0); }
	void OpenGLGraphics::TranslateLayer(double z) { glTranslated(0, 0, z); }
	void OpenGLGraphics::Rotate(float rot) { glRotated(rot, 0, 0, 1); }

	void OpenGLGraphics::RenderTest() {
		// Render Quad
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.0f);
		glEnd();
	}

	// Game Loop

	void OpenGLGraphics::BeginRender() {
		// Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set the Projection Matrix based on the Main Camera
		Vector2d size = m_MainCamera.GetSize();
		glOrtho(
			-(size.X / 2),
			size.X / 2,
			-(size.Y / 2),
			size.Y / 2,
			0.0, 10.0); // Make sure everything behind the cam clips away
		// Note: zFar goes in the negative z direction

		// Translate and Rotate the Camera
		Vector3d rot = m_MainCamera.GetRotation();
		glRotated(-rot.X, 1, 0, 0);
		glRotated(-rot.Y, 0, 1, 0);
		glRotated(-rot.Z, 0, 0, 1);
		Vector3d pos = m_MainCamera.GetPosition();
		glTranslated(-pos.X, -pos.Y, -pos.Z);

		// Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Clear the Buffer
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0);
	}

	void OpenGLGraphics::EndRender() {
		m_Window.SwapBuffer();
	}
}