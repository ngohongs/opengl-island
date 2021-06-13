//----------------------------------------------------------------------------------------
/**
 * \file       CVertex.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Struct representing a vertex with all its attributes
 *
 *
*/
//----------------------------------------------------------------------------------------
#pragma once
#include "pgr.h"

/**
 * Struct for representing a vertex of an object
 */
struct CVertex
{
	/**
	 * Postion of the vertex
	 */
	glm::vec3 MPosition;

	/**
	 * Normal of the vertex
	 */
	glm::vec3 MNormal;

	/**
	 * Texture coordinates of the vertex
	 */
	glm::vec2 MTextureCoordinates;
};
