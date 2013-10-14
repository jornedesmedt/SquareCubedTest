#pragma once

#include <ClientBase/ITexture2D.h>
#include <ClientBase/IContentBase.h>

#include <CommonLib/postypes.h>

#include <string>

namespace OpenGLGraphics {
	class Texture2D final : public Graphics::ITexture2D, public Content::IContentBase {
	public: static const char* GetType();

	public: // Initialization/Uninitialization
		Texture2D(const std::string &path);
		~Texture2D();

	private: // Properties
		Vector2ui m_Size;
		unsigned int m_TextureID;

	private: // Internal Utility Functions
		void LoadTextureFromPixels32(unsigned int* pixels, Vector2ui size);

	public: // Render Functions
		void Render(double x, double y, double w, double h);
	};
}