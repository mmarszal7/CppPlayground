#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

in vec3 FragPos;  
in vec3 Normal;  

uniform vec3 viewPos;
uniform Material material;
uniform vec3 lightPosition;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
vec3 lightAmbient = lightColor * vec3(0.2f);
vec3 lightDiffuse = lightColor * vec3(0.5f);
vec3 lightSpecular = vec3(1.0f);

void main()
{
	// ambient
    vec3 ambient = lightAmbient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightDiffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightSpecular * (spec * material.specular);    
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}