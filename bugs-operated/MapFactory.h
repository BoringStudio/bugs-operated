#pragma once

#include <memory>
#include <string>

#include "Map.h"

#include "AbstractFactory.h"

class MapFactory : public AbstractFactory
{
public:
	MapFactory(const std::string& filename);

	void* load() override;
	void clear() override;

private:
	std::string m_filename;

	std::unique_ptr<Map> m_data;
};