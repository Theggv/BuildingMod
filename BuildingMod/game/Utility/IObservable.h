#pragma once

#include <pch.h>

class IObservable
{
public:
	virtual ~IObservable() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};