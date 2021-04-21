#ifndef _UTILITY_IOBSERVER_
#define _UTILITY_IOBSERVER_

#include <pch.h>

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void Update() = 0;
};

#endif // !_UTILITY_IOBSERVER_

