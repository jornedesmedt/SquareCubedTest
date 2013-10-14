#include "LoggingManager.h"
#include "Logger.h"

namespace Utils {
	LoggingManager::LoggingManager() :
		m_Minimum(LoggingLevel::Highlight),
		m_Log("../Logs/Client.log")
	{ }

	LoggingManager::~LoggingManager() {
		try {
			m_Log.close();
		}
		catch (...) {
			// We don't want an exception to go uncatched in the deconstructor
		}
	}

	Logger LoggingManager::CreateLogger(const char* className) {
		return Logger(className, this);
	}

	void LoggingManager::SetMinimumLevel(LoggingLevel level) {
		m_Minimum = level;
	}

	void LoggingManager::Log(const char* className, const char* message, LoggingLevel loggingLevel, const unsigned int bufferSize) {
		// Create a Message
		char *buff = new char[bufferSize];
		sprintf_s(buff, bufferSize, "[%s] [%s] %s", LevelToString(loggingLevel), className, message);

		// Output it to the File and the Console
		if (loggingLevel >= m_Minimum)
			m_Log << buff << std::endl;
		std::cout << buff << std::endl;
	}

	const char* LoggingManager::LevelToString(LoggingLevel loggingLevel) {
		switch (loggingLevel) {
		case LoggingLevel::Info:
			return "Info";
		case LoggingLevel::Highlight:
			return "Highlight";
		case LoggingLevel::Warning:
			return "Warning";
		case LoggingLevel::Error:
			return "Error";
		}

		// Should never happen unless someone adds a new level
		return "INVALID";
	}
}