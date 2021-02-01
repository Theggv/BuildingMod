#ifndef _BUILDOBJECTS_WALLFULL_
#define _BUILDOBJECTS_WALLFULL_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/WallBase/WallBase.h>

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 *      StabilityComponent
 * */
class WallFull : public WallBase
{
public:
    WallFull(edict_t *owner);

    virtual void Start() override;
    virtual void Update() override;
    virtual void StateUpdated() override;

    /**
     * Идея метода - соединить this фундамент с other, 
     * и затем вызвать other->ConnectionFoundations(this, false)
     * useRecursion нужна, чтобы метод не зациклился 
    * */
    virtual void ConnectFoundations(WallFull *other, bool useRecursion = true) = 0;

protected:
    static const double m_ModelSize;
    static const double m_MinHeight;
    static const double m_MaxHeight;

    virtual void AimPointHandler();
    virtual AimTestResult TraceGroundTest(AimTestResult result) = 0;
    AimTestResult MaxHeightTest(AimTestResult aimTest, AimTestResult groundTest);
    AimTestResult MinHeightTest(AimTestResult aimTest, AimTestResult groundTest);

    virtual AimTestResult AimTest(ray ray) = 0;

    Shape GetShape();
    virtual Shape GetShape(AimTestResult result) = 0;

    /**
	 * Генерирует треугольники для 4 точек a b c d
	 * heights - массив высот [minHeight, maxHeight]
 	 * */
    std::vector<Triangle> GenerateTriangles(vec2 a, vec2 b, vec2 c, vec2 d, vec2 heights);

private:
    AimTestResult IntersectionTest(AimTestResult result);
};

#endif // !_BUILDOBJECTS_WALLFULL_
