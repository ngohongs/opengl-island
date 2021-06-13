//----------------------------------------------------------------------------------------
/**
 * \file       CSkyboxSceneNode.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Scene node of a skybox
 *
 * Modification of scene node for drawing a skybox
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "CSceneNode.h"

#include "cube.h"

/**
 * Scene node designated for skybox
 * 
 * handles drawing skybox center around the camera, skybox can change with time
 */
class CSkyboxSceneNode : public CSceneNode
{
private:
    /**
     * Member variable for slowing the time to slow the animation
     */
    float MSlow = 1.0f;
public:
    /**
     * Constructor for a skybox
     * 
     * \param program - program used for drawing the object
     * \param slow - slow coeficient for animation
     */
    CSkyboxSceneNode(const CShaderProgram& program, const float& slow);
    void Draw() override;
};

