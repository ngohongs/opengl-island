//----------------------------------------------------------------------------------------
/**
 * \file       SWaterGeometryShader.geom
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   Geometry shader for drawing water plane
 * 
 * Calculates normal for the water plane
*/
//----------------------------------------------------------------------------------------
#version 330

/**
 * Take in triangles for calculating normals
 */
layout ( triangles ) in;
layout ( triangle_strip, max_vertices = 3) out;

/**
 * Vertex output - fragment inputs
 * 
 *	    fPosition - position of the vertex in camera space
 *		  fNormal - normal of the vertex
 *		fTexCoord - texturing coordinates of vertex
 */
out vec3 fNormal;
out vec3 fPosition;

/**
 * Pojection, view, model matrices
 */
uniform mat4 projection;
uniform mat4 view;     
uniform mat4 model;  

/**
 * Fog constants
 */
out float visibility;
const float density = 0.0025f;
const float gradient = 4.0f;


/**
 * Calculation of triangle's normal
 */ 
vec3 calculateTriangleNormal(){
	vec3 tangent = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 bitangent = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 normal = cross(tangent, bitangent);	
	return normalize(normal);
}


void main(void){
	vec3 normal = calculateTriangleNormal();

	// calculate for each vertex:
	//   1. visibility factor for fog,
	//   2. normal in camera space
	//   3. vertex position in camera space


	vec4 position = gl_in[0].gl_Position;
	gl_Position = projection * view * model * position;
	vec3 cameraPosition =  vec3(view * model * position);
	float distanceToCamera = length(cameraPosition);
	visibility = clamp(exp(-pow(distanceToCamera * density, gradient)), 0.0f, 1.0f);
	fNormal = mat3(transpose(inverse(view * model))) * normal;
	fPosition = vec3(view * model * position);
	EmitVertex();
	
	position = gl_in[1].gl_Position;
	gl_Position = projection * view * model * position;
	cameraPosition =  vec3(view * model * position);
	distanceToCamera = length(cameraPosition);
	visibility = clamp(exp(-pow(distanceToCamera * density, gradient)), 0.0f, 1.0f);
	fNormal = mat3(transpose(inverse(view * model))) * normal;
	fPosition = vec3(view * model * position);
	EmitVertex();
	
	position = gl_in[2].gl_Position;
	gl_Position = projection * view * model * position;
	cameraPosition =  vec3(view * model * position);
	distanceToCamera = length(cameraPosition);
	visibility = clamp(exp(-pow(distanceToCamera * density, gradient)), 0.0f, 1.0f);
	fNormal = mat3(transpose(inverse(view * model))) * normal;
	fPosition = vec3(view * model * position);
	EmitVertex();
	
	EndPrimitive();
}