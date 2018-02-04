#include "MapLoader.h"

#include "ResourceManager.h"
#include "TextureFactory.h"
#include "Log.h"

using json = nlohmann::json;

bool MapLoader::load(const nlohmann::json& data, Map& map)
{
	if (!processMapNode(data, map)) {
		Log::write("Error: unable to load map");
		return false;
	}

	// TODO: init rendering from parsed data

	return true;
}

bool MapLoader::processMapNode(const nlohmann::json & mapData, Map & map)
{
	if (!mapData.is_object()) {
		return false;
	}

	// loading basic map properties
	{
		json mapWidthData = mapData.value("width", json());
		json mapHeightData = mapData.value("height", json());
		if (mapWidthData.is_number_unsigned() && mapHeightData.is_number_unsigned()) {
			map.m_size = uvec2(mapWidthData.get<unsigned int>(), mapHeightData.get<unsigned int>());
		}
		else {
			return false;
		}

		json tileWidthData = mapData.value("tilewidth", json());
		json tileHeightData = mapData.value("tileheight", json());
		if (tileWidthData.is_number_unsigned() && tileHeightData.is_number_unsigned()) {
			map.m_tileSize = uvec2(tileWidthData.get<unsigned int>(), tileHeightData.get<unsigned int>());
		}
		else {
			return false;
		}

		json backgroundColorData = mapData.value("backgroundcolor", json());
		if (backgroundColorData.is_string()) {
			map.m_backgroundColor = math::colorFromHex(backgroundColorData.get<std::string>());
		}
	}

	// loading custom map properties
	{
		json propertiesData = mapData.value("properties", json());
		if (propertiesData.is_object()) {
			map.m_properties = propertiesData;
		}
	}

	// loading map tilesets
	{
		json tilesetsData = mapData.value("tilesets", json());
		if (tilesetsData.is_array()) {
			for (const auto& tilesetData : tilesetsData) {
				MapTileset tileset;
				if (processTilesetNode(tilesetData, tileset)) {
					map.m_tilesets.push_back(tileset);
				}
				else {
					Log::write("Error: unable to load tileset");
					// return false;
				}
			}
		}
	}

	return true;
}

bool MapLoader::processTilesetNode(const nlohmann::json & tilesetData, MapTileset& tileset)
{
	if (!tilesetData.is_object()) {
		return false;
	}

	// loading basic tileset properties
	{
		json nameData = tilesetData.value("name", json());
		if (nameData.is_string()) {
			tileset.m_name = nameData.get<std::string>();
		}
		else {
			return false;
		}

		json imageData = tilesetData.value("image", json());
		if (imageData.is_string()) {
			tileset.m_imageFileName = imageData.get<std::string>();
			ResourceManager::bind<TextureFactory>(tileset.m_name + "_" + tileset.m_imageFileName, tileset.m_imageFileName);
		}

		json marginData = tilesetData.value("margin", json());
		if (marginData.is_number_integer()) {
			tileset.m_margin = marginData.get<int>();
		}

		json spacingData = tilesetData.value("spacing", json());
		if (spacingData.is_number_integer()) {
			tileset.m_spacing = spacingData.get<int>();
		}

		json tileWidthData = tilesetData.value("tilewidth", json());
		json tileHeightData = tilesetData.value("tileheight", json());
		if (tileWidthData.is_number_unsigned() && tileHeightData.is_number_unsigned()) {
			tileset.m_tileSize = uvec2(tileWidthData.get<unsigned int>(), tileHeightData.get<unsigned int>());
		}

		json firstGidData = tilesetData.value("firstgid", json());
		if (firstGidData.is_number_unsigned()) {
			tileset.m_firstGid = firstGidData.get<unsigned int>();
		}

		json tileCountData = tilesetData.value("tilecount", json());
		if (tileCountData.is_number_unsigned()) {
			tileset.m_tileCount = tileCountData.get<unsigned int>();
		}

		json columnCountData = tilesetData.value("columns", json());
		if (columnCountData.is_number_unsigned()) {
			tileset.m_columnCount = columnCountData.get<unsigned int>();
		}
	}

	// loading tile specific data
	{
		json tilesData = tilesetData.value("tiles", json());
		if (tilesData.is_object()) {
			for (nlohmann::json::const_iterator it = tilesData.begin(); it != tilesData.end(); ++it) {
				const json& tileData = it.value();

				MapTile tile;

				bool tileLoaded;
				try {
					tile.m_relativeGid = std::stoul(it.key());

					tileLoaded = processTileNode(tileData, tile);
				}
				catch (const std::invalid_argument&) {
					tileLoaded = false;
				}

				if (!tileLoaded) {
					Log::write("Error: unable to load tile information");
					// return false;
				}
			}
		}
	}

	return true;
}

bool MapLoader::processTileNode(const nlohmann::json & tileData, MapTile & tile)
{
	if (!tileData.is_object()) {
		return false;
	}

	json animationData = tileData.value("animation", json());
	if (animationData.is_array()) {
		std::vector<std::pair<unsigned int, unsigned int>> animation;

		if (!processAnimationNode(animationData, animation)) {
			Log::write("Error: unable to load tile animation");
			// return false;
		}
	}

	return true;
}

bool MapLoader::processAnimationNode(const nlohmann::json & animationData, std::vector<std::pair<unsigned int, unsigned int>>& animation)
{
	for (const auto& frameData : animationData) {
		if (frameData.is_object()) {
			json tileIdData = frameData.value("tileid", json());
			json durationData = frameData.value("duration", json());
			if (tileIdData.is_number_unsigned() && durationData.is_number_unsigned()) {
				animation.push_back(std::make_pair<unsigned int, unsigned int>(tileIdData.get<unsigned int>(), durationData.get<unsigned int>()));
			}
			else {
				Log::write(tileIdData.dump(), durationData.dump());
				return false;
			}
		}
		else {
			Log::write("frame is not an object");
			return false;
		}
	}

	return true;
}
