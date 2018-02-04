#include "MapFactory.h"

#include "FileManager.h"
#include "MapLoader.h"

MapFactory::MapFactory(const std::string & filename) :
	AbstractFactory(tag<Map>{}), m_data(nullptr),
	m_filename(filename)
{
}

void * MapFactory::load()
{
	if (m_data == nullptr) {
		std::unique_ptr<Map> map = std::make_unique<Map>();

		nlohmann::json mapData;

		{
			std::vector<char> data = FileManager::open(m_filename);
			mapData = nlohmann::json::parse(data.begin(), data.end());
		}
		
		MapLoader mapLoader;
		if (!mapLoader.load(mapData, *map)) {
			throw std::runtime_error("Unable to load map: \"" + m_filename + "\"");
		}

		m_data = std::move(map);
	}

	return m_data.get();
}

void MapFactory::clear()
{
	m_data.reset(nullptr);
}
