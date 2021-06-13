//----------------------------------------------------------------------------------------
/**
 * \file       CTexture.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Struct representing a texture
 *
 * Handles loading of a texture from image file 
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include <string>
#include <iostream>

#include "pgr.h"

#include "../dependencies/stb_image.h"


/**
 * Struct representing a texture
 */
struct CTexture
{
	/**
	 * Boolean for checking if the texture is initialized
	 */
	bool MInitialized = false;

	/**
	 * OpenGL identifier of the texture
	 */
	GLuint MID;

	/**
	 * Type of the texture
	 */
	GLenum MType;

	/**
	 * Default constructor
	 * 
	 * creates an unintialized texture
	 */
	CTexture() = default;

	/**
	 * General constructor
	 * 
	 * creates a texture with image located in 'path' and type 'type'
	 * 
	 * \param path - path to an image
	 * \param type - OpenGL texture type
	 * \param wrap - whether the texture should be clamped for banners 
	 */
	CTexture(const std::string& path, const GLenum& type, const bool& clamp = false);

	/**
	 * Cubemap constructor
	 * 
	 * create a cubemap texture
	 * 
	 * \param faces - paths for each faces of the cubemap.
	 * 		        - faces are loaded in this order right, left, up, 
	 *				  down, back, front of the cubemap
	 */
	CTexture(const std::vector<std::string>& faces);

	/**
	 * Destroy a texture
	 * 
	 * deletes OpenGL's abstraction from memory
	 */
	void Destroy();
};

