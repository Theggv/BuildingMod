#if !defined(_FACTORIES_IBUILDINGFACTORY)
#define _FACTORIES_IBUILDINGFACTORY

#include <memory>

class GameObject;

class IBuildingFactory
{
    virtual std::unique_ptr<GameObject *> CreateSquareFoundation() = 0;
};

#endif // _FACTORIES_IBUILDINGFACTORY
