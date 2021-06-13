//----------------------------------------------------------------------------------------
/**
 * \file       CSceneNode.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Scene node of an object, represents single object
 *
 * Handles manipulation of an object and mainly draw the of object to the screen
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "pgr.h"

#include "CShaderProgram.h"
#include "CVertex.h"
#include "CTexture.h"
#include "CMeshGeometry.h"

/**
 * General scene node/object to be drawn to the window
 * 
 * handles size, position, direction, interaction reaction of the object,
 * object's geometry is loaded through ASSIMP loader or through
 * PGR's Blender exporter files
 */
class CSceneNode
{
protected:
	/**
	 * Boolean for checking whether the node should be drawn
	 */
	bool IsOn = true;

	/**
	 * Directory of the object's file, used for ASSIMP
	 */
	std::string MDirectory = "";
	
	/**
	 * Boolean showing whether the object is pickable
	 */
	bool IsPickable = false;
	/**
	 * Boolean showing whether the object is picked
	 */
	bool IsPicked = false;

	/**
	 * Boolean if collision with camera is set.
	 */
	bool MCollision = false;

	/**
	 * Mesh geometry of the object
	 */
	CMeshGeometry MMesh;
	/**
	 * Shader used for drawing the object
	 */
	CShaderProgram MShaderProgram;
	/**
	 * If the object consists of multiple meshes, they would be stored in MSceneNodes
	 */
	std::vector<std::shared_ptr<CSceneNode>> MSceneNodes;

	/**
	 * Position of the object
	 */
	glm::vec3 MPosition = glm::vec3(0.0f);
	/**
	 * Size of the object
	 */
	glm::vec3 MSize = glm::vec3(1.0f);
	/**
	 * Direction which the object faces
	 */
	glm::vec3 MDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	/**
	 * Up vector the object
	 */
	glm::vec3 MUpVector = glm::vec3(0.0f, 1.0f, 0.0f);

	/**
	 * Time of the object
	 */
	float MTime = 0.0f;

	/**
	 * Boolean showing wheter the object has time to live.
	 */
	bool MTimeSet = false;
	/**
	 * Duration the object can be drawn
	 */
	float MTimeToLive = 0.0f;

	/**
	 * Help method for loading objects geometry
	 * 
	 * loads mesh geometry represented in ASSIMP's format and
	 * converts it into CMeshGeometry
	 * 
	 * loads vertices's position, normals, texture coordinates, material and diffuse texture
	 * 
	 * \see CMeshGeometry
	 * 
	 * \param mesh - mesh geometry given by ASSIMP to be converted to program's mesh representation
	 * \param scene - scene of the object 
	 */
	void LoadSceneNode(aiMesh* mesh, const aiScene* scene);

	/**
	 * Help method for loading meshes' textures
	 * 
	 * loads texture files and converts them to CTextures for drawing
	 * 
	 * \param mat - material of the mesh that holds the texture's path
	 * \param type - type of the texture to be loaded
	 * 
	 * \return vector of textures for the object
	 */
	std::vector<CTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);

	/**
	 * Help method for loading meshes
	 * 
	 * navigates in ASSIMP's structure and loads each node's mesh
	 * goes through all node's in scene recursively
	 * 
	 * \param node - ASSIMP node that would be loaded and its child nodes would be processed
	 * \param scene - scene of the object
	 */
	void ProcessSceneNode(aiNode* node, const aiScene* scene);

	/**
	 * Method for creating child nodes to the current node
	 * 
	 * child node inherits MDirectory, MPostion, MSize, MDirection of the parent node
	 * 
	 * \return child node of the caller
	 */
	std::shared_ptr<CSceneNode> CreateChildNode();
public:
	/**
	 * Default constructor
	 * 
	 * does not represent an object but a place holder of nodes
	 */
	CSceneNode() = default;

	/**
	 * Constructor for an object
	 * 
	 * \param program - program used for drawing the object
	 */
	CSceneNode(const CShaderProgram& program);

	/**
	 * Default destructor
	 */
	virtual ~CSceneNode() = default;

	/**
	 * Deinitializer of a node
	 * 
	 * destroys mesh of a node
	 */
	void Destroy();

	/**
	 * Getter of the child nodes
	 *
	 * \return refrence to child nodes vector
	 */
	std::vector<std::shared_ptr<CSceneNode>>& GetSceneNodes();

	/**
	 * Update method
	 * 
	 * updates objects MTime
	 * 
	 * \param deltaTime - deltaTime that would be added to MTime
	 */
	virtual void Update(const float& deltaTime);

	/**
	 * Draw method
	 * 
	 * draws object to the screen 
	 */
	virtual void Draw();

	/**
	 * Model matrix getter
	 * 
	 * creates a model matrix for the objects,
	 * takes into account MPosition, MSize, MDirection of the object
	 * 
	 * \return mat4 model matrix 
	 */
	glm::mat4 GetModelMatrix();

	/**
	 * Texture loader
	 * 
	 * loads texture to the current node
	 * 
	 * \param  file - path to the texture
	 * \param  type - type of the texture
	 * \param clamp - whether should the texture be clamped for banners
	 */
	void LoadTextureSceneNode(const std::string& file, const GLenum& type, const bool& clamp = false);

	/**
	 * Object loader
	 * 
	 * loads object through ASSIMP's interface
	 * 
	 * \param file - path to the object's file
	 */
	void LoadSceneNode(const std::string& file);

	/**
	 * Object loader
	 * 
	 * loads object with PGR's Blender plugin export parameters
	 * 
	 * \param  attributesCount - number of attributes of a vertex
	 * \param    verticesCount - number of vertices 
	 * \param   trianglesCount - number of triangles
	 * \param vertexAttributes - array containing vertex attributes in this order (x, y, z, nx, ny, nz, ts, tt)
	 *						     where the first three attributes are x,y,z coordinates of a vertex,
	 *						     second three attributes are x,y,z coordinates of a vertex
	 *							 and last two attributes are its texturing coordinates
	 * \param         indicies - array of indicies representing a triangle in the object
	 */
	void LoadSceneNode(const int& attributesCount,
					const int& verticesCount,
					const int& trianglesCount,
					const float* vertexAttributes,
					const unsigned int* indicies);

	/**
	 * Push method to the MSceneNodes
	 * 
	 * pushes a node into MSceneNodes
	 * 
	 * \param node - node that would be added to MSceneNodes
	 */
	void PushSceneNode(const std::shared_ptr<CSceneNode>& node);

	/**
	 * Setter for node's position
	 * 
	 * \param position - position to be set
	 */
	void SetPosition(const glm::vec3& position);

	/**
	 * Getter of the node's position
	 * 
	 * \return nodes position
	 */
	glm::vec3 GetPosition();

	/**
	 * Setter for the node's size
	 *
	 * \param scale - scale vector for the object 
	 */
	void SetSize(const glm::vec3& scale);

	/**
	 * Setter for node's direction
	 * 
	 * \param direction - direction which the node should face
	 */
	void SetDirection(const glm::vec3& direction);

	/**
	 * Getter of the node's direction
	 * 
	 * \return direction of the node
	 */
	glm::vec3 GetDirection();

	/**
	 * Setter for the node's up vector
	 * 
	 * \param upVector - new up vector of the node
	 */
	void SetUpVector(const glm::vec3& upVector);

	/**
	 * Setter for MPickable
	 * 
	 * \param pickable - true if the node is pickable else false 
	 */
	void SetPickable(const bool& pickable);

	/**
	 * Getter of MPickable
	 * 
	 * \return MPickable
	 */
	bool GetPickable();

	/**
	 * Setter for MPicked
	 * 
	 * \param picked - true if the object is picked else false
	 */
	void SetPicked(const bool& picked);

	/**
	 * Switch for MPicked.
	 * 
	 * switches MPicked
	 * 
	 * \return switched MPicked value
	 */
	bool SwitchPicked();


	/**
	 * Getter of IsOn member variable
	 * 
	 * \return IsOn
	 */
	bool GetOn();

	/**
	 * Setter for IsOn
	 * 
	 * \param on - true if the object is to be drawn else false
	 */
	void SetOn(const bool& on);

	/**
	 * Switch for IsOn	
	 * 
	 * switches IsOn
	 * 
	 * \return switched IsOn value
	 */
	bool SwitchOn();

	/**
	 * Setter for MTimeToLive
	 * 
	 * sets the duration for how long should the object be drawn
	 * 
	 * \param time - the duration of drawing
	 */
	void SetTimeToLive(const float& time);

	/**
	 * Setter for MCollision
	 * 
	 * \param collision - true if collision should be checked else false
	 */
	void SetCollision(const bool& collision);

	/**
	 * Method that checks whether the object collides with object passed by parameters
	 * 
	 * collisions are calculated as spherical collisions
	 * 
	 * \param position - position of the other object that collision should be checked with
	 * \param	  size - size of the the other object that collision should be checked with
	 * 
	 * \return - true if collsion is found else false 
	 */
	bool CheckCollision(const glm::vec3& position, const glm::vec3 size);
};

