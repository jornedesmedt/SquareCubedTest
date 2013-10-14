#pragma once

#include <CommonLib/postypes.h>

namespace Input {
	typedef unsigned int KeyID;

	struct AxisDesc final {
		Vector2f RawValues;

		// Useful Input Values
		bool Any;
		Vector2f Scaled;
		Anglef Angle;

		AxisDesc() :
			RawValues(),
			Scaled(),
			Angle()
		{}
	};

	class IInput {
	public: // Key Accessors
		virtual bool GetForwardKey() = 0;
		virtual bool GetBackwardKey() = 0;
		virtual bool GetLeftKey() = 0;
		virtual bool GetRightKey() = 0;

	public: // Complex Input Accessors
		virtual AxisDesc GetMovementAxis() = 0;

	public:
		virtual ~IInput() {}
	};
}