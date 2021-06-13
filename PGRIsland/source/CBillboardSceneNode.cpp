//----------------------------------------------------------------------------------------
/**
 * \file       CBillboardSceneNode.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Billboard scene node that represents a billboard texture
 *
 * Modification of parent CSceneNode for drawing billboard textures
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CBillboardSceneNode.h"
#include "../include/CGameState.h"

CBillboardSceneNode::CBillboardSceneNode(const CShaderProgram& program)
	: CSceneNode(program)
{
}

void CBillboardSceneNode::Draw()
{
    if (!IsOn)
        return;
    MShaderProgram.UseProgram();

    MShaderProgram.SetFloat("time", MTime);

    // calculation of model matrix so that the object faces the camera
    glm::mat4 viewMatrix = gameState.MCamera.GetViewMatrix();
    glm::mat4 rotationMatrix = glm::mat4(
        viewMatrix[0],
        viewMatrix[1],
        viewMatrix[2],
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    rotationMatrix = glm::inverse(rotationMatrix);

    MShaderProgram.SetMat4("model", GetModelMatrix() * rotationMatrix);
    MShaderProgram.SetMat4("view", viewMatrix);
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
    for (const auto& node : MSceneNodes)
        node->Draw();
}
