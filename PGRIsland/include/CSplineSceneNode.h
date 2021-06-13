//----------------------------------------------------------------------------------------
/**
 * \file       CSplineSceneNode.h
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Scene node of an object that moves along a Catmull-Rom spline
 *
 * Modification of a scene node for drawing a moving object
 *
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "CSceneNode.h"
#include "CCatmulRomSpline.h"

/**
 * Scene node that moves along a Catmul-Rom spline
 */
class CSplineSceneNode : public CSceneNode
{
private:

    /**
     * Spline that the object moves along
     */
    CCatmulRomSpline MSpline;

    /**
     * Time in spline time, used for getting the object's position
     */
    float MSplineTime = 0.0f;

    /**
     * Time for slowing the movement along the spline
     */
    float MSlow = 1.0f;
public:
    
    /**
     * Constructor for a spline node
     * 
     * \param program - program used for drawing the object
     * \param spline - spline along which the object moves
     * \param slow - slow coeficient for slowing the animatiom
     */
    CSplineSceneNode(const CShaderProgram& program, const CCatmulRomSpline& spline, const float& slow);

    /**
     * Update function
     * 
     * handles time change so that the object moves
     * 
     * \param deltaTime - time delta from last frame
     */
    void Update(const float& deltaTime) override;
};

