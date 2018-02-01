#pragma once

#include <typeindex>

class AbstractFactory
{
protected:
	template<class T>
	struct tag {
		typedef T type;
	};
public:
	template<class T>
	AbstractFactory(tag<T>) :
		m_storedType(std::type_index(typeid(T)))
	{
	}

	virtual ~AbstractFactory() {
		clear();
    }

	virtual void* load() = 0;
	virtual void clear() {}

	std::type_index getStoredTypeIndex() const {
		return m_storedType;
	}

protected:
	std::type_index m_storedType;
};
