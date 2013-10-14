#pragma once

namespace Graphics {
	class ITexture2D {
	public: // Initialization/Uninitialization
		virtual ~ITexture2D() {}

	public: // Render Functions
		virtual void Render(double x, double y, double w, double h) = 0;
	};
}