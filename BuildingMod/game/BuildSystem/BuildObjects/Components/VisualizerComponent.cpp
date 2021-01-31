#include "VisualizerComponent.h"
#include <game/Server/PrecacheManager.h>

VisualizerComponent::VisualizerComponent(double updateRate)
    : m_UpdateRate(updateRate)
{
    m_IsEnable = false;
    m_NextUpdate = 0;
}

VisualizerComponent::~VisualizerComponent()
{
}

void VisualizerComponent::Enable()
{
    m_IsEnable = true;
}

void VisualizerComponent::Disable()
{
    m_IsEnable = false;
}

bool VisualizerComponent::IsEnabled()
{
    return m_IsEnable;
}

void VisualizerComponent::Visualize(std::vector<Triangle> triangles)
{
    if (!m_IsEnable)
        return;

    if (gpGlobals->time >= m_NextUpdate)
    {
        for (auto triangle : triangles)
        {
            DrawLine(triangle._v0, triangle._v1);
            DrawLine(triangle._v0, triangle._v2);
            DrawLine(triangle._v1, triangle._v2);
        }

        m_NextUpdate = gpGlobals->time + m_UpdateRate;
    }
}

void VisualizerComponent::DrawLine(vec3 p1, vec3 p2)
{
    auto spriteId = PrecacheManager::Instance().GetLaserBeamId();

    MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
    WRITE_BYTE(TE_BEAMPOINTS);
    WRITE_COORD(p1.x);                    //Стартовая точка x
    WRITE_COORD(p1.y);                    //Стартовая точка y
    WRITE_COORD(p1.z);                    //Стартовая точка z
    WRITE_COORD(p2.x);                    //Конечная точка x
    WRITE_COORD(p2.y);                    //Конечная точка y
    WRITE_COORD(p2.z);                    //Конечная точка z
    WRITE_SHORT(spriteId);                //Индекс спрайта
    WRITE_BYTE(0);                        //Стартовый кадр
    WRITE_BYTE(1);                        //Скорость анимации
    WRITE_BYTE((int)(m_UpdateRate * 10)); //Время существования
    WRITE_BYTE(5);                        //Толщина луча
    WRITE_BYTE(0);                        //Искажение
    WRITE_BYTE(255);                      //Цвет красный
    WRITE_BYTE(0);                        //Цвет зеленый
    WRITE_BYTE(0);                        //Цвет синий
    WRITE_BYTE(1000);                     //Яркость
    WRITE_BYTE(0);                        //...
    MESSAGE_END();
}
