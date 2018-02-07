#include "ShaderFactory.h"

#include "FileManager.h"

ShaderFactory::ShaderFactory(const ShaderSource & vertexShaderSource, const ShaderSource & fragmentShaderSource) :
	AbstractFactory(tag<sf::Shader>{}),
	m_vertexShaderSource(vertexShaderSource),
	m_fragmentShaderSource(fragmentShaderSource),
	m_data(nullptr)
{
}

void * ShaderFactory::load()
{
	if (m_data == nullptr) {
		std::unique_ptr<sf::Shader> shader = std::make_unique<sf::Shader>();

		std::vector<char> vertexShaderData;
		std::vector<char> fragmentShaderData;

		if (m_vertexShaderSource.type == ShaderSource::FILE) {
			vertexShaderData = FileManager::open(m_vertexShaderSource.source);
		}
		else {
			vertexShaderData = std::vector<char>(m_vertexShaderSource.source.begin(), m_vertexShaderSource.source.end());
			vertexShaderData.push_back(0);
		}

		if (m_fragmentShaderSource.type == ShaderSource::FILE) {
			fragmentShaderData = FileManager::open(m_fragmentShaderSource.source);
		}
		else {
			fragmentShaderData = std::vector<char>(m_fragmentShaderSource.source.begin(), m_fragmentShaderSource.source.end());
			fragmentShaderData.push_back(0);
		}

		if (!shader->loadFromMemory(vertexShaderData.data(), fragmentShaderData.data())) {
			throw std::runtime_error("Unable to load shader: " + 
				(m_vertexShaderSource.type == ShaderSource::FILE ? m_vertexShaderSource.source : "\"...some vertex shader...\"") + ", " +
				(m_fragmentShaderSource.type == ShaderSource::FILE ? m_fragmentShaderSource.source : "\"...some fragment shader...\""));
		}

		m_data = std::move(shader);
	}

	return m_data.get();
}

void ShaderFactory::clear()
{
	m_data.reset();
}
