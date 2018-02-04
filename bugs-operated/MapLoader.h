#pragma once

#include "Map.h"

class MapLoader
{
public:
	static bool load(const nlohmann::json& data, Map& map);

private:
	static bool processMapNode(const nlohmann::json& mapData, Map& map);
	static bool processTilesetNode(const nlohmann::json& tilesetData, MapTileset& tileset);
	static bool processTileNode(const nlohmann::json& tileData, MapTile& tile);
	static bool processAnimationNode(const nlohmann::json& animationData, std::vector<std::pair<unsigned int, unsigned int>>& animation);
};