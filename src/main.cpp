#include <Framer/Camera.h>
#include <array>
#include "Framer/Framer.h"

#include "Cube.h"
#include "glm/gtc/type_ptr.hpp"
#include "stb_image.h"
#include "stb_perlin.h"
#include "Helper.h"


const unsigned int worldX = 128;
const unsigned int worldZ = 128;
const float worldHeight = 32.0f;
const unsigned int maxCubes = worldX * worldZ * worldHeight * 2;

// Function to generate terrain height using Perlin noise with octaves
float generateTerrainHeight(float x, float z, int num_octaves = 1, float persistence = 0.6f, float lacunarity = 3.0f, float scale = 0.9f) {
    float amplitude = 1.0f;
    float frequency = scale;
    float max_value = 0.0f;   // Used to normalize the result to [0, 1]
    float total = 0.0f;

    for (int octave = 0; octave < num_octaves; ++octave) {
        // Sample perlin noise at the given frequency
        float noise_value = stb_perlin_noise3(x * frequency, 0.0f, z * frequency, 0, 0, 0);

        // Accumulate the noise value weighted by the amplitude
        total += noise_value * amplitude;

        // Update maximum value for normalization
        max_value += amplitude;

        // Update amplitude and frequency for next octave
        amplitude *= persistence;    // Reduce amplitude for finer details
        frequency *= lacunarity;     // Increase frequency for finer details
    }

    // Normalize the total noise value to be between 0 and 1
    return total / max_value;
}

void Run() {
        // Indices for drawing the cube with triangles
    std::vector<unsigned int> indices = CreateIndices(maxCubes);
    std::vector<Cube> vertices;

    int neco = 1;
    std::cout << floor(1.7f) << std::endl;

    float scale = 0.05f;
    glm::vec3 noiseSample = glm::vec3(0.0f);
    for (int x = 0; x < worldX; x++) {
        for (int z = 0; z < worldZ; z++) {
            float height = generateTerrainHeight(noiseSample.x, noiseSample.y) * worldHeight;
            height = floor(height);
            for (int y = -worldHeight; y < height; y++) {
                glm::vec3 pos{x, y, z};
                vertices.emplace_back(CreateDirt(pos));

            }
            glm::vec3 pos{x, height, z};
            vertices.emplace_back(CreateCube(pos));
            noiseSample.y += scale;
        }
        noiseSample.y = 0.0f;
        noiseSample.x += scale;
    }

    fr::Window window{800, 800, "Radcraft"};
    fr::Camera camera{window, 90.0f};


    int widthImg = 0, heightImg = 0, numColCh = 0;
    unsigned char *bytes = stbi_load(RESOURCES_PATH "terrain.png", &widthImg, &heightImg, &numColCh, 0);

    GLuint tex;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);

    glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureStorage2D(tex, 1, GL_RGBA8, widthImg, heightImg);
    glTextureSubImage2D(tex, 0, 0, 0, widthImg, heightImg, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateTextureMipmap(tex);

    stbi_image_free(bytes);

    fr::VBO batchVBO{};
    batchVBO.NamedBufferStorage(vertices.size() * sizeof(Cube));

    fr::Shader shader(RESOURCES_PATH "shaders/shader.vert", RESOURCES_PATH "shaders/shader.frag");
    fr::VBO VBO{vertices.data(), static_cast<GLsizeiptr>(sizeof(Cube) * vertices.size())};
    fr::EBO EBO{indices.data(), static_cast<GLsizeiptr>(sizeof(unsigned int) * indices.size())};
    fr::VAO VAO{};
    VAO.SpecifyData(0, 3, offsetof(Vertex, position));
    VAO.SpecifyData(1, 2, offsetof(Vertex, texCoord));
    VAO.BindVertexBuffer(batchVBO, 0, 0, sizeof(Vertex));
    VAO.BindElementBuffer(EBO);

    batchVBO.NamedBufferSubData(0, sizeof(Cube) * vertices.size(), vertices.data());

    float rotation = 0.0f;
    glEnable(GL_DEPTH_TEST);
    while (window.IsRunning()) {
        camera.OnUpdate();
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = camera.GetProjectionMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, -0.5f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 1, 1));

        glViewport(0, 0, window.Width(), window.Height());
        glClearColor(0.34f, 0.68f, 0.82f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        VAO.Bind();
        glBindTextureUnit(0, tex);
        shader.uni1i("u_tex", 0);
        shader.uni4mat("u_proj", glm::value_ptr(projection));
        shader.uni4mat("u_view", glm::value_ptr(view));
        shader.uni4mat("u_model", glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        window.OnUpdate();
    }
}

void RunTest() {
    fr::Window window{800, 800, "Radcraft"};

    // Indices for drawing the cube with triangles
    std::vector<unsigned int> indices = CreateIndices(maxCubes);
    std::vector<Cube> vertices;


    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 1; y++) {
            for (int z = 0; z < 32; z++) {
                glm::vec3 pos{x,sin(x + z),z};
                vertices.emplace_back(CreateCube(pos));
            }
        }
    }

    fr::Camera camera{window, 90.0f};
    gladLoadGL();

    int widthImg = 0, heightImg = 0, numColCh = 0;
    unsigned char *bytes = stbi_load(RESOURCES_PATH "terrain.png", &widthImg, &heightImg, &numColCh, 0);

    GLuint tex;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);

    glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureStorage2D(tex, 1, GL_RGBA8, widthImg, heightImg);
    glTextureSubImage2D(tex, 0, 0, 0, widthImg, heightImg, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateTextureMipmap(tex);

    stbi_image_free(bytes);


    while (window.IsRunning()) {
        window.OnUpdate();
    }
}

int main() {
    try {
        Run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }
}
