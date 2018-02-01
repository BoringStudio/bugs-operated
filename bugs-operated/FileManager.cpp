#include "FileManager.h"

#include <fstream>

std::unique_ptr<AbstractFileSystem> FileManager::m_fileSystem = nullptr;

void FileManager::close()
{
	m_fileSystem.reset(nullptr);
}

std::vector<char> FileManager::open(const std::string & filename)
{
	if (m_fileSystem == nullptr) {
		throw std::runtime_error("Unable to open file: \"" + filename + "\". Filesystem wasn't initialized");
	}
	else {
		return m_fileSystem->open(filename);
	}
}


DefaultFileSystem::DefaultFileSystem(const std::string & dataFolder) :
	m_dataFolder(dataFolder)
{
}

std::vector<char> DefaultFileSystem::open(const std::string & filename) const
{
	std::ifstream file(m_dataFolder + filename, std::ios::binary);

	if (file.is_open()) {
		file.seekg(0, std::ios_base::end);
		std::streampos fileSize = file.tellg();

		std::vector<char> result(fileSize);

		file.seekg(0, std::ios_base::beg);
		file.read(&result[0], fileSize);

		return result;
	}
	else {
		throw std::runtime_error("Unable to open file: \"" + m_dataFolder + filename + "\". File is missing");
	}
}
