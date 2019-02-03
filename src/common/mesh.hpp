#pragma once

#include <program.hpp>
#include <texture.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <vector>

class Mesh {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    struct MaterialTexture {
        std::shared_ptr<Texture> texture;
        std::string type;
        std::string path;
    };

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MaterialTexture> textures);

    void draw(const Program &program) const;

private:
    /*  Mesh Data  */
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<MaterialTexture> _textures;

    /*  Render data  */
    unsigned int vao, vbo, ibo;

private:
    void init();
};