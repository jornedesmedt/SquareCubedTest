#include "../WorldServerLib/Server.h"
#include <crossos.h>
#include <Exception.h>

int main(int argc, char* args [])
{
#ifdef _DEBUG
	// Initialize Engine
	Core::Server server;

	// Run Engine
	return server.Run();
#else
	try {
		// Initialize Engine
		Core::Server server;

		// Run Engine
		return server.Run();
	}
	catch (Exception e) {
		ErrorMessageBox(e.what(), e.Message.c_str());
	}
	catch (Exception* e) {
		std::string msg("Developer threw a pointer to an exception instead of just an exception! Exception Message: ");
		msg += e->Message;
		ErrorMessageBox(e->what(), msg.c_str());
	}
	catch (std::exception e) {
		ErrorMessageBox("Unhandled std::exception!", e.what());
	}

	// If we reach this something went wrong so return -1 exit code
	return -1;
#endif
}