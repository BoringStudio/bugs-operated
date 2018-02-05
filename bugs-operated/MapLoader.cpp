#include "MapLoader.h"

#include <list>

#include "ResourceManager.h"
#include "TextureFactory.h"
#include "Log.h"

using json = nlohmann::json;

bool MapLoader::load(const nlohmann::json& data, Map& map)
{
	MapInfo mapInfo;
	if (!processMapNode(data, mapInfo)) {
		Log::write("Error: unable to load map");
		return false;
	}

	// TODO: init rendering from parsed data

	return true;
}

bool MapLoader::processMapNode(const nlohmann::json & mapData, MapInfo & mapInfo)
{
	if (!mapData.is_object()) {
		return false;
	}

	// loading basic map properties
	{
		json mapWidthData = mapData.value("width", json());
		json mapHeightData = mapData.value("height", json());
		if (mapWidthData.is_number_unsigned() && mapHeightData.is_number_unsigned()) {
			mapInfo.size = uvec2(mapWidthData.get<unsigned int>(), mapHeightData.get<unsigned int>());
		}
		else {
			Log::write("Error: map must contain width and height");
			return false;
		}

		json tileWidthData = mapData.value("tilewidth", json());
		json tileHeightData = mapData.value("tileheight", json());
		if (tileWidthData.is_number_unsigned() && tileHeightData.is_number_unsigned()) {
			mapInfo.tileSize = uvec2(tileWidthData.get<unsigned int>(), tileHeightData.get<unsigned int>());
		}
		else {
			Log::write("Error: map must contain tilewidth and tileheight");
			return false;
		}

		json backgroundColorData = mapData.value("backgroundcolor", json());
		if (backgroundColorData.is_string()) {
			mapInfo.backgroundColor = math::colorFromHex(backgroundColorData.get<std::string>());
		}
	}

	// loading custom map properties
	{
		json propertiesData = mapData.value("properties", json());
		if (propertiesData.is_object()) {
			mapInfo.properties = propertiesData;
		}
	}

	// loading map tilesets
	{
		json tilesetsData = mapData.value("tilesets", json());
		if (tilesetsData.is_array()) {
			for (const auto& tilesetData : tilesetsData) {
				MapTilesetInfo tilesetInfo;
				if (processTilesetNode(tilesetData, tilesetInfo)) {
					mapInfo.tilesets.push_back(tilesetInfo);
				}
				else {
					Log::write("Error: unable to load tileset");
					// return false;
				}
			}
		}
	}

	// loading map layers
	{
		json layersData = mapData.value("layers", json());
		if (layersData.is_array()) {
			std::list<MapLayerInfo> groups;

			std::list<std::pair<const json*, json::const_iterator>> iterators;

			iterators.push_back(std::make_pair<const json*, json::const_iterator>(&layersData, layersData.begin()));

			while (!iterators.empty()) {
				auto& it = iterators.back();
				const json& layerData = it.second.value();

				MapLayerInfo layerInfo;
				if (processLayerNode(layerData, layerInfo)) {
					const MapLayerInfo& parentGroup = groups.back();
					
					layerInfo.opacity = static_cast<sf::Uint8>(layerInfo.opacity * static_cast<float>(parentGroup.opacity) / 255.0f);
					layerInfo.isVisible &= parentGroup.isVisible;
					layerInfo.offset += parentGroup.offset;

					switch (layerInfo.type)
					{
					case MapLayerInfo::TILE_LAYER:
						mapInfo.layers.push_back(layerInfo);
						break;

					case MapLayerInfo::OBJECT_GROUP:
						//TODO: add object group
						break;

					case MapLayerInfo::IMAGE_LAYER:
						//TODO: add image layer

					case MapLayerInfo::GROUP:
						{
							auto layersIt = layerData.find("layers");
							if (layersIt != layerData.end() && layersIt.value().is_array()) {
								if (++it.second == it.first->end()) {
									iterators.pop_back();
								}

								groups.push_back(layerInfo);
								iterators.push_back(std::make_pair(&layersIt.value(), layersIt.value().begin()));
								continue;
							}
						}
						break;
					}
				}
				else {
					Log::write("Error: unable to load layer");
					// return false;
				}

				if (++it.second == it.first->end()) {
					iterators.pop_back();

					if (!groups.empty()) {
						groups.pop_back();
					}
				}
			}
		}
	}

	return true;
}

bool MapLoader::processLayerNode(const nlohmann::json & layerData, MapLayerInfo & layerInfo)
{
	{
		json layerTypeData = layerData.value("type", json());
		if (layerTypeData.is_string()) {
			std::string layerType = layerTypeData.get<std::string>();

			if (layerType == "tilelayer") {
				layerInfo.type = MapLayerInfo::TILE_LAYER;
			}
			else if (layerType == "objectgroup") {
				layerInfo.type = MapLayerInfo::OBJECT_GROUP;
				Log::write("Error: loading objectgroup is not implemented yet");
				return false;
			}
			else if (layerType == "imagelayer") {
				layerInfo.type = MapLayerInfo::IMAGE_LAYER;
				Log::write("Error: loading imagelayer is not implemented yet");
				return false;
			}
			else if (layerType == "group") {
				layerInfo.type = MapLayerInfo::GROUP;
			}
		}
	}

	// loading basic layer properties
	{
		json nameData = layerData.value("name", json());
		if (nameData.is_string()) {
			layerInfo.name = nameData.get<std::string>();
		}
		else {
			Log::write("Error: layer can't be unnamed");
			return false;
		}

		json opacityData = layerData.value("opacity", json());
		if (opacityData.is_number()) {
			layerInfo.opacity = static_cast<sf::Uint8>(255.0f * opacityData.get<float>());
		}

		json visibilityData = layerData.value("visible", json());
		if (visibilityData.is_boolean()) {
			layerInfo.isVisible = visibilityData.get<bool>();
		}

		json xOffsetData = layerData.value("offsetx", json());
		json yOffsetData = layerData.value("offsety", json());
		if (xOffsetData.is_number() && yOffsetData.is_number()) {
			layerInfo.offset = vec2(xOffsetData.get<float>(), yOffsetData.get<float>());
		}

		//
		if (layerInfo.type == MapLayerInfo::GROUP) { // finish loading group here!
			return true;
		}
		//

		json widthData = layerData.value("width", json());
		json heightData = layerData.value("height", json());
		if (widthData.is_number_unsigned() && heightData.is_number_unsigned()) {
			layerInfo.size = uvec2(widthData.get<unsigned int>(), heightData.get<unsigned int>());
		}
	}

	// loading data format
	bool compressed = false;
	{
		json encodingData = layerData.value("encoding", json());
		if (encodingData.is_string()) {
			std::string encoding = encodingData.get<std::string>();
			if (encoding != "base64") {
				Log::write("Error: layer must be encoded with base64");
				return false;
			}
		}
		else {
			Log::write("Error: layer must contain encoding data");
			return false;
		}

		json compressionData = layerData.value("compression", json());
		if (compressionData.is_string()) {
			std::string compression = compressionData.get<std::string>();
			if (compression != "zlib") {
				Log::write("Error: only zlib compression is supported");
				return false;
			}
			else {
				compressed = true;
			}
		}
	}

	// loading data
	{
		json dataData = layerData.value("data", json());
		if (dataData.is_string()) {
			std::vector<char> data;
			if (compressed) {
				data = math::decompress(math::decodeBase64(dataData.get<std::string>()));
			}
			else {
				data = math::decodeBase64(dataData.get<std::string>());
			}

			layerInfo.data.resize(data.size() / 4);
			std::memcpy(layerInfo.data.data(), data.data(), data.size());
		}
		else {
			Log::write("Error: layer must contain any data");
			return false;
		}
	}

	return true;
}

