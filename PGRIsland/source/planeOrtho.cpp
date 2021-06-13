//----------------------------------------------------------------------------------------
/**
 * \file       planeOrtho.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Orthogonal plane data
 *
 * Data for drawing an orthogonal plane
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/planeOrtho.h"
const int planeOrthoNAttribsPerVertex = 8;
const int planeOrthoNVertices = 4;
const int planeOrthoNTriangles = 2;
const float planeOrthoVertices[] = {
 0.0f,-1.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
 0.0f, 1.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,
 0.0f, 1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,
 0.0f,-1.0f,1.0f,-0.0f,0.0f,1.0f,0.0f,1.0f,
}; // end planeVertices

const float planeOrthoBannerVertices[] = {
 0.0f,-1.0f,-1.0f,0.0f,0.0f,1.0f,40.0f,1.0f,
 0.0f, 1.0f,-1.0f,0.0f,0.0f,1.0f,40.0f,0.0f,
 0.0f, 1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,
 0.0f,-1.0f,1.0f,-0.0f,0.0f,1.0f,0.0f,1.0f,
}; // end planeBannerVertices

const unsigned planeOrthoTriangles[] = {
  0, 1, 2,
  0, 2, 3,
}; // end planeTriangles



