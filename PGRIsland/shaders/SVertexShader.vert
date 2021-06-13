//----------------------------------------------------------------------------------------
/**
 * \file       SVertexShader.vert
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   General vertex shader for drawing objects
 *
*/
//----------------------------------------------------------------------------------------
#version 330

/**
 * Position, normal, texturing coordinates of the vertex
 */
layout (location = 0) in vec3 position;          
layout (location = 1) in vec3 normal;            
layout (location = 2) in vec2 texCoord;           

/**
 * Sun position for calcalculating directional light
 */
uniform vec3 lightPosition; 

/**
 * Projection, view, model matrices
 */
uniform mat4 projection;
uniform mat4 view;     
uniform mat4 model;      

/**
 * Vertex output - fragment inputs
 * 
 *	    fPosition - position of the vertex in camera space
 *		  fNormal - normal of the vertex in camera space
 *		fTexCoord - texturing coordinates of vertex
 */
out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;

/**
 * Fog constants
 */
out float visibility;
const float density = 0.0035f;
const float gradient = 4.0f;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0f);
  fPosition = vec3(view * model * vec4(position, 1.0));
  fNormal = mat3(transpose(inverse(view * model))) * normal; 
  fTexCoord = texCoord;

  // fog calculation
  float cameraVertexDistance = length((view * model * vec4(position, 1.0f)).xyz);
  visibility = clamp(exp(-pow(cameraVertexDistance * density, gradient)), 0.0f, 1.0f);
}
