//----------------------------------------------------------------------------------------
/**
 * \file       CCatmulRomSpline.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing a Catmull-Rom spline
 *
 * Calculates point and gradient on a looped spline with given time
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CCatmulRomSpline.h"

glm::vec3 CCatmulRomSpline::GetSplineLoopPoint(float t) const
{
	// Indicies of the closest 4 points
	int pointIndex1 = int(t);
	int pointIndex2 = (pointIndex1 + 1) % MControlPoints.size();
	int pointIndex3 = (pointIndex2 + 1) % MControlPoints.size();
	int pointIndex0 = pointIndex1 > 0 ? pointIndex1 - 1 : MControlPoints.size() - 1;

	t = t - (int)t;
	float tt = t * t;
	float ttt = t * t * t;

	// cubic functions
	float q1 = -ttt + 2.0f * tt - t;
	float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
	float q3 = -3.0f * ttt + 4.0f * tt + t;
	float q4 = ttt - tt;

	float x = MControlPoints[pointIndex0].x * q1 + MControlPoints[pointIndex1].x * q2 + 
			  MControlPoints[pointIndex2].x * q3 + MControlPoints[pointIndex3].x * q4;
	x /= 2;
	float y = MControlPoints[pointIndex0].y * q1 + MControlPoints[pointIndex1].y * q2 +
			  MControlPoints[pointIndex2].y * q3 + MControlPoints[pointIndex3].y * q4;
	y /= 2;
	float z = MControlPoints[pointIndex0].z * q1 + MControlPoints[pointIndex1].z * q2 +
			  MControlPoints[pointIndex2].z * q3 + MControlPoints[pointIndex3].z * q4;
	z /= 2;
	return { x, y, z };
}

glm::vec3 CCatmulRomSpline::GetSplineLoopGradient(float t) const
{
	// indicies of the closest 4 points
	int pointIndex1 = int(t);
	int pointIndex2 = (pointIndex1 + 1) % MControlPoints.size();
	int pointIndex3 = (pointIndex2 + 1) % MControlPoints.size();
	int pointIndex0 = pointIndex1 > 0 ? pointIndex1 - 1 : MControlPoints.size() - 1;

	t = t - (int)t;
	float tt = t * t;
	float ttt = t * t * t;

	// cubic functions
	float q1 = -3.0f * tt + 4.0f * t - 1.0f;
	float q2 = 9.0f * tt - 10.0f * t;
	float q3 = -9.0f * tt + 8.0f * t + 1.0f;
	float q4 = 3.0f * tt - 2.0f * t;

	float x = MControlPoints[pointIndex0].x * q1 + MControlPoints[pointIndex1].x * q2 +
		MControlPoints[pointIndex2].x * q3 + MControlPoints[pointIndex3].x * q4;
	x /= 2;
	float y = MControlPoints[pointIndex0].y * q1 + MControlPoints[pointIndex1].y * q2 +
		MControlPoints[pointIndex2].y * q3 + MControlPoints[pointIndex3].y * q4;
	y /= 2;
	float z = MControlPoints[pointIndex0].z * q1 + MControlPoints[pointIndex1].z * q2 +
		MControlPoints[pointIndex2].z * q3 + MControlPoints[pointIndex3].z * q4;
	z /= 2;
	return { x, y, z };
}

size_t CCatmulRomSpline::GetControlPointSize() const
{
	return MControlPoints.size();
}
