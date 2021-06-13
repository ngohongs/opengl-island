//----------------------------------------------------------------------------------------
/**
 * \file       plane.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Plane data
 *
 * Data for drawing a plane
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/plane.h"
const int planeNAttribsPerVertex = 8;
const int planeNVertices = 4;
const int planeNTriangles = 2;
const float planeVertices[] = {
  -1.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
  1.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,
  1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,
  -1.0f,1.0f,0.0f,-0.0f,0.0f,1.0f,1.0f,0.0f,
}; // end planeVertices

const unsigned planeTriangles[] = {
  0, 1, 2,
  0, 2, 3,
}; // end planeTriangles

