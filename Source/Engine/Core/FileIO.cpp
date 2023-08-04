#include "FileIO.h"
#include "Logger.h"

#include <fstream>
#include <iostream>

namespace umbra
{
	std::string getFilePath()
	{
		return std::filesystem::current_path().string();
	}

	bool setFilePath(const std::filesystem::path& path)
	{
		std::error_code ec; //error code = ec cause convience i think
		std::filesystem::current_path(path, ec);

		return ec.value() == 0;
	}

	std::string getFileName(const std::filesystem::path& path)
	{
		return path.filename().string();
	}

	bool fileExists(const std::filesystem::path& path)
	{
		return std::filesystem::exists(path);
	}

	bool getFileSize(const std::filesystem::path& path, size_t& size)
	{
		std::error_code ec;
		size = std::filesystem::file_size(path, ec);

		return ec.value() == 0;
	}

	bool readFile(const std::filesystem::path& path, std::string& buffer)
	{
		if (!fileExists(path))
		{
			WARNING_LOG("File not loaded: " << path.string());
			return false;
		}

		size_t size; //we need this to expand the buffer
		if (!getFileSize(path, size)) return false;
		buffer.resize(size);
		
		//"older style" c++ coding
		std::ifstream stream(path); //could also just use fstream i think
		stream.read(buffer.data(), size); //.data returns the information as a pointer
		stream.close();

		return true;
	}
}