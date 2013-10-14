#pragma once

#include <ClientBase/ICamera.h>

#include <CommonLib/postypes.h>

namespace OpenGLGraphics {
	class OpenGLCamera : public Graphics::ICamera {
		double m_AspectRatio;
		Vector3d m_Position;
		Vector2d m_Size;
		Vector3d m_Rotation;

	public:
		OpenGLCamera() :
			// Default Values
			m_Position(),
			m_Size(),
			m_Rotation(),
			// Can't have the aspect ratio at weird values, might cause problems
			m_AspectRatio(1)
		{
		}

		OpenGLCamera(Vector2i resolution)
			: OpenGLCamera()
		{
			SetAspectRatioByResolution(resolution);
		}

		void SetAspectRatio(double aspectRatio) { m_AspectRatio = aspectRatio; }
		void SetAspectRatioByResolution(Vector2i resolution) {
			m_AspectRatio = (double) resolution.X / (double) resolution.Y;
		}
		double GetAspectRatio() { return m_AspectRatio; }

		void SetPosition(double x, double y, double z) { m_Position.X = x; m_Position.Y = y; m_Position.Z = z; }
		void SetPosition(Vector3d position) { m_Position = position; }
		void SetPosition(double x, double y) { m_Position.X = x; m_Position.Y = y; }
		void SetPosition(Vector2d position) { m_Position.X = position.X; m_Position.Y = position.Y; }
		Vector3d& GetPosition() { return m_Position; }

		void SetWidth(double width) {
			m_Size.X = width;
			m_Size.Y = width / m_AspectRatio;
			OnResize.Invoke(Utils::NO_ARGS);
		}
		void SetHeight(double height) {
			m_Size.X = height * m_AspectRatio;
			m_Size.Y = height;
			OnResize.Invoke(Utils::NO_ARGS);
		}
		Vector2d& GetSize() { return m_Size; }

		void SetRotation(double x, double y, double z) { m_Rotation.X = x; m_Rotation.Y = y; m_Rotation.Z = z; }
		void SetRotation(Vector3d rotation) { m_Rotation = rotation; }
		Vector3d& GetRotation() { return m_Rotation; }
	};
}