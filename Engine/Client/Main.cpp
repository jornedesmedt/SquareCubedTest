#include <ClientBase/Engine.h>
#include <ClientBase/IContent.h>
#include <ClientBase/IContext.h>
#include <ClientBase/IGraphics.h>
#include <ClientBase/IInput.h>
#include <ClientBase/INetwork.h>
#include <ClientBase/IStateEngine.h>

#include <DefaultContent/DefaultContentLoader.h>
#include <GLFWContext/GLFWContextLoader.h>
#include <OpenGLGraphics/OpenGLGraphicsLoader.h>
#include <DefaultInput/DefaultInputLoader.h>
#include <RakNetNetwork/RakNetNetworkLoader.h>
#include <DefaultStateEngine/DefaultStateEngineLoader.h>

#include <MainMenuState/MainMenuStateSwitcher.h>

// These headers don't follow the new design rules yet
#include <CommonLib/LoggingManager.h>

int main(int argc, char* args [])
{
	// Initialize Logger
	Utils::ILoggingManager *loggingManager = new Utils::LoggingManager();
	Utils::Logger logger = loggingManager->CreateLogger("Loader");

	logger.LogHighlight("Initializing all engine modules...");

	// Initialize Engine
	Core::Engine engine(loggingManager);
	
	// Set up Content Module
	Content::IContent *content = DefaultContent::LoadContent();
	engine.SetContent(content);

	// Set up Context Module
	Context::IContext *context = GLFWContext::LoadContext();
	engine.SetContext(context);

	// Set up Graphics Module
	Graphics::IGraphics *graphics = OpenGLGraphics::LoadGraphics(context->GetMainWindow(), *content);
	engine.SetGraphics(graphics);

	// Set up Input Module
	Input::IInput *input = DefaultInput::LoadInput(*context);
	engine.SetInput(input);

	// Set up Network Module
	Network::INetwork *network = RakNetNetwork::LoadNetwork(loggingManager->CreateLogger("Network"));
	engine.SetNetwork(network);

	// Set up State Engine
	StateEngine::IStateEngine *stateEngine = DefaultStateEngine::LoadStateEngine(engine);
	engine.SetStateEngine(stateEngine);

	logger.LogHighlight("All engine modules initialized!");
	logger.LogHighlight("Initializing default state...");

	// Set Default State
	MainMenuState::ImmediateSwitchToState(*stateEngine);

	logger.LogHighlight("Default state initialized!");

	// Run Engine
	engine.Execute();
}