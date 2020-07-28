#pragma once

#include <pch.h>
#include "Components/Transform.h"

class GameObject
{
public:

	/// <summary>
	/// Unique id of object
	/// </summary>
	const int Id;

	const Transform Transform;
};