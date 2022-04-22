#if !defined(_INTERFACES_BUILDINGOBJECT_)
#define _INTERFACES_BUILDINGOBJECT_

#include <pch.h>
#include <building/GameObject.h>
#include <interfaces/Position.h>

class BuildingObject : public GameObject
{
private:
public:
    virtual ~BuildingObject();

    virtual Position GetObjectOffset(double angle) = 0;
};

#endif // _INTERFACES_BUILDINGOBJECT_
