//----------------------------------------------------------------------------------------
/**
 * \file       SWaterVertexShader.vert
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   Vertex shader for drawing a water plane
 *
*/
//----------------------------------------------------------------------------------------
#version 330
layout (location = 0) in vec3 position; 

/**
 * Time for calculating height of a wave
 */
uniform float time;

/**
 * Projection, view, model matrices
 */
uniform mat4 projection;
uniform mat4 view;     
uniform mat4 model;   

const float PI = 3.1415926535897932384626433832795;

/**
 * Amplitude of a wave
 */
const float amplitude = 0.05f;

/**
 * Calculate wave height according to the time and X, Z coordinates
 */
float generateHeight(){
	float component1 = sin(2.0 * PI * time + (position.x * 16.0)) * amplitude;
	float component2 = sin(2.0 * PI * time + (position.z * position.x * 8.0)) * amplitude;
	return component1 + component2;
}

void main(void) {
	float height = generateHeight();
	gl_Position = vec4(position.x,  height, position.z, 1.0f);
}