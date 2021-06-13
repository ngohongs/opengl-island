//----------------------------------------------------------------------------------------
/**
 * \file       CCatmulRomSpline.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing a Catmull-Rom spline
 *
 * Calculates point and gradient on a looped spline with given time
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include <vector>

#include "pgr.h"

/**
 * Class representing a Catmul-Rom spline
 * 
 * spline is considered as loop
 */
class CCatmulRomSpline
{
private:

	/**
	 * Control points which the spline goes through
	 */
	std::vector<glm::vec3> MControlPoints;
public:

	/**
	 * Constructor for a Catmull-Rom spline 
	 * 
	 * \param controlPoints - controlPoints of the spline
	 */
	CCatmulRomSpline(const std::vector<glm::vec3>& controlPoints) : MControlPoints(controlPoints) {};

	/**
	 * Method for getting the position 
	 * 
	 * gives position depending on the time
	 * 
	 * \param t - time for retrieving the position
	 * 
	 * \return 3D vector of the position at the time t
	 */
	glm::vec3 GetSplineLoopPoint(float t) const;

	/**
	 * Method for getting the gradient
	 * 
	 * gives gradient that the object moving on the spline
	 * should face at time t 
	 * 
	 * \param t - time for retrieving the gradient
	 * 
	 * \return 3D vector of the direction which the moving object should face 
	 */
	glm::vec3 GetSplineLoopGradient(float t) const;

	/**
	 * Getter for the size of MControlPoints
	 * 
	 * \return number of MControlpoints
	 */
	size_t GetControlPointSize() const;
};

