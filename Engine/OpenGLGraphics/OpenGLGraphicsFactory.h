#pragma once

#include <ClientBase/IGraphicsFactory.h>

namespace Content { class IContent; }

namespace OpenGLGraphics {
	class OpenGLGraphicsFactory final : public Graphics::IGraphicsFactory {
		Content::IContent &m_Content;

	public: // Initialization/Uninitialization
		OpenGLGraphicsFactory(Content::IContent &content);

	public: // Renderer Types
		Graphics::ITileRenderer* CreateTileRenderer();

	public: // Content Types
		Graphics::ITexture2D& GetTexture2D(const std::string &path);
		Graphics::ITileArray& GetTileArray(const std::string &path);
	};
}