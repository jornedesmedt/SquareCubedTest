#pragma once

#include "../CommonLib/ILoggingManager.h"
#include "../CommonLib/LoggingManager.h"
#include "../CommonLib/Logger.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace Utils {
	class LoggingManagerMock : public ILoggingManager {
		// Class for Storing Internal Values
		struct LogMockEntry {
			LoggingLevel Level;
			std::string ClassName;
			std::string Message;
			LogMockEntry(LoggingLevel level, const char* className, const char* entry) :
				Level(level),
				ClassName(className),
				Message(entry)
			{}
		};

	public: // Public Members
		std::vector<LogMockEntry> LoggingBuffer;

	public: // Implementation
		~LoggingManagerMock(){}

		void SetMinimumLevel(Utils::LoggingLevel level) {}

		void Log(const char* className, const char* message, LoggingLevel loggingLevel, const unsigned int bufferSize) {
			LoggingBuffer.push_back(
				LogMockEntry(
					loggingLevel,
					className,
					message));
		}

		Logger CreateLogger(const char* className) { return Logger(className, this); }
	};

	TEST(Logging, LevelStringResolving) {
		// If any of these fail, make sure it's resolving correctly and if it is change/add values.
		// You might have your case blocks in the switch block in the wrong order.
		EXPECT_STREQ("Error", LoggingManager::LevelToString(LoggingLevel::Error)) << "LoggingLevel::ERROR Incorrectly Resolved";
		EXPECT_STREQ("Highlight", LoggingManager::LevelToString(LoggingLevel::Highlight)) << "LoggingLevel::HIGHLIGHT Incorrectly Resolved";
		EXPECT_STREQ("Info", LoggingManager::LevelToString(LoggingLevel::Info)) << "LoggingLevel::INFO Incorrectly Resolved";
		EXPECT_STREQ("INVALID", LoggingManager::LevelToString((LoggingLevel)39)) << "Bad Type Incorrectly Resolved";
		EXPECT_STREQ("Warning", LoggingManager::LevelToString(LoggingLevel::Warning)) << "LoggingLevel::WARNING Incorrectly Resolved";
	}

	TEST(Logging, LoggingMessages) {
		// Create Testing Data
		std::string className = "UnitTest";
		std::string infoMessage = "This is an info message!";
		std::string errorMessage = "This is an error message!";
		LoggingManagerMock mock;

		// Set up Data to Test
		Logger logger("UnitTest", &mock);
		logger.LogInfo(infoMessage.c_str());
		logger.LogError(errorMessage.c_str());
		logger.LogInfo(infoMessage.c_str());

		// Test Result Data
		ASSERT_EQ(3, mock.LoggingBuffer.size()) << "Incorrect Amount of Messages Logged";

		EXPECT_EQ(LoggingLevel::Info, mock.LoggingBuffer[0].Level) << "LoggingLevel 0 Incorrectly Logged";
		EXPECT_EQ(className, mock.LoggingBuffer[0].ClassName) << "ClassName 0 Incorrectly Logged";
		EXPECT_EQ(infoMessage, mock.LoggingBuffer[0].Message) << "Message 0 Incorrectly Logged";

		EXPECT_EQ(LoggingLevel::Error, mock.LoggingBuffer[1].Level) << "LoggingLevel 1 Incorrectly Logged";
		EXPECT_EQ(className, mock.LoggingBuffer[1].ClassName) << "ClassName 1 Incorrectly Logged";
		EXPECT_EQ(errorMessage, mock.LoggingBuffer[1].Message) << "Message 1 Incorrectly Logged";

		EXPECT_EQ(LoggingLevel::Info, mock.LoggingBuffer[2].Level) << "LoggingLevel 2 Incorrectly Logged";
		EXPECT_EQ(className, mock.LoggingBuffer[2].ClassName) << "ClassName 2 Incorrectly Logged";
		EXPECT_EQ(infoMessage, mock.LoggingBuffer[2].Message) << "Message 2 Incorrectly Logged";
	}

	TEST(Logging, LoggingComplexMessages) {
		// Create Testing Data
		std::string className = "UnitTest";
		LoggingManagerMock mock;

		// Set up Data to Test
		Logger logger("UnitTest", &mock);
		logger.LogInfo("This is a complex %s message!", "Info");
		logger.LogError("This is a complex %s message!", "Error");

		// Test Result Data
		EXPECT_EQ(LoggingLevel::Info, mock.LoggingBuffer[0].Level) << "LoggingLevel 0 Incorrectly Logged";
		EXPECT_EQ(className, mock.LoggingBuffer[0].ClassName) << "ClassName 0 Incorrectly Logged";
		EXPECT_EQ("This is a complex Info message!", mock.LoggingBuffer[0].Message) << "Message 0 Incorrectly Logged";

		EXPECT_EQ(LoggingLevel::Error, mock.LoggingBuffer[1].Level) << "LoggingLevel 1 Incorrectly Logged";
		EXPECT_EQ(className, mock.LoggingBuffer[1].ClassName) << "ClassName 1 Incorrectly Logged";
		EXPECT_EQ("This is a complex Error message!", mock.LoggingBuffer[1].Message) << "Message 1 Incorrectly Logged";

	}
}