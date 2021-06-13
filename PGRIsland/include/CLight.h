//----------------------------------------------------------------------------------------
/**
 * \file       CLight.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Struct representing light in shadrers
 *
 * Holds all necessary information for lighting an object in shaders
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "pgr.h"

/**
 * Struct for lights
 */
struct CLight {
	/**
	 * Position or direction of the light
	 * if the w value is 0, the light is directional
	 * if the w value is 1, the light has position
	 */
	glm::vec4 MVector;

	/**
	 * Ambient value for Phong's lighting 
	 */
	glm::vec3 MAmbient;

	/**
	 * Diffuse value for Phong's lighting
	 */
	glm::vec3 MDiffuse;

	/**
	 * Specular value for Phong's lighting
	 */
	glm::vec3 MSpecular;

	/**
	 * Dimming values for a spot light
	 */
	glm::vec3 MDim;
};
