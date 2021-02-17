#include "IConnectionPoints.h"

IConnectionPoints::~IConnectionPoints()
{
    delete m_Successor;
}

void IConnectionPoints::SetSuccessor(IConnectionPoints *successor)
{
    m_Successor = successor;
}

AimTestResult IConnectionPoints::CallNext(GameObject *object, GameObject *bindable, int zoneId)
{
    if (m_Successor != nullptr)
        return m_Successor->GetConnectionPoint(object, bindable, zoneId);

    return AimTestResult(false);
}

int IConnectionPoints::CallNext(GameObject *object, GameObject *bindable, vec3 pos)
{
    if (m_Successor != nullptr)
        return m_Successor->GetZoneIdByPosition(object, bindable, pos);

    return -1;
}