bool MapLoader::processTilesetNode(const nlohmann::json & tilesetData, MapTilesetInfo& tilesetInfo)
{
	if (!tilesetData.is_object()) {
		return false;
	}

	// loading basic tileset properties
	{
		json nameData = tilesetData.value("name", json());
		if (nameData.is_string()) {
			tilesetInfo.name = nameData.get<std::string>();
		}
		else {
			return false;
		}

		json imageData = tilesetData.value("image", json());
		if (imageData.is_string()) {
			tilesetInfo.imageFileName = imageData.get<std::string>();
			ResourceManager::bind<TextureFactory>(tilesetInfo.name + "_" + tilesetInfo.imageFileName, tilesetInfo.imageFileName);
		}

		json imageWidthData = tilesetData.value("imagewidth", json());
		json imageHeightData = tilesetData.value("imageheight", json());
		if (imageWidthData.is_number_unsigned() && imageHeightData.is_number_unsigned()) {
			tilesetInfo.imageSize = uvec2(imageWidthData.get<unsigned int>(), imageHeightData.get<unsigned int>());
		}

		json marginData = tilesetData.value("margin", json());
		if (marginData.is_number_integer()) {
			tilesetInfo.margin = marginData.get<int>();
		}

		json spacingData = tilesetData.value("spacing", json());
		if (spacingData.is_number_integer()) {
			tilesetInfo.spacing = spacingData.get<int>();
		}

		json tileWidthData = tilesetData.value("tilewidth", json());
		json tileHeightData = tilesetData.value("tileheight", json());
		if (tileWidthData.is_number_unsigned() && tileHeightData.is_number_unsigned()) {
			tilesetInfo.tileSize = uvec2(tileWidthData.get<unsigned int>(), tileHeightData.get<unsigned int>());
		}
		else {
			return false;
		}

		json firstGidData = tilesetData.value("firstgid", json());
		if (firstGidData.is_number_unsigned()) {
			tilesetInfo.firstGid = firstGidData.get<unsigned int>();
		}
		else {
			return false;
		}

		json tileCountData = tilesetData.value("tilecount", json());
		if (tileCountData.is_number_unsigned()) {
			tilesetInfo.tileCount = tileCountData.get<unsigned int>();
		}

		json columnCountData = tilesetData.value("columns", json());
		if (columnCountData.is_number_unsigned()) {
			tilesetInfo.columnCount = columnCountData.get<unsigned int>();
		}

		json tileOffsetData = tilesetData.value("tileoffset", json());
		if (tileOffsetData.is_object()) {
			json xOffsetData = tileOffsetData.value("x", json());
			json yOffsetData = tileOffsetData.value("y", json());
			if (xOffsetData.is_number_unsigned() && yOffsetData.is_number_unsigned()) {
				tilesetInfo.tileOffset = uvec2(xOffsetData.get<unsigned int>(), yOffsetData.get<unsigned int>());
			}
		}
	}

	// loading tile specific data
	{
		json tilesData = tilesetData.value("tiles", json());
		if (tilesData.is_object()) {
			for (nlohmann::json::const_iterator it = tilesData.begin(); it != tilesData.end(); ++it) {
				const json& tileData = it.value();

				MapTileInfo tile;

				bool tileLoaded;
				try {
					tile.relativeGid = std::stoul(it.key());

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

bool MapLoader::processTileNode(const nlohmann::json & tileData, MapTileInfo & tileInfo)
{
	if (!tileData.is_object()) {
		return false;
	}

	json animationData = tileData.value("animation", json());
	if (animationData.is_array()) {
		MapTileAnimationInfo animationInfo;

		if (!processAnimationNode(animationData, animationInfo)) {
			Log::write("Error: unable to load tile animation");
			// return false;
		}
	}

	// TODO: parse objects

	return true;
}

bool MapLoader::processAnimationNode(const nlohmann::json & animationData, MapTileAnimationInfo& animationInfo)
{
	for (const auto& frameData : animationData) {
		if (frameData.is_object()) {
			json tileIdData = frameData.value("tileid", json());
			json durationData = frameData.value("duration", json());
			if (tileIdData.is_number_unsigned() && durationData.is_number_unsigned()) {
				animationInfo.push_back(std::make_pair<unsigned int, unsigned int>(tileIdData.get<unsigned int>(), durationData.get<unsigned int>()));
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
