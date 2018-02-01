#pragma once

#include <memory>
#include <vector>

class AbstractFileSystem;

class FileManager
{
public:
	// initializes filesystem with specified FileSystem in template argument
	template <class T, class... Args>
	static void init(Args&&... args)
	{
		static_assert(std::is_base_of<AbstractFileSystem, T>::value,
			"Template parameter of FileManager::init must be a child of AbstractFileSystem class");
		
		m_fileSystem = std::make_unique<T>(std::forward(args)...);
	}

	static void close();

	static std::vector<char> open(const std::string& filename);

private:
	static std::unique_ptr<AbstractFileSystem> m_fileSystem;
};


class AbstractFileSystem
{
public:
	virtual ~AbstractFileSystem() {}

	virtual std::vector<char> open(const std::string& filename) const = 0;
};

// Filesystem which uses simple files
class DefaultFileSystem : public AbstractFileSystem
{
public:
	DefaultFileSystem(const std::string& dataFolder = "data/");

	std::vector<char> open(const std::string& filename) const override;

private:
	std::string m_dataFolder;
};
