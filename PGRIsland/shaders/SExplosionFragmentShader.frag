//----------------------------------------------------------------------------------------
/**
 * \file       SExplosionFragmentShader.frag
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   Fragment shader for drawing explosion texture 
*/
//----------------------------------------------------------------------------------------
#version 330

uniform sampler2D texture_diffuse0;  // sampler for the texture access

uniform float time;

in vec2 fTexCoord;     // fragment texture coordinates
out vec4 color;        // outgoing fragment color

in float visibility;
ivec2 pattern = ivec2(3,3);

vec4 sampleTexture(int frame)
{
    vec2 size = vec2(1.0f) / pattern;
    vec2 origin = fTexCoord / pattern;
    vec2 offset;
    offset.x = frame % pattern.x;
    offset.y = (frame / pattern.x) % pattern.y; 
    return texture(texture_diffuse0, origin + offset * size);
};
void main() {
    int frame = int(time / 0.075f);
    color = mix(vec4(0.7f, 0.7f, 0.7f, sampleTexture(frame).a), sampleTexture(frame), visibility);
}