#pragma once

#include <pch.h>

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void Update() = 0;
};