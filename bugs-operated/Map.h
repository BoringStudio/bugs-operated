#pragma once

#include <vector>

#include <json.hpp>

#include "Math.h"


class MapLayer;
class MapTileset;
class MapTile;


class Map
{
public:

private:
	friend class MapLoader;

	uvec2 m_size;
	uvec2 m_tileSize;
	sf::Color m_backgroundColor;

	nlohmann::json m_properties;

	std::vector<MapLayer> m_layers;
	std::vector<MapTileset> m_tilesets;
};


class MapLayer
{
public:

private:
	friend class MapLoader;


};


class MapTileset
{
public:

private:
	friend class MapLoader;

	std::string m_name;
	std::string m_imageFileName;

	int m_margin;
	int m_spacing;

	uvec2 m_tileSize;

	unsigned int m_firstGid;
	unsigned int m_tileCount;
	unsigned int m_columnCount;
};


class MapTile
{
public:

private:
	friend class MapLoader;

	unsigned int m_relativeGid;

	std::vector<std::pair<unsigned int, unsigned int>> m_animation;
};