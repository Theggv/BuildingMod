#if !defined(_FACTORIES_IBUILDINGFACTORY)
#define _FACTORIES_IBUILDINGFACTORY

#include <pch.h>

class BuildingObject;

class IBuildingFactory
{
    virtual std::unique_ptr<BuildingObject> CreateSquareFoundation() = 0;
};

#endif // _FACTORIES_IBUILDINGFACTORY
