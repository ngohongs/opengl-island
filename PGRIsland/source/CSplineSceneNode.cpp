//----------------------------------------------------------------------------------------
/**
 * \file       CSplineSceneNode.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Scene node of an object that moves along a Catmull-Rom spline
 *
 * Modification of a scene node for drawing a moving object
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CSplineSceneNode.h"
#include "../include/CGameState.h"

CSplineSceneNode::CSplineSceneNode(const CShaderProgram& program, const CCatmulRomSpline& spline, const float& slow)
	:CSceneNode(program), MSpline(spline), MSlow(slow)
{
    // initial position
    glm::vec3 point = MSpline.GetSplineLoopPoint(MTime);
    glm::vec3 gradient = MSpline.GetSplineLoopGradient(MTime);
    SetPosition(point);
    SetDirection(glm::normalize(gradient));
}

void CSplineSceneNode::Update(const float& deltaTime)
{
    if (MTimeSet && MTime > MTimeToLive)
    {
        MTimeSet = false;
        MTimeToLive = 0.0f;
        SetOn(false);
    }
	MTime += deltaTime / MSlow;

	for (const auto& node : MSceneNodes)
		node->Update(deltaTime);

    // Move and rotate the object
    if (MTime >= (float) MSpline.GetControlPointSize())
        MTime -= MSpline.GetControlPointSize();
    glm::vec3 point = MSpline.GetSplineLoopPoint(MTime);
    glm::vec3 gradient = MSpline.GetSplineLoopGradient(MTime);
    SetPosition(glm::vec3(point.x, point.y, point.z));
    SetDirection(glm::normalize(glm::vec3(gradient.x, 0.0f, gradient.z)));
}

