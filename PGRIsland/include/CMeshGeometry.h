//----------------------------------------------------------------------------------------
/**
 * \file       CMeshGeometry.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing a mesh geometry of an object
 *
 * Holds information of a mesh in C++ form and transforms it into OpenGL's form
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include <vector>

#include "pgr.h"

#include "HConstants.h"
#include "CShaderProgram.h"
#include "CVertex.h"
#include "CTexture.h"
#include "CMaterial.h"

/**
 * Class representing a mesh in OpenGL abstraction
 * 
 * holds VAO, VBO, EBO of the mesh for draw by the GPU
 */
class CMeshGeometry {
public:
	/**
	 * Default constructor
	 * 
	 * represents an empty mesh
	 */
	CMeshGeometry() = default;

	/**
	 * Constructor for a mesh
	 * 
	 * \param vertices - vertices for drawing, already ordered for VBO setup
	 * \param  indices - indices of the faces, already ordered for EBO setup
	 * \param textures - textures of the mesh
	 * \param material - material of the mesh
	 */
	CMeshGeometry(const std::vector<CVertex>& vertices,
				  const std::vector<unsigned int>& indices,
				  const std::vector<CTexture>& textures,
				  const CMaterial& material);

	/**
	 * Deinitialzer for a mesh
	 * 
	 * destroy OpenGL's buffers and internal information about the mesh
	 */
	void Destroy();

	/**
	 * Help method for generating a plane mesh
	 * 
	 * generates plane mesh 
	 * 
	 * \param vertexCount - number of vertices on one side
	 * \param		 size - gaps between each vertex
	 */
	void GeneratePlaneMesh(const int& vertexCount, const float& size);

	/**
	 * Draw method
	 * 
	 * draws mesh with shaderProgram
	 * 
	 * \param shaderProgram - shader program used for drawing the mesh
	 */
	void Draw(CShaderProgram& shaderProgram);

	/**
	 * Appends a texture for the mesh
	 * 
	 * \param texture - new texture for the mesh
	 */
	void PushTexture(const CTexture& texture);
private:
	/**
	 * VBO represented as a vector of CVertex
	 * 
	 * \see CVertex
	 */
	std::vector<CVertex> MVertices;

	/**
	 * EBO represented as a vector unsigned ints
	 */
	std::vector<unsigned int> MIndices;

	/**
	 * Textures of the mesh
	 */
	std::vector<CTexture> MTextures;

	/**
	 * VAO of the mesh
	 */
	GLuint MVertexArrayObject;

	/**
	 * EBO of the mesh
	 */
	GLuint MElementBufferObject;

	/**
	 * VBO of the mesh
	 */
	GLuint MVertexBufferObject;

	/**
	 * Material of the mesh
	 */
	CMaterial MMaterial;

	/**
	 * Help method for conversion between C++ and OpenGL vertex abstractions
	 * 
	 * convertes MVertices, MIndices into OpenGL's VBO and EBO and encapsulates it into a VAO
	 * 
	 */
	void SetupMeshGeometry();
};

