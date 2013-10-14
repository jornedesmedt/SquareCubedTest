#pragma once

namespace Core { class Engine; }
namespace StateEngine { class IStateEngine; }

namespace DefaultStateEngine {
	// Use this function to create a new DefaultStateEngine object without
	// including DefaultStateEngine.h (and the includes that come with it)
	StateEngine::IStateEngine* LoadStateEngine(Core::Engine &engine);
}