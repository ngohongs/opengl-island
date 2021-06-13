//----------------------------------------------------------------------------------------
/**
 * \file       CWaterPlaneSceneNode.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Scene node of a water plane
 *
 * Handles initialization of a plane mesh and drawing simulated water waves
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "CSceneNode.h"

/**
 * Scene node for drawing water
 * 
 * generates a plane mesh that is used for water animation
 */
class CWaterPlaneSceneNode : public CSceneNode
{
private:
public:

    /**
     * Constructor for water plane
     * 
     * generates a plane mesh for water animation
     * 
     * \param program - program that is used for drawing the object
     */
    CWaterPlaneSceneNode(const CShaderProgram& program);

    /**
     * Draw method
     */
    void Draw() override;
};

