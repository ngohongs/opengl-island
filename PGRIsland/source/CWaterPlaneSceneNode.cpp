//----------------------------------------------------------------------------------------
/**
 * \file       CWaterPlaneSceneNode.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Scene node of a water plane
 *
 * Handles initialization of a plane mesh and drawing simulated water waves
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CWaterPlaneSceneNode.h"
#include "../include/CGameState.h"

CWaterPlaneSceneNode::CWaterPlaneSceneNode(const CShaderProgram& program)
	: CSceneNode(program)
{
	MMesh.GeneratePlaneMesh(WATER_PLANE_SIDE_SIZE, WATER_PLANE_VERTEX_GAP);
}

void CWaterPlaneSceneNode::Draw()
{
	if (!IsOn)
		return;
	MShaderProgram.UseProgram();
	MShaderProgram.SetFloat("time", MTime);
	MShaderProgram.SetMat4("model", GetModelMatrix());
	MShaderProgram.SetMat4("view", gameState.GetViewMatrix());
	MShaderProgram.SetMat4("projection", gameState.GetProjectionMatrix());

	MShaderProgram.SetVec4("dirLight.vector", gameState.dirLight.MVector);
	MShaderProgram.SetVec3("dirLight.ambient", gameState.dirLight.MAmbient);
	MShaderProgram.SetVec3("dirLight.diffuse", gameState.dirLight.MDiffuse);
	MShaderProgram.SetVec3("dirLight.specular", gameState.dirLight.MSpecular);

	MShaderProgram.SetVec3("cameraDir", gameState.MCamera.MDirection);
	MShaderProgram.SetFloat("cutOff", CAMERA_LIGHT_CUTOFF);
	MShaderProgram.SetFloat("outerCutOff", CAMERA_LIGHT_OUTERCUTOFF);

	MMesh.Draw(MShaderProgram);
	for (const auto& node : MSceneNodes)
		node->Draw();
}
