#pragma once

#include <memory>

#include <SFML/Graphics/Shader.hpp>

#include "AbstractFactory.h"

class ShaderFactory : public AbstractFactory
{
private:
	struct ShaderSource
	{
		enum Type { FILE, STRING };
		ShaderSource(Type type, const std::string& source) : 
			type(type), source(source) 
		{}

		Type type;
		std::string source;
	};
public:
	struct FromFile : ShaderSource
	{
		FromFile(const std::string& source) : ShaderSource(ShaderSource::FILE, source) {}
	};
	
	struct FromString : ShaderSource
	{
		FromString(const std::string& source) : ShaderSource(ShaderSource::STRING, source) {}
	};

	ShaderFactory(const ShaderSource& vertexShaderSource, const ShaderSource& fragmentShaderSource);

	void* load() override;
	void clear() override;

private:
	ShaderSource m_vertexShaderSource;
	ShaderSource m_fragmentShaderSource;

	std::unique_ptr<sf::Shader> m_data;
};
