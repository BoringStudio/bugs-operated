#pragma once

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <json.hpp>

#include "Math.h"

class Layer;
class LayerSet;

class Map : public sf::Drawable
{
public:
	void cull(const rect& bounds);

	sf::Color getBackgroundColor() const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
	friend class MapLoader;

	sf::Color m_backgroundColor;

	std::vector<Layer> m_layers;
};


class Layer : public sf::Drawable
{
public:
	void cull(const rect& bounds);

	void setVisible(bool visible);
	bool isVisible() const;

	LayerSet& getLayerSet(sf::Uint32 id);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	friend class MapLoader;

	bool m_isVisible;

	std::unordered_map<sf::Uint32, LayerSet> m_layerSets;
};


// Stuff
class LayerSet : public sf::Drawable
{
public:
	LayerSet(const uvec2& mapSize, const uvec2& tileSize, const std::string& textureName, unsigned int patchSize = 10);

	void addTile(const std::array<sf::Vertex, 4>& vertices, unsigned int x, unsigned int y);

	void cull(const rect& bounds);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void updateAABB(const vec2& topLeft, const vec2& bottomRight);

	bool m_isVisible;
	
	uvec2 m_mapSize;
	uvec2 m_tileSize;
	
	uvec2 m_patchCount;
	unsigned int m_patchSize;

	std::string m_textureName;
	sf::Texture* m_texture;

	ivec2 m_visiblePatchStart;
	ivec2 m_visiblePatchEnd;
	std::vector<std::vector<sf::Vertex>> m_patches;

	rect m_boundingBox;
};