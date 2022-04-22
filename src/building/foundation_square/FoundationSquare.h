#if !defined(_FOUNDATION_SQUARE_)
#define _FOUNDATION_SQUARE_

#include <pch.h>
#include <building/foundation_base/FoundationBase.h>

class FoundationSquare : public FoundationBase
{
private:
public:
    FoundationSquare();
    ~FoundationSquare();

    Position GetObjectOffset(double angle) override;
};

#endif // _FOUNDATION_SQUARE_
