#pragma once

#include <bitset>

#include "Map.h"

class MapLoader
{
public:
	bool load(const std::string& filename, Map& map);

private:
	typedef std::vector<std::pair<unsigned int, unsigned int>> MapTileAnimationInfo;

	struct MapTileInfo
	{
		MapTileInfo() :
			relativeGid(0)
		{}

		unsigned int relativeGid;

		MapTileAnimationInfo animation;
	};

	struct MapTilesetInfo
	{
		MapTilesetInfo() :
			margin(0), spacing(0), firstGid(0), tileCount(0), columnCount(0) 
		{}

		std::string name;

		std::string textureName;
		uvec2 imageSize;

		int margin;
		int spacing;
		ivec2 offset;

		uvec2 tileSize;

		unsigned int firstGid;
		unsigned int tileCount;
		unsigned int columnCount;
	};

	struct MapLayerInfo
	{
		enum Type 
		{
			TILE_LAYER,
			OBJECT_GROUP,
			IMAGE_LAYER,
			GROUP
		};

		MapLayerInfo() :
			opacity(255), isVisible(true)
		{}

		Type type;
		std::string name;
		sf::Uint8 opacity;
		bool isVisible;

		uvec2 size;
		vec2 offset;

		std::vector<sf::Uint32> data;
	};

	struct MapObjectInfo
	{
		
	};

	struct MapInfo
	{
		MapInfo() {}

		uvec2 size;
		uvec2 tileSize;
		sf::Color backgroundColor;

		nlohmann::json properties;

		std::vector<MapLayerInfo> layers;
		std::vector<MapTilesetInfo> tilesets;
	};


	bool processMapNode(const nlohmann::json& mapData, MapInfo& mapInfo);
	bool processLayerNode(const nlohmann::json& layerData, MapLayerInfo& layerInfo);
	bool processTilesetNode(const nlohmann::json& tilesetData, MapTilesetInfo& tilesetInfo);
	bool processTileNode(const nlohmann::json& tileData, MapTileInfo& tileInfo);
	bool processAnimationNode(const nlohmann::json& animationData, MapTileAnimationInfo& animationInfo);

	sf::Uint32 unpackGid(sf::Uint32 gid, bool& flipHorizontally, bool& flipVertically, bool& flipDiagonally);

	std::string m_folder;
};