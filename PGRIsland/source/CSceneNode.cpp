//----------------------------------------------------------------------------------------
/**
 * \file       CSceneNode.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Scene node of an object, represents single object
 *
 * Handles manipulation of an object and mainly draw the of object to the screen
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CSceneNode.h"
#include "../include/CGameState.h"

CSceneNode::CSceneNode(const CShaderProgram& program)
    : MShaderProgram(program)
{}

void CSceneNode::Destroy()
{
    MMesh.Destroy();
    for (auto& child : MSceneNodes)
        child->Destroy();
}

std::vector<std::shared_ptr<CSceneNode>>& CSceneNode::GetSceneNodes()
{
    return MSceneNodes;
}

std::shared_ptr<CSceneNode> CSceneNode::CreateChildNode()
{
    std::shared_ptr<CSceneNode> childNode = std::make_shared<CSceneNode>(MShaderProgram);
    childNode->MDirectory = MDirectory;
    childNode->MPosition = MPosition;
    childNode->MSize = MSize;
    childNode->MDirection = MDirection;
    return childNode;
}

void CSceneNode::Update(const float& deltaTime)
{
    if (MTimeSet && MTime > MTimeToLive)
    {
        MTimeSet = false;
        MTimeToLive = 0.0f;
        SetOn(false);
    }
    MTime += deltaTime;
    for (const auto& node : MSceneNodes)
        node->Update(deltaTime);
}

void CSceneNode::Draw()
{
    if (!IsOn)
        return;

    // Use MShaderProgram for rendering current scenenode
    MShaderProgram.UseProgram();

    // Set uniform attributes
    MShaderProgram.SetFloat("time", MTime);

    MShaderProgram.SetMat4("model", GetModelMatrix());
    MShaderProgram.SetMat4("view", gameState.MCamera.GetViewMatrix());
    MShaderProgram.SetMat4("projection", gameState.GetProjectionMatrix());

    MShaderProgram.SetVec3("lightPosition", SUN_POSITION);
    MShaderProgram.SetVec4("light.vector", gameState.light.MVector);
    MShaderProgram.SetVec3("light.ambient", gameState.light.MAmbient);
    MShaderProgram.SetVec3("light.diffuse", gameState.light.MDiffuse);
    MShaderProgram.SetVec3("light.specular", gameState.light.MSpecular);
    MShaderProgram.SetVec3("light.dim", gameState.light.MDim);
   
    MShaderProgram.SetVec3("cameraDir", gameState.MCamera.MDirection);
    MShaderProgram.SetFloat("cutOff", CAMERA_LIGHT_CUTOFF);
    MShaderProgram.SetFloat("outerCutOff", CAMERA_LIGHT_OUTERCUTOFF);

    MShaderProgram.SetVec4("dirLight.vector", gameState.dirLight.MVector);
    MShaderProgram.SetVec3("dirLight.ambient", gameState.dirLight.MAmbient);
    MShaderProgram.SetVec3("dirLight.diffuse", gameState.dirLight.MDiffuse);
    MShaderProgram.SetVec3("dirLight.specular", gameState.dirLight.MSpecular);

    MMesh.Draw(MShaderProgram);
    // Draw child nodes
    for (const auto& node: MSceneNodes)
        node->Draw();
}

glm::mat4 CSceneNode::GetModelMatrix()
{
   // If the object is picked show it by the camera
    if (IsPicked && IsOn)
    {
        glm::vec3 position = MPosition;
        glm::vec3 direction = MDirection;
        glm::vec3 upVector = MUpVector;
        glm::vec3 rightOffset = glm::normalize(glm::cross(gameState.MCamera.MDirection, gameState.MCamera.MUpVector));
        glm::vec3 offset = 2.5f * gameState.MCamera.MDirection + rightOffset + -0.5f * gameState.MCamera.MUpVector;
        position = gameState.MCamera.MEye + offset;
        upVector = gameState.MCamera.MUpVector;
        direction = gameState.MCamera.MDirection;
        SetPosition(position);
        SetDirection(direction);
        SetUpVector(upVector);
    }
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, MSize);
    modelMatrix = glm::inverse(glm::lookAt(MPosition, MPosition + MDirection, MUpVector)) * modelMatrix;
    return modelMatrix;
}

void CSceneNode::LoadTextureSceneNode(const std::string& file, const GLenum& type, const bool& clamp)
{
    MMesh.PushTexture(CTexture(file, type, clamp));
}

void CSceneNode::ProcessSceneNode(aiNode* node, const aiScene* scene)
{
    // load mesh from current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        std::shared_ptr<CSceneNode> childNode = CreateChildNode();
        childNode->LoadSceneNode(mesh, scene);
        MSceneNodes.push_back(childNode);
    }
    // process children of the current node
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        std::shared_ptr<CSceneNode> childNode = CreateChildNode();
        childNode->ProcessSceneNode(node->mChildren[i], scene);
        MSceneNodes.push_back(childNode);
    }
}

void CSceneNode::LoadSceneNode(const std::string& file)
{
    Assimp::Importer importer;
    importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);
    const aiScene* scene = importer.ReadFile(file,
        aiProcess_Triangulate
        | aiProcess_FlipUVs
        | aiProcess_PreTransformVertices
        | aiProcess_GenSmoothNormals
        | aiProcess_JoinIdenticalVertices);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    MDirectory = file.substr(0, file.find_last_of('/'));
    std::cout << MDirectory << std::endl;
    ProcessSceneNode(scene->mRootNode, scene);
}

void CSceneNode::LoadSceneNode(const int& attributesCount, const int& verticesCount, const int& trianglesCount, const float* vertexAttributes, const unsigned int* indicies)
{
    std::vector<CVertex> vertices;
    for (int i = 0; i < verticesCount; ++i) {
        const float* vertexData = vertexAttributes + 8 * i;
        CVertex vertex;
        vertex.MPosition = glm::vec3(vertexData[0], vertexData[1], vertexData[2]);
        vertex.MNormal = glm::vec3(vertexData[3], vertexData[4], vertexData[5]);
        vertex.MTextureCoordinates = glm::vec2(vertexData[6], vertexData[7]);

        vertices.push_back(vertex);
    }
    std::vector<unsigned int> meshIndicies(indicies, indicies + trianglesCount * 3);
    MMesh = CMeshGeometry(vertices, meshIndicies, {}, {});

}

void CSceneNode::PushSceneNode(const std::shared_ptr<CSceneNode>& node)
{
    MSceneNodes.push_back(node);
}

void CSceneNode::LoadSceneNode(aiMesh* mesh, const aiScene* scene)
{
    std::vector<CVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<CTexture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        CVertex vertex;
        // positions
        vertex.MPosition = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        // normals
        if (mesh->HasNormals())
            vertex.MNormal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        // texture coordinates
        if (mesh->mTextureCoords[0]) 
            vertex.MTextureCoordinates = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        else
            vertex.MTextureCoordinates = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    // go through all faces of the node
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve indicies of the face
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // get material
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    CMaterial mat;
    aiColor4D ambient;
    aiColor4D diffuse;
    aiColor4D specular;
    float shininess;

    aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient);
    aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
    aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular);
    aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

    mat.MKa = glm::vec3(ambient.r, ambient.g, ambient.b);
    mat.MKd = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
    mat.MKs = glm::vec3(specular.r, specular.g, specular.b);
    mat.MNs = shininess;

    // get diffuse texture
    if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
        std::vector<CTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    MMesh = CMeshGeometry(vertices, indices, textures, mat);
}

std::vector<CTexture> CSceneNode::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
    std::vector<CTexture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        CTexture texture(MDirectory + "/" + str.C_Str(), GL_TEXTURE_2D);
        textures.push_back(texture);
    }
    return textures;
}

void CSceneNode::SetPosition(const glm::vec3& position)
{
    MPosition = position;
    for (const auto& node : MSceneNodes)
        node->SetPosition(position);
}

glm::vec3 CSceneNode::GetPosition()
{
    return MPosition;
}

void CSceneNode::SetSize(const glm::vec3& scale)
{
    MSize = scale;
    for (const auto& node : MSceneNodes)
        node->SetSize(scale);
}

void CSceneNode::SetDirection(const glm::vec3& direction)
{
    MDirection = direction;
    for (const auto& node : MSceneNodes)
        node->SetDirection(direction);
}

glm::vec3 CSceneNode::GetDirection()
{
    return MDirection;
}

void CSceneNode::SetUpVector(const glm::vec3& upVector)
{
    MUpVector = upVector;
    for (const auto& node : MSceneNodes)
        node->SetUpVector(upVector);
}

void CSceneNode::SetPickable(const bool& pickable)
{
    IsPickable = pickable;
}

bool CSceneNode::GetPickable()
{
    return IsPickable;
}

void CSceneNode::SetPicked(const bool& picked)
{
    IsPicked = picked;
}

bool CSceneNode::SwitchPicked()
{
    if (!IsPickable)
        return false;
    return IsPicked = !IsPicked;
}

bool CSceneNode::GetOn()
{
    return IsOn;
}

void CSceneNode::SetOn(const bool& on)
{
    IsOn = on;
}

bool CSceneNode::SwitchOn()
{
    return IsOn = !IsOn;
}

void CSceneNode::SetTimeToLive(const float& time)
{
    // Sets time to live
    SetOn(true);
    MTimeSet = true;
    MTimeToLive = MTime + time;
}

void CSceneNode::SetCollision(const bool& collision)
{
    MCollision = collision;
}

bool CSceneNode::CheckCollision(const glm::vec3& position, const glm::vec3 size)
{
    // If checking the collision is necessary
    if (!MCollision || !IsOn)
        return false;

    float distance = glm::distance(position, MPosition);
    float radiusSum = MSize.x + size.x;

    return distance < radiusSum;
}
