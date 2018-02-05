#include "Map.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "ResourceManager.h"
#include "TextureFactory.h"
#include "Log.h"


sf::Color Map::getBackgroundColor() const
{
	return m_backgroundColor;
}


void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const auto& layer : m_layers) {
		if (layer.isVisible()) {
			target.draw(layer, states);
		}
	}
}


LayerSet::LayerSet(const uvec2 & mapSize, const uvec2 & tileSize, const std::string & textureName, unsigned int patchSize) :
	m_isVisible(true), m_mapSize(mapSize), m_tileSize(tileSize), 
	m_patchCount(static_cast<sf::Uint32>(std::ceil(static_cast<float>(mapSize.x) / patchSize)), static_cast<sf::Uint32>(std::ceil(static_cast<float>(mapSize.y) / patchSize))),
	m_patchSize(patchSize), m_textureName(textureName), m_texture(nullptr)
{
	m_texture = ResourceManager::get<sf::Texture>(textureName);
	m_patches.resize(m_patchCount.x * m_patchCount.y);
}

void LayerSet::addTile(const std::array<sf::Vertex, 4>& vertices, unsigned int x, unsigned int y)
{
	sf::Int32 patchX = static_cast<sf::Int32>(std::ceil(x / m_patchSize));
	sf::Int32 patchY = static_cast<sf::Int32>(std::ceil(y / m_patchSize));
	sf::Int32 patchIndex = m_patchCount.x * patchY + patchX;

	for (size_t i = 0; i < 4; ++i) {
		m_patches[0].push_back(vertices[i]);
	}
}

void LayerSet::setVisible(bool visible)
{
	m_isVisible = visible;
}

bool LayerSet::isVisible() const
{
	return m_isVisible;
}

void LayerSet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// TODO: make culling using screen quad and etc.
	for (size_t i = 0; i < m_patches.size(); ++i) {
		states.texture = m_texture;
		target.draw(m_patches[i].data(), m_patches[i].size(), sf::Quads, states);
	}
}