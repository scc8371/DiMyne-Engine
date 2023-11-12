#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec4 tint;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform sampler2D tex0;

uniform float ambientStrength;
uniform float specularStrength;


void main()
{
   //ambient
   float ambient = ambientStrength;
   vec3 ambient = ambientStrength * lightColor;

   //diffuse
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;

   //specular
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * spec * lightColor;

   FragColor = (ambient + diffuse + specular) * (texture(tex0, texCoord) * tint);
}