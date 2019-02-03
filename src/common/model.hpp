#pragma once

#include <mesh.hpp>

#include <assimp/scene.h>

class Model {
public:
    explicit Model(const std::string &path);

    void draw(const Program &program) const;

private:
    std::vector<Mesh::MaterialTexture> _loadedTextures;
    std::vector<Mesh> meshes;
    std::string directory;

private:
    void loadModel(const std::string &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Mesh::MaterialTexture>
    loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
};