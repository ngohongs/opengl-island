//----------------------------------------------------------------------------------------
/**
 * \file       CCamera.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing a camera of viewer
 *
 * Handles camera manipulation
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CCamera.h"
#include "../include/CGameState.h"

glm::mat4 CCamera::GetViewMatrix() const
{
	glm::vec3 center = MEye + MDirection;
	return glm::lookAt(MEye, center, MUpVector);
}

void CCamera::SetCamera(const glm::vec3& eye, const glm::vec3& direction, const glm::vec3& upVector)
{
	MEye = eye;
	MDirection = direction;
	MUpVector = upVector;
}

void CCamera::MoveForwardBackward(const float & coeficient)
{
	glm::vec3 moveVector = coeficient * glm::normalize(MDirection);
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), moveVector);
	glm::vec4 eye = translateMatrix * glm::vec4(MEye, 1.0f);
	if (-XZ_RESTRICTION > eye.x || eye.x > XZ_RESTRICTION ||
		-XZ_RESTRICTION > eye.z || eye.z > XZ_RESTRICTION ||
		Y_BOTTOM_RESTRICTION > eye.y || eye.y > Y_CEIL_RESTRICTION) {
		return;
	}

	for (const auto& object : gameState.MRoot->GetSceneNodes())
	{
		if (object->CheckCollision(eye, CAMERA_SIZE))
			return;
	}

	MEye = eye;
	//std::cout << "MEye: [" << MEye.x << ", " << MEye.y << ", " << MEye.z << "]\n"
	//	<< "MDirection: (" << MDirection.x << ", " << MDirection.y << ", " << MDirection.z << ")\n"
	//	<< "MUpVector: (" << MUpVector.x << ", " << MUpVector.y << ", " << MUpVector.z << ")\n";
}

void CCamera::MoveRightLeft(const float& coeficient)
{
	glm::vec3 directionVector = glm::normalize(glm::cross(MUpVector, MDirection));
	glm::vec3 moveVector = coeficient * directionVector;
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), moveVector);
	glm::vec4 eye = translateMatrix * glm::vec4(MEye, 1.0f);
	if (-XZ_RESTRICTION > eye.x || eye.x > XZ_RESTRICTION ||
		-XZ_RESTRICTION > eye.z || eye.z > XZ_RESTRICTION ||
		Y_BOTTOM_RESTRICTION > eye.y || eye.y > Y_CEIL_RESTRICTION) {
		return;
	}

	for (const auto& object : gameState.MRoot->GetSceneNodes())
	{
		if (object->CheckCollision(eye, CAMERA_SIZE))
			return;
	}

	MEye = eye;
	//std::cout << "MEye: [" << MEye.x << ", " << MEye.y << ", " << MEye.z << "]\n"
	//	<< "MDirection: (" << MDirection.x << ", " << MDirection.y << ", " << MDirection.z << ")\n"
	//	<< "MUpVector: (" << MUpVector.x << ", " << MUpVector.y << ", " << MUpVector.z << ")\n";
}

void CCamera::Pan(float angle)
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), MUpVector);
	MDirection = rotationMatrix * glm::vec4(MDirection, 0.0f);
	//std::cout << "MEye: [" << MEye.x << ", " << MEye.y << ", " << MEye.z << "]\n"
	//	<< "MDirection: (" << MDirection.x << ", " << MDirection.y << ", " << MDirection.z << ")\n"
	//	<< "MUpVector: (" << MUpVector.x << ", " << MUpVector.y << ", " << MUpVector.z << ")\n";
}

void CCamera::Tilt(float angle)
{
	glm::vec3 rotationAxis = glm::normalize(glm::cross(MDirection, MUpVector));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotationAxis);
	MUpVector = rotationMatrix * glm::vec4(MUpVector, 0.0f);
	MDirection = rotationMatrix * glm::vec4(MDirection, 0.0f);
	//std::cout << "MEye: [" << MEye.x << ", " << MEye.y << ", " << MEye.z << "]\n"
	//	<< "MDirection: (" << MDirection.x << ", " << MDirection.y << ", " << MDirection.z << ")\n"
	//	<< "MUpVector: (" << MUpVector.x << ", " << MUpVector.y << ", " << MUpVector.z << ")\n";
}
