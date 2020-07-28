#pragma once

#include <pch.h>
#include "Components/Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	/// <summary>
	/// Unique id of object
	/// </summary>
	const int Id;

	const transform_t* Transform;
};