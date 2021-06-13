//----------------------------------------------------------------------------------------
/**
 * \file       SWaterFragmentShader.frag
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   Fragment shader for drawing a water plane
 *
*/
//----------------------------------------------------------------------------------------
#version 330

/**
 * Light struct
 */
struct Light {
	vec4 vector;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 dim;
};

/**
 * Material struct
 */
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

/**
 * Water material
 */
Material material;

/**
 * Spotlight parameter
 *
 *   cameraEye - position of camera, source of spotlight
 *   cameraDir - front vector of camera, direction of casted Light
 *	    cutOff - spotlight cutoff
 * outerCutOff - spotlight outerCutoff 
 */
uniform vec3 cameraEye;
uniform vec3 cameraDir;
uniform float cutOff;
uniform float outerCutOff;

/**
 * Direction of directional light
 */
uniform Light dirLight;

/**
 * View matrix
 */
uniform mat4 view;

/**
 * Vertex output - fragment inputs
 * 
 *	    fPosition - position of the vertex in camera space
 *		  fNormal - normal of the vertex in camera space
 *		fTexCoord - texturing coordinates of vertex
 */
in vec3 fPosition;
in vec2 fTexCoord;
in vec3 fNormal;

/**
 * Fog factor
 */
in float visibility;

/**
 * Color of the fragment
 */
out vec4 color;

vec3 normal = normalize(fNormal);

/**
 * Setups a material for water
 */
void setupMaterial() {
	material.ambient = vec3(0.3f);
	material.diffuse = vec3(0.0f, 0.70f, 0.93f);
	material.specular = vec3(1.0f);
	material.shininess = 48.0f;
}

/**
 * Calculation of directional light
 */
vec3 dirCalc() {
	// ambient
	vec3 ambient = dirLight.ambient * material.ambient;
	
	// diffuse
	vec3 toLightDir = normalize(-vec3(dirLight.vector));
	vec3 diffuse =  max(dot(normal, toLightDir), 0.0) * dirLight.diffuse * material.diffuse;
	
	// specular
	vec3 fromLightDir = -toLightDir;
	vec3 viewDir = normalize(-fPosition);
	vec3 reflectDir =  reflect(fromLightDir, normal);
	vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * dirLight.specular * material.specular;

	return ambient + diffuse + specular;
}

/**
 * Calculation of spot light
 */
vec3 spotCalc() {
	vec3 cameraDir = normalize(vec3(view * vec4(cameraDir, 0)));
	vec3 toLightDir = normalize(-fPosition);
	float theta = dot(toLightDir, -cameraDir); 

	// check if fragment is in spotlight cone
	if(theta > outerCutOff) 
	{    
		// ambient
		vec3 ambient = vec3(0.1f) * material.ambient;
        
		// diffuse 
		vec3 diffuse = max(dot(normal, toLightDir), 0.0) * vec3(1.0f) * material.diffuse;;  
        
		// specular
		vec3 viewDir = normalize(-fPosition);
		vec3 reflectDir = reflect(-toLightDir, normal);  
		vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * vec3(1.0f) * material.specular;

		// dimming around outer cone
        float epsilon = (cutOff - outerCutOff);
		float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity; 
		
		// attenuation, futher fragments dimmer
		float dist = length(-fPosition);
		float attenuation = 1.0 / (1.0f + 0.0009f * dist + 0.0005f * (dist * dist));    
		diffuse *= attenuation;
		specular *= attenuation;   
            
		return ambient + diffuse + specular;
	}
	// else return just ambient lighting
	return vec3(0.1f) * material.ambient;
}


void main(void){
	setupMaterial();
	color = mix(vec4(0.7f, 0.7f, 0.7f, 1.0f), vec4(dirCalc() + spotCalc(), 0.7f), visibility);
}