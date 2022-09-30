#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <string.h>
#include <assert.h>

using namespace DirectX;

#define	PI	3.14159f

static float DegreeToRadian(float Angle)
{
	return Angle / 180.f * PI;
}

static float RadianToDegree(float Angle)
{
	return Angle * 180.f / PI;
}


