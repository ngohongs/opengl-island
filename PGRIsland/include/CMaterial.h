//----------------------------------------------------------------------------------------
/**
 * \file       CMaterial.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Struct representing a material 
 *
 * Holds all necessary information for a material of an object in shaders
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "pgr.h"

/**
 * Struct representing a material
 */
struct CMaterial
{
	/**
	 * Ambient value of the material
	 */
	glm::vec3 MKa = glm::vec3(1.0f);

	/**
	 * Diffuse value of the material
	 */
	glm::vec3 MKd = glm::vec3(1.0f);

	/**
	 * Specular value of the material
	 */
	glm::vec3 MKs = glm::vec3(1.0f);

	/**
	 * Shininess of the material
	 */
	float MNs = 0;
};