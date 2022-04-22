#include "FoundationSquare.h"
#include <building/constants.h>

FoundationSquare::FoundationSquare()
{
}

FoundationSquare::~FoundationSquare()
{
}

Position FoundationSquare::GetObjectOffset(double angle)
{
	auto mat = mat4::TranslateMatrix(vec3(0, UNIT_SIZE / 2))
		* mat4::RotationMatrix(angle);

	return Position(vec3::Zero().Transform(mat), vec3(0, angle, 0));
}
