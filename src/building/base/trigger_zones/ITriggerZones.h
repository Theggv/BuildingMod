#if !defined(_BASE_ITRIGGERZONES_)
#define _BASE_ITRIGGERZONES_

#include <pch.h>
#include <math/math_include.h>

class GameObject;

class ITriggerZones
{
public:
    virtual ~ITriggerZones();

protected:
    virtual double GetDistanceToZone(
        GameObject *object, Ray ray, int packedIndex, int minRayLength = 75);

    virtual std::vector<Triangle> GetTransformedZone(GameObject *object, int packedIndex);

    std::vector<std::vector<Triangle>> m_TriggerZones;
};

#endif // _BASE_ITRIGGERZONES_
