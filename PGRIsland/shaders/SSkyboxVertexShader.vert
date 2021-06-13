//----------------------------------------------------------------------------------------
/**
 * \file       SSkyboxVertexShader.vert
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   Vertex shader for drawing skybox
 *
 * Passes texturing coordinates for sampling of a skybox
 *
*/
//----------------------------------------------------------------------------------------
#version 330 core

/**
 * Vertex of skybox
 */
layout (location = 0) in vec3 position;

/**
 * Texturing coordinates for skybox
 */
out vec3 TexCoords;

/**
 * Projection, view, model matrices
 */
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = position;
    gl_Position = projection * view * model * vec4(position, 1.0);;
}  