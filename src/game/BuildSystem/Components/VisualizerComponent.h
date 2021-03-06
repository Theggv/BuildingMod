#ifndef _BUILDINGOBJECTS_COMPONENTS_VISUALIZERCOMPONENT_
#define _BUILDINGOBJECTS_COMPONENTS_VISUALIZERCOMPONENT_

#include <pch.h>
#include "IComponent.h"
#include <game/Geometry.h>

class VisualizerComponent : public IComponent
{
public:
    /**
     * @param updateRate OnUpdate rate in seconds 
     * */
    VisualizerComponent(double updateRate = 0.2);
    ~VisualizerComponent();

    void Enable();
    void Disable();

    bool IsEnabled();

    void Visualize(std::vector<Triangle> triangles);

private:
    double m_UpdateRate;
    bool m_IsEnable;
    double m_NextUpdate;

    void DrawLine(vec3 p1, vec3 p2);
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_VISUALIZERCOMPONENT_
