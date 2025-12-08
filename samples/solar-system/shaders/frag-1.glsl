#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TextCoord;
in vec3 Normal;
in vec3 FragPosition;
uniform vec3 viewPos;

uniform Light light;
uniform Material material;

out vec4 FragColor;

void main()
{
    vec4 textel1 = texture(material.diffuse, TextCoord);
    vec3 texDiff= textel1.rgb;
    float texAlpha = textel1.a;

    vec4 textel2 = texture(material.specular, TextCoord);
    vec3 texSpec = textel2.rgb;

    //Ambient light;
    vec3 ambientColor = light.ambient * texDiff;

    //Diffuse calc
    vec3 lightVector = normalize(light.position - FragPosition);
    vec3 normalVector = normalize(Normal);
    float diffuseFactor = dot(lightVector, normalVector);
    vec3 diffuseColor = light.diffuse * (max(diffuseFactor, 0.0f) * texDiff);

    //Specular calc
    vec3 viewVector = normalize(viewPos - FragPosition);
    vec3 reflectVector = reflect(-lightVector, normalVector);
    float specularFactor = pow(max(dot(reflectVector, viewVector), 0.0f), 32);
    vec3 specularColor = light.specular * (specularFactor * texSpec);

    vec3 fragColor = ambientColor + diffuseColor + specularColor;

    #ifdef USE_EMISSION_TEXTURE
    //Emission calc
    vec4 textel3 = texture(material.emission, TextCoord);
    vec3 texEmission = textel3.rgb;
    float emissionFactor = max(-diffuseFactor, 0.0f);
    vec3 emissionColor = emissionFactor * texEmission;

    fragColor += emissionColor;
    #endif

	FragColor = vec4(fragColor, texAlpha);
}