//----------------------------------------------------------------------------------------
/**
 * \file       CShaderProgram.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing a shader program
 *
 * Initializes a shader program and handles setting of uniform variables
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include <vector>

#include "pgr.h"

/**
 * Class representing a shader program
 * 
 * activates shader program for drawing, sets uniform attributes of the shader program
 */
class CShaderProgram {
public:
	/**
	 * Default constructor
	 * 
	 * an empty shader program
	 */
	CShaderProgram() = default;

	/**
	 * Constructor of a shader program
	 * 
	 * creates a shader program with a vertex shader and a fragment shader
	 * 
	 * \param vertexShaderFile - path to the vertex shader source file
	 * \param fragmentShaderFile - path to the fragment shader source file
	 */
	CShaderProgram(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	/**
	 * Constructor of a an advance shader program.
	 * 
	 * create a shader program with a vertex, geometry, fragment shader
	 * 
	 * \param   vertexShaderFile - path to the vertex shader source file
	 * \param geometryShaderFile - path to the geometry shader source file
	 * \param fragmentShaderFile - path to the fragment shader source file
	 */
	CShaderProgram(const std::string& vertexShaderFile, const std::string& geometryShaderFile, const std::string& fragmentShaderFile);

	/**
	 * Activate method
	 * 
	 * activates the shader program for drawing
	 */
	void UseProgram();

	/**
	 * Uniform setter for a boolean
	 * 
	 * \param  name - name of the uniform attribute
	 * \param value - value of the set boolean
	 */
	void SetBool(const std::string& name, bool value) const;

	/**
	 * Uniform setter for a integer
	 * 
	 * \param  name - name of the uniform attribute
	 * \param value - value of the set integer
	 */
	void SetInt(const std::string& name, int value) const;

	/**
	 * Uniform setter for a float
	 * 
	 * \param  name - name of the uniform attribute
	 * \param value - value of the set float
	 */
	void SetFloat(const std::string& name, float value) const; 

	/**
	 * Uniform setter for a vec3
	 *
	 * \param  name - name of the uniform attribute
	 * \param value - value of the set vector
	 */
	void SetVec3(const std::string& name, glm::vec3 value) const;

	/**
	 * Uniform setter for a vec4
	 *
	 * \param  name - name of the uniform attribute
	 * \param value - value of the set vector
	 */
	void SetVec4(const std::string& name, glm::vec4 value) const;

	/**
	 * Uniform setter for a mat4
	 *
	 * \param  name - name of the uniform attribute
	 * \param value - value of the set mat4
	 */
	void SetMat4(const std::string& name, const glm::mat4& value) const;
protected:
	/**
	 * Boolean representing if the program is initialized
	 */
	bool MInitiliazed = false;

	/**
	 * OpenGL id of the shader program
	 */
	GLuint MProgram;
};
