#include "Map.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "ResourceManager.h"
#include "TextureFactory.h"
#include "Log.h"


void Map::cull(const rect & bounds)
{
	for (auto& layer : m_layers) {
		layer.cull(bounds);
	}
}

sf::Color Map::getBackgroundColor() const
{
	return m_backgroundColor;
}


void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const auto& layer : m_layers) {
		target.draw(layer, states);
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
		m_patches[patchIndex].push_back(vertices[i]);
	}

	updateAABB(vertices[0].position, vertices[2].position);
}

void LayerSet::cull(const rect & bounds)
{
	m_isVisible = m_boundingBox.intersects(bounds);

	m_visiblePatchStart.x = static_cast<int>(std::floor((bounds.left / m_tileSize.x) / m_patchSize));
	m_visiblePatchStart.y = static_cast<int>(std::floor((bounds.top / m_tileSize.y) / m_patchSize));
	if (m_visiblePatchStart.x < 0) m_visiblePatchStart.x = 0;
	if (m_visiblePatchStart.y < 0) m_visiblePatchStart.y = 0;

	m_visiblePatchEnd.x = static_cast<int>(std::ceil((bounds.width / m_tileSize.x) / m_patchSize));
	m_visiblePatchEnd.y = static_cast<int>(std::ceil((bounds.height / m_tileSize.y) / m_patchSize));
	if (m_visiblePatchEnd.x > static_cast<int>(m_patchCount.x)) m_visiblePatchEnd.x = m_patchCount.x;
	if (m_visiblePatchEnd.y > static_cast<int>(m_patchCount.y)) m_visiblePatchEnd.y = m_patchCount.y;

	m_visiblePatchEnd += m_visiblePatchStart;
}

void Layer::cull(const rect & bounds)
{
	for (auto& layerSet : m_layerSets) {
		layerSet.second.cull(bounds);
	}
}

void Layer::setVisible(bool visible)
{
	m_isVisible = visible;
}

bool Layer::isVisible() const
{
	return m_isVisible;
}

void Layer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!m_isVisible) {
		return;
	}

	for (const auto& layerSet : m_layerSets) {
		target.draw(layerSet.second, states);
	}
}

void LayerSet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!m_isVisible) {
		return;
	}

	states.texture = m_texture;

	for (auto x = m_visiblePatchStart.x; x <= m_visiblePatchEnd.x; ++x)
	{
		for (auto y = m_visiblePatchStart.y; y <= m_visiblePatchEnd.y; ++y)
		{
			auto index = y * m_patchCount.x + x;

			target.draw(m_patches[index].data(), m_patches[index].size(), sf::Quads, states);
		}
	}
}

void LayerSet::updateAABB(const vec2 & topLeft, const vec2 & bottomRight)
{
	if (topLeft.x < m_boundingBox.left) {
		m_boundingBox.left = topLeft.x;
	}

	if (topLeft.y < m_boundingBox.top) {
		m_boundingBox.top = topLeft.y;
	}

	if (bottomRight.x > m_boundingBox.left + m_boundingBox.width) {
		m_boundingBox.width = bottomRight.x - m_boundingBox.left;
	}

	if (bottomRight.y > m_boundingBox.top + m_boundingBox.height) {
		m_boundingBox.height = bottomRight.y - m_boundingBox.top;
	}
}
