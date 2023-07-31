#pragma once
#include <filesystem> //apart of new C++
#include <string>

//dont use using namespace std in headers, can get confusing
//forces anyone who uses the header to ALSO use the namespace std


namespace umbra
{
	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& path); //:: = scope operator

	bool fileExists(const std::filesystem::path& path); //path& is a reference, which copies the variable being used?
	bool getFileSize(const std::filesystem::path& path, size_t& size); //size_t is a unsigned long long, used in modern coding
	bool readFile(const std::filesystem::path& path, std::string& buffer); //returns bool so it acts as a fail safe // buffer - a block of data
}