//----------------------------------------------------------------------------------------
/**
 * \file       CCamera.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing a camera of viewer
 *
 * Handles camera manipulation
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include <iostream>

#include "pgr.h"

#include "HConstants.h"

/**
 * CCamera struct representing camera/player
 * 
 * contains function for getting appropriate view matrix
 * and movement of the camera
 */
struct CCamera
{
	/**
	 * Position of the camera
	 */
	glm::vec3 MEye = glm::vec3(0.0f, 0.0f, 0.0f);

	/**
	 * Direction which the camera looks at.
	 */
	glm::vec3 MDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	/**
	 * Up vector for the camera.
	 */
	glm::vec3 MUpVector = glm::vec3(0.0f, 1.0f, 0.0f);

	/**
	 * View matrix getter
	 * 
	 * creates view matrix for current camera
	 * 
	 * \return view matrix for current camera
	 */
	glm::mat4 GetViewMatrix() const;

	/**
	 * Setter for camera's properties
	 * 
	 * \param       eye - position of the camera
	 * \param direction - direction which the camera looks at
	 * \param  upVector - up vector to the camera 
	 */
	void SetCamera(const glm::vec3& eye, const glm::vec3& direction, const glm::vec3& upVector);

	/**
	 * Forward and backward movement for the camera
	 * 
	 * moves the camera in the direction of MDirection multiplied by a coeficient
	 *
	 * restricts movement in world space, in X and Z axis (-XZ_RESTRICTION; XZ_RESTRICTION)
	 * and in Y axis (Y_BOTTOM_RESTRICTION; Y_CEIL_RESTRICTION)
	 * 
	 * \see HConstants.h
	 * 
	 * \param coeficient - coeficient for multiplying the MDirection
	 */
	void MoveForwardBackward(const float & coeficient);

	/**
	 * Left and right movement for the cameera
	 * 
	 * moves the camera in the direction of right vector (cross product of MDirection and MUpVector) 
	 * multiplied by a coeficient
	 * 
	 * restricts movement in world space, in X and Z axis (-XZ_RESTRICTION; XZ_RESTRICTION)
	 * and in Y axis (Y_BOTTOM_RESTRICTION; Y_CEIL_RESTRICTION)
	 * 
	 * \see HConstants.h
	 * 
	 * \param coeficient - coeficient for multiplying the right vector
	 */
	void MoveRightLeft(const float& coeficient);

	/**
	 * Pan function
	 * 
	 * pans the camera by an angle
	 * 
	 * \param angle - panning angle
	 */
	void Pan(float angle);

	/**
	 * Tilt function
	 * 
	 * tilts the camera by an angle
	 * 
	 * \param angle - tilting angle
	 */
	void Tilt(float angle);
};

