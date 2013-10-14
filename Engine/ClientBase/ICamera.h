#pragma once

#include <CommonLib/postypes.h>
#include <CommonLib/Events.h>

namespace Graphics {
	class ICamera {
	public:
		virtual ~ICamera() {}

	public: // Events
		Utils::Event<Utils::EmptyEventArgs> OnResize;

	public: // Position Accessors
		/// <summary>Sets the Position</summary>
		/// <param name="x">X Coordinate</param>
		/// <param name="y">Y Coordinate</param>
		/// <param name="z">Z Coordinate</param>
		virtual void SetPosition(double x, double y, double z) = 0;

		/// <summary>Sets the Position</summary>
		/// <param name="position">The new Position</param>
		virtual void SetPosition(Vector3d position) = 0;

		/// <summary>Sets the Position</summary>
		/// <param name="x">X Coordinate</param>
		/// <param name="y">Y Coordinate</param>
		virtual void SetPosition(double x, double y) = 0;

		/// <summary>Sets the Position</summary>
		/// <param name="position">The new Position</param>
		virtual void SetPosition(Vector2d position) = 0;

		/// <summary>Gets the Position</summary>
		/// <returns>Reference to the Position</returns>
		virtual Vector3d& GetPosition() = 0;

	public: // Size Accessors
		/// <summary>Gets the Size</summary>
		/// <returns>Reference to the Size</returns>
		virtual Vector2d& GetSize() = 0;

	public: // Size Helper Functions
		/// <summary>Sets the height and calculates the width using the aspect ratio.</summary>
		/// <param name="height">The new Height</param>
		virtual void SetHeight(double height) = 0;

		/// <summary>Sets the width and calculates the height using the aspect ratio.</summary>
		/// <param name="width">The new Width</param>
		virtual void SetWidth(double width) = 0;
	};
}