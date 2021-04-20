#ifndef _STABILITYCOMPONENT_CONNECTIONTYPES_
#define _STABILITYCOMPONENT_CONNECTIONTYPES_

#include <game/BuildSystem/ObjectManager.h>

enum class ConnectionTypes
{
	Child,		// Стабильность зависит от родительского объекта
	Additional, // Добавляет стабильность соседним объектам
	Parent,		// Влияет на стабильность дочерних объектов
	Independent // Не влияет на стабильность
};

struct Connection
{
	ConnectionTypes type;
	p_GameObjectWeak_t ptr;

	friend bool operator<(const Connection &lhs, const Connection &rhs)
	{
		return lhs.ptr < rhs.ptr;
	}
};

#endif // _STABILITYCOMPONENT_CONNECTIONTYPES_