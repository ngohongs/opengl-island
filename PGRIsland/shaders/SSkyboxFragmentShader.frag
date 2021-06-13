//----------------------------------------------------------------------------------------
/**
 * \file       SSkyboxFragmentShader.frag
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   Shader for drawing a skybox
 *
*/
//----------------------------------------------------------------------------------------
#version 330 core

/**
 * Color of the fragment
 */
out vec4 color;

/**
 * Texturing coordinates
 */
in vec3 TexCoords;

/**
 * Blend factor for changing skybox
 */
uniform float blend;

/**
 * Boolean whether it is day or night
 */
uniform bool day;

/**
 * Texture samplers
 */
uniform samplerCube texture_diffuse0;
uniform samplerCube texture_diffuse1;

void main()
{    
    if (!day) 
    {
        color = texture(texture_diffuse1, TexCoords);
        return;
    }
    color = mix(texture(texture_diffuse0, TexCoords), texture(texture_diffuse1, TexCoords), blend);
}