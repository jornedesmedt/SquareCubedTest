#include "OpenGLGraphicsFactory.h"

#include "TileRenderer.h"
#include "Texture2D.h"
#include "TileArray.h"

#include <ClientBase/IContent.h>

namespace OpenGLGraphics {
	// Initialization/Uninitialization

	OpenGLGraphicsFactory::OpenGLGraphicsFactory(Content::IContent &content) :
		m_Content(content)
	{
	}

	// Renderer Types

	Graphics::ITileRenderer* OpenGLGraphicsFactory::CreateTileRenderer() {
		return new TileRenderer();
	}

	// Content Types

	Graphics::ITexture2D& OpenGLGraphicsFactory::GetTexture2D(const std::string &path) {
		return m_Content.GetContent<Texture2D>(path);
	}

	Graphics::ITileArray& OpenGLGraphicsFactory::GetTileArray(const std::string &path) {
		return m_Content.GetContent<TileArray, Content::IContent&>(path, m_Content);
	}
}