#ifndef _UTILITY_IOBSERVABLE_
#define _UTILITY_IOBSERVABLE_

#include <pch.h>

class IObserver;

class IObservable
{
public:
	virtual ~IObservable() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};

#endif // !_UTILITY_IOBSERVABLE_
