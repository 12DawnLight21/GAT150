#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace umbra
{
	Logger g_logger(LogLevel::Info, &std::cout);

	bool Logger::Log(LogLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case LogLevel::Info:
			*m_ostream << "INFO: ";
			break;
		case LogLevel::Warning:
			*m_ostream << "WARNING: ";
			break;
		case LogLevel::Error:
			*m_ostream << "ERROR: ";
			break;
		case LogLevel::Assert:
			*m_ostream << "ASSERT: ";
			break;
		default:
			break;
		}

		*m_ostream << getFileName(filename) << "(" << line << ")\n";

		return true;
	}
}