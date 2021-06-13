//----------------------------------------------------------------------------------------
/**
 * \file       CMeshGeometry.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing a mesh geometry of an object
 *
 * Holds information of a mesh in C++ form and transforms it into OpenGL's form
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CMeshGeometry.h"
#include <iostream>

CMeshGeometry::CMeshGeometry(const std::vector<CVertex>& vertices,
                const std::vector<unsigned int>& indices, 
                const std::vector<CTexture>& textures,
                const CMaterial& material)
{
	MVertices = vertices;
	MIndices = indices;
	MTextures = textures;
    MMaterial = material;

	SetupMeshGeometry();
}

void CMeshGeometry::Destroy()
{
    glDeleteVertexArrays(1, &MVertexArrayObject);
    glDeleteBuffers(1, &MVertexBufferObject);
    glDeleteBuffers(1, &MElementBufferObject);
    MVertices.clear();
    MIndices.clear();
    for ( auto& texture: MTextures ) 
        texture.Destroy();
    MTextures.clear();
}

void CMeshGeometry::GeneratePlaneMesh(const int& vertexCount, const float& size)
{
    std::vector<CVertex> verticies;
    for (int i = 0; i < vertexCount; ++i)
    {
        for (int j = 0; j < vertexCount; ++j)
        {
            CVertex vertex;
            vertex.MPosition = glm::vec3(j * size, 0, i * size);
            verticies.push_back(vertex);
        }
    }

    std::vector<unsigned int> indicies;
    for (int i = 0; i < vertexCount - 1; ++i)
    {
        for (int j = 0; j < vertexCount - 1; ++j)
        {
            unsigned int topLeft = (i * vertexCount) + j;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = ((i + 1) * vertexCount) + j;
            unsigned int bottomRight = bottomLeft + 1;
            indicies.push_back(topLeft);
            indicies.push_back(bottomLeft);
            indicies.push_back(topRight);
            indicies.push_back(topRight);
            indicies.push_back(bottomLeft);
            indicies.push_back(bottomRight);
        }
    }
    MVertices = verticies;
    MIndices = indicies;
    SetupMeshGeometry();
}

void CMeshGeometry::SetupMeshGeometry()
{
    glGenVertexArrays(1, &MVertexArrayObject);
    glGenBuffers(1, &MVertexBufferObject);
    glGenBuffers(1, &MElementBufferObject);

    glBindVertexArray(MVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, MVertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, MVertices.size() * sizeof(CVertex), &MVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MIndices.size() * sizeof(unsigned int),
        &MIndices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)offsetof(CVertex, MNormal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)offsetof(CVertex, MTextureCoordinates));

    glBindVertexArray(0);
}

void CMeshGeometry::Draw(CShaderProgram& shader)
{
    bool noTexture = false;
    for (unsigned int i = 0; i < MTextures.size(); i++)
    { 
        if (!MTextures[i].MInitialized) {
            noTexture = true;
            break;
        }
        glActiveTexture(GL_TEXTURE0 + i);
        std::string type = "texture_diffuse"+std::to_string(i);
        shader.SetInt(type, i);
        glBindTexture(MTextures[i].MType, MTextures[i].MID);
    }
    if (noTexture || !MTextures.size()) {
        shader.SetBool("textureUse", false);
    }
    else
        shader.SetBool("textureUse", true);
    shader.SetVec3("material.ambient", MMaterial.MKa);
    shader.SetVec3("material.diffuse", MMaterial.MKd);
    shader.SetVec3("material.specular", MMaterial.MKs);
    shader.SetFloat("material.shininess", MMaterial.MNs);
    // draw mesh
    glBindVertexArray(MVertexArrayObject);
    glDrawElements(GL_TRIANGLES, MIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void CMeshGeometry::PushTexture(const CTexture& texture)
{
    MTextures.push_back(texture);
}
