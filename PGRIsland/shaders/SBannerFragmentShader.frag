//----------------------------------------------------------------------------------------
/**
 * \file       SBannerFragmentShader.frag
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief	   Fragment shader for drawing banner texture 
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
 *
 */
uniform sampler2D texture_diffuse0;

uniform float time;

uniform Material material;

uniform Light light;

uniform Light dirLight;

uniform vec3 cameraEye;
uniform vec3 cameraDir;
uniform float cutOff;
uniform float outerCutOff;

uniform mat4 view;

in vec3 fNormal;
in vec3 fPosition;
in vec2 fTexCoord;
in vec3 fLightPosition;

in float visibility;

out vec4 color;



vec3 normal = normalize(fNormal);

vec3 dirCalc() {
	vec3 ambient = dirLight.ambient * material.ambient;

	vec3 toLightDir = normalize(-vec3(dirLight.vector));
	vec3 diffuse =  max(dot(normal, toLightDir), 0.0) * dirLight.diffuse * material.diffuse;

	vec3 fromLightDir = -toLightDir;
	vec3 viewDir = normalize(-fPosition);
	vec3 reflectDir =  reflect(fromLightDir, normal);
	vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * dirLight.specular * material.specular;

	return ambient + diffuse + specular;
}

vec3 pointCalc() {
	vec4 lightPos = view * light.vector;
	float dist = length(fPosition - vec3(lightPos));
	float attenuation = 1/(light.dim[0]+light.dim[1]*dist+light.dim[2]*dist*dist);

	vec3 ambient = light.ambient * material.ambient;

	vec3 toLightDir = normalize(vec3(lightPos)-fPosition);
	vec3 diffuse =  max(dot(normal, toLightDir), 0.0) * light.diffuse * material.diffuse;

	vec3 viewDir = normalize(-fPosition);
	vec3 reflectDir =  reflect(-toLightDir, normal);
	vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * light.specular * material.specular;

	return (ambient + diffuse + specular)*attenuation;
}

vec3 spotCalc() {
	vec3 cameraDir = normalize(vec3(view *vec4(cameraDir, 0)));
	vec3 toLightDir = normalize(-fPosition);
	float theta = dot(toLightDir, -cameraDir); 
	if(theta > outerCutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
	{    
		// ambient
		vec3 ambient = vec3(0.1f) * material.ambient;
        
		// diffuse 
		vec3 diffuse = max(dot(normal, toLightDir), 0.0) * vec3(1.0f) * material.diffuse;;  
        
		// specular
		vec3 viewDir = normalize(-fPosition);
		vec3 reflectDir = reflect(-toLightDir, normal);  
		vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * vec3(1.0f) * material.specular;
        float epsilon = (cutOff -outerCutOff);
		float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity; 
		// attenuation
		float dist = length(-fPosition);
		float attenuation = 1.0 / (1.0f + 0.0009f * dist + 0.0005f * (dist * dist));    

		// ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
		diffuse *= attenuation;
		specular *= attenuation;   
            
		return ambient + diffuse + specular;
	}
	return vec3(0.1f) * material.ambient;
}

void main() {
	// directional light
	// ambient
	vec3 ambientCoef = dirLight.ambient * material.ambient;
	// diffuse
	vec3 toLightDir = normalize(-vec3(dirLight.vector));
	float diffCoef =  max(dot(normal, toLightDir), 0.0);
	// specular
	vec3 fromLightDir = -toLightDir;
	vec3 viewDir = normalize(-fPosition);
	vec3 reflectDir =  reflect(fromLightDir, normal);
	float specCoef = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 l = dirCalc();
	vec3 p = pointCalc();
	vec3 s = spotCalc();
	// vec3 result = (ambientCoef + diffCoef * dirLight.diffuse * material.diffuse + specCoef * dirLight.specular * material.specular);

	vec2 offset = vec2(0.0f, 0.0f);
	offset.x -= fract(time / 40.0f) * 40.0f;

	vec4 lightMaterialColor = vec4(l+s+p, 1.0f) * texture(texture_diffuse0, fTexCoord + offset);
	color = lightMaterialColor;
}