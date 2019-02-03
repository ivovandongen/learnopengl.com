#include "model.hpp"

#include <texture.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <algorithm>
#include <iostream>

Model::Model(const std::string &path) {
    loadModel(path);
}

void Model::draw(const Program &program) const {
    for (const auto &mesh : meshes) {
        mesh.draw(program);
    }
}

void Model::loadModel(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Mesh::Vertex> vertices{};
    std::vector<unsigned int> indices{};
    std::vector<Mesh::MaterialTexture> textures{};

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec2 texCoords(0.0f, 0.0f);
        // does the mesh contain texture coordinates?
        if (mesh->mTextureCoords[0]) {
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
        }

        Mesh::Vertex vertex{
                // Position
                {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
                // Normal
                {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z},
                // Texcoords
                texCoords
        };

        vertices.push_back(vertex);
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Mesh::MaterialTexture> diffuseMaps = loadMaterialTextures(
                material,
                aiTextureType_DIFFUSE,
                "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Mesh::MaterialTexture> specularMaps = loadMaterialTextures(
                material,
                aiTextureType_SPECULAR,
                "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Mesh::MaterialTexture>
Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName) {
    std::vector<Mesh::MaterialTexture> textures{};
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        const auto &found = std::find_if(
                std::begin(_loadedTextures),
                std::end(_loadedTextures),
                [&str](const Mesh::MaterialTexture &t) {
                    return std::strcmp(t.path.data(), str.C_Str()) == 0;
                });

        if (found != std::end(_loadedTextures)) {
            textures.push_back(*found);
        } else {
            // if texture hasn't been loaded already, load it and add to loaded textures
            Mesh::MaterialTexture mt{
                    std::make_shared<Texture>(Image{directory + '/' + str.C_Str()}, true),
                    typeName,
                    std::string{str.C_Str()}
            };
            textures.push_back(mt);
            _loadedTextures.push_back(mt);
        }
    }
    return textures;
}
