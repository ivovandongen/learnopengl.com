#pragma once

#include <mesh.hpp>

#include <assimp/scene.h>

class Model {
public:
    explicit Model(const std::string &path);

    void draw(const Program &program) const;

    const std::vector<Mesh>& meshes() const {
        return _meshes;
    }

private:
    std::vector<Mesh::MaterialTexture> _loadedTextures;
    std::vector<Mesh> _meshes;
    std::string _directory;

private:
    void loadModel(const std::string &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Mesh::MaterialTexture>
    loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
};