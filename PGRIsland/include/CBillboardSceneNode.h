//----------------------------------------------------------------------------------------
/**
 * \file       CBillboardSceneNode.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Billboard scene node that represents a billboard texture
 *
 * Modification of parent CSceneNode for drawing billboard textures 
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "CSceneNode.h"

/**
 * Scene node designated for billboards
 * 
 * handles the drawing object so that it faces the camera
 */
class CBillboardSceneNode : public CSceneNode
{
public:
    /**
     * Constructor for a billboard
     * 
     * \param program - program used for drawing the object
     */
    CBillboardSceneNode(const CShaderProgram& program);

    /**
     * Draw function
     * 
     * handles drawing the object so that it faces the camera 
     */
    void Draw() override;
};

