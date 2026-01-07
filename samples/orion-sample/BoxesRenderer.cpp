#include <BoxesRenderer.h>
#include <ResourceManager.h>

namespace oriongl::samples::boxes {

const char *vertex_shader = R"(#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 nPos;
    layout (location = 2) in vec2 aTextCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    out vec3 FragPos;
    out vec3 NormalPos;
    out vec2 TextCoord;

    void main()
    {
      gl_Position = projection * view * model * vec4(aPos, 1.0);
      FragPos = vec3(model * vec4(aPos, 1.0));
      NormalPos = mat3(transpose(inverse(model))) * nPos;
      TextCoord = aTextCoord;
    }
)";

const char *frag_shader = R"(#version 330 core
    struct Light {
        vec3 position;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
  
    struct Material {
      sampler2D diffuse;
      sampler2D specular;
      sampler2D emission;
      float shininess;
    };

    in vec3 FragPos;
    in vec3 NormalPos;
    in vec2 TextCoord;

    uniform Light light;
    uniform Material material;
    uniform vec3 viewPos;

    out vec4 FragColor;

    void main()
    {
      vec4 textel1 = texture(material.diffuse, TextCoord);
      vec4 textel2 = texture(material.specular, TextCoord);
  
      vec3 diffTextelRGB = textel1.rgb;
      vec3 specTextelRGB = textel2.rgb;
      vec3 ambientColor = diffTextelRGB * light.ambient; 

      vec3 lightVector = normalize(light.position - FragPos);
      vec3 normalVector = normalize(NormalPos);
      float diffuseFactor = max(dot(lightVector, normalVector), 0.0);

      vec3 diffuseColor = light.diffuse * (diffuseFactor * diffTextelRGB);
  
      vec3 specularVector = normalize(viewPos - FragPos);
      vec3 reflectedVector = reflect(-lightVector, normalVector);
      float specularFactor = pow(max(dot(reflectedVector, specularVector), 0.0), 32);

      vec3 specularColor = light.specular * (specularFactor * specTextelRGB);

      vec3 finalColor = ambientColor + diffuseColor + specularColor;
      float alpha = textel1.a + textel2.a;
      FragColor = vec4(finalColor, alpha);
    }
)";

const char *frag_light_shader = R"(#version 330 core
    out vec4 FragColor;

    void main()
    {
      FragColor = vec4(1.0f);
    }
)";

BoxesRenderer::BoxesRenderer() {
    // clang-format off
    const std::vector<glm::vec3> cubePositions = {
        {  35.0f,   0.0f,   0.0f },
        {  24.7f,   8.0f,  24.7f },
        {   0.0f,  15.0f,  35.0f },
        { -24.7f,   8.0f,  24.7f },
        { -35.0f,   0.0f,   0.0f },

        { -24.7f,  -8.0f, -24.7f },
        {   0.0f, -15.0f, -35.0f },
        {  24.7f,  -8.0f, -24.7f },

        {  17.5f,  20.0f,  30.3f },
        { -17.5f, -20.0f, -30.3f }
    };
    // clang-format on

    std::vector<std::string> boxMaterial{
        "assets/container.png",
        "assets/container_specular.png",
        "assets/black_pixel.png",
    };

    auto cube = std::make_unique<graphics::Model>(oriongl::core::getProgram(vertex_shader, frag_shader, {}));
    cube->loadData(oriongl::core::getCubeData(3.0f), oriongl::core::getMaterial(boxMaterial));

    data.emplace_back(std::move(cube));
    for (auto &position : cubePositions) {
        data.back().addInstance(graphics::ModelData{position});
    }

    auto light = std::make_unique<graphics::Model>(oriongl::core::getProgram(vertex_shader, frag_light_shader, {}));
    light->loadData(oriongl::core::getSphereData(5.0f));

    data.emplace_back(std::move(light));
    data.back().addInstance(graphics::ModelData{glm::vec3(0.0f)});
};

} // namespace oriongl::samples::boxes
