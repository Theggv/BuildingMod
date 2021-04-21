#ifndef _STABILITYCOMPONENT_CONNECTIONTYPES_
#define _STABILITYCOMPONENT_CONNECTIONTYPES_

#include <game/BuildSystem/ObjectManager.h>

enum class ConnectionTypes
{
	Unknown,	// Изначальное состояние (нет соединения)
	Child,		// Стабильность зависит от родительского объекта
	Additional, // Добавляет стабильность соседним объектам
	Parent,		// Влияет на стабильность дочерних объектов
	Independent // Не влияет на стабильность
};

struct Connection
{
	ConnectionTypes type;
	p_GameObjectWeak_t ptr;
};

struct ConnectionOrdering
{
	// impl of < operator
	bool operator()(Connection const &lhs, Connection const &rhs) const
	{
		if (&lhs.ptr == &rhs.ptr)
			return lhs.type < rhs.type;

		return &lhs.ptr < &rhs.ptr;
	}
};

#endif // _STABILITYCOMPONENT_CONNECTIONTYPES_