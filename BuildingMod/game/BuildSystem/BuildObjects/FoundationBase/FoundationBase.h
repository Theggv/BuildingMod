#ifndef _BUILDOBJECTS_FOUNDATIONBASE_
#define _BUILDOBJECTS_FOUNDATIONBASE_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/AimTestResult.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>

enum class HeightZones
{
    LOW,
    MIDDLE,
    HIGH,
};

class FoundationBase : public GameObject
{
public:
    FoundationBase(edict_t *owner);

    virtual void Start() override;
    virtual void Update() override;
    virtual void StateUpdated() override;

    /**
     * Идея метода - соединить this фундамент с other, 
     * и затем вызвать other->ConnectionFoundations(this, false)
     * useRecursion нужна, чтобы метод не зациклился 
    * */
    virtual void ConnectFoundations(FoundationBase *other, bool useRecursion = true) = 0;

protected:
    static const double m_ModelSize;
    static const double m_MinHeight;
    static const double m_MaxHeight;

    virtual void AimPointHandler();
    virtual AimTestResult TraceGroundTest(vec3 viewPoint, vec3 viewAngle) = 0;
    virtual AimTestResult FoundationAimTest(ray ray) = 0;

    /**
	 * Генерирует треугольники для 4 точек a b c d
	 * heights - массив высот [minHeight, maxHeight]
 	 * */
    std::vector<Triangle> GenerateTriangles(vec2 a, vec2 b, vec2 c, vec2 d, vec2 heights);

    void VisualizeZones(std::vector<Triangle> triangles);
    void DrawLine(vec3, vec3);
};

#endif // !_BUILDOBJECTS_FOUNDATIONBASE_
