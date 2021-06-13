//----------------------------------------------------------------------------------------
/**
 * \file       CSkyboxSceneNode.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Scene node of a skybox
 *
 * Modification of scene node for drawing a skybox
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CSkyboxSceneNode.h"
#include "../include/CGameState.h"

CSkyboxSceneNode::CSkyboxSceneNode(const CShaderProgram& program, const float& slow)
    :CSceneNode(program), MSlow(slow)
{
    // loads a cube mesh
    LoadSceneNode(cubeNAttribsPerVertex,
        cubeNVertices, cubeNTriangles,
        cubeVertices, cubeTriangles);
    SetSize(SKYBOX_SIZE);
    MMesh.PushTexture(CTexture(SKYBOX_FACES));
    MMesh.PushTexture(CTexture(SKYBOX_MIDNIGHT_FACES));
}

void CSkyboxSceneNode::Draw()
{
    if (!IsOn)
        return;

    float blend = 0.5f * sin(MTime / MSlow) + 0.5f;

    MShaderProgram.UseProgram();

    // Setup uniform attributes
    MShaderProgram.SetFloat("blend", blend);
    MShaderProgram.SetMat4("model", GetModelMatrix());
    MShaderProgram.SetBool("day", gameState.MDay);

    // Setup view matrix so that the skybox moves with the camera
    glm::mat4 view = gameState.GetViewMatrix();
    view[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    MShaderProgram.SetMat4("view", view);
    MShaderProgram.SetMat4("projection", gameState.GetProjectionMatrix());
    MMesh.Draw(MShaderProgram);
    for (const auto& node : MSceneNodes)
        node->Draw();
}
