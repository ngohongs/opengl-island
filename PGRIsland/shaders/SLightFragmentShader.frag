//----------------------------------------------------------------------------------------
/**
 * \file       SLightFragmentShader.frag
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   Fragment shader for drawing light sources
 *
*/
//----------------------------------------------------------------------------------------
#version 330

/**
 * Fragment color of the sun
 */
out vec4 color;

void main() {
  color = vec4(0.93f, 0.55f, 0.23f, 1.0f);
}