//
// Created by AlNov on 23.02.2021.
//

#ifndef DRAW_MODEL_H
#define DRAW_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <filesystem>

#include "mesh.h"

class Model {
public:

    explicit Model(const std::filesystem::path &path)
            : directory_(path.parent_path()) {
        loadModel(path);
    }

    void Draw(const Shader &shader);

private:
    std::vector<Mesh> meshes_;
    std::filesystem::path directory_;
    std::vector<TextureStruct> textures_loaded;

    void loadModel(const std::filesystem::path &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(const aiMesh *mesh, const aiScene *scene);

    std::vector<TextureStruct> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);

    static unsigned int TextureFromFile(const std::string &path, bool gamma = false);
};

void Model::loadModel(const std::filesystem::path &path) {
    Assimp::Importer import;

    const aiScene *scene = import.ReadFile(path.string(), aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

void Model::Draw(const Shader &shader) {
    for (auto &mesh : meshes_) {
        mesh.Draw(shader);
    }
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (auto i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.push_back(processMesh(mesh, scene));
    }

    for (auto i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(const aiMesh *mesh, const aiScene *scene) {
    std::cout << "Processing mesh [ " << mesh->mName.C_Str() << " ]\n";

    std::vector<VertexStruct> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureStruct> textures;

    // Vertex
    std::cout << "----Loading vertices\n";
    std::cout << "--------Loading [" << mesh->mNumVertices << "] vertices" << std::endl;
    for (auto i = 0; i < mesh->mNumVertices; i++) {
        VertexStruct vertex{};

        if (mesh->HasPositions()) {
            vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        } else {
            vertex.position = {0.0f, 0.0f, 0.0f};
        }

        if (mesh->HasNormals()) {
            vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
        } else {
            vertex.normal = {0.0f, 0.0f, 0.0f};
        }

        if (mesh->HasTextureCoords(0)) {
            vertex.tex_coords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        } else {
            vertex.tex_coords = {0.0f, 0.0f};
        }

        vertices.push_back(vertex);
    }

    // Index
    std::cout << "----Loading indexes\n";
    if (mesh->HasFaces()) {
        std::cout << "--------Loading [" << mesh->mNumFaces << "] faces" << std::endl;
        for (auto i = 0; i < mesh->mNumFaces; i++) {
            for (auto j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
                indices.push_back(mesh->mFaces[i].mIndices[j]);
            }
        }
    }

    // Texture
    std::cout << "----Loading textures for mesh\n";
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<TextureStruct> diffuseMaps = loadMaterialTextures(
                material, aiTextureType_DIFFUSE, TextureStruct::diffuse_str
        );
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<TextureStruct> specularMaps = loadMaterialTextures(
                material, aiTextureType_SPECULAR, TextureStruct::specular_str
        );
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        std::cout << std::endl;
    }

    return {std::move(vertices), std::move(indices), std::move(textures)};
}

std::vector<TextureStruct>
Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName) {
    std::vector<TextureStruct> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::cout << "--------Mesh wanded tex: " << str.C_Str() << " \t";

        std::filesystem::path texPath = str.C_Str();
        if (texPath.is_absolute()) {
            texPath = directory_ / texPath.filename();
        } else {
            texPath = directory_ / texPath;
        }

        bool already_loaded = false;
        for (auto & texture_loaded : textures_loaded) {
            if (texture_loaded.path == texPath.string()) {
                std::cout << " Tex exist: " << texture_loaded.path << std::endl;
                textures.push_back(texture_loaded);
                already_loaded = true;
                break;
            }
        }
        if (!already_loaded) {
            TextureStruct texture {TextureFromFile(texPath.string()), typeName, texPath.string()};
            if (texture.id) {
                std::cout << " Loaded Tex: " << texture.path << std::endl; //
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
    }
    return std::move(textures);
}

unsigned int Model::TextureFromFile(const std::string &path, bool gamma) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width;
    int height;
    int nrComponents;
    unsigned char *data = SOIL_load_image(path.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SOIL_free_image_data(data);
    } else {
        glDeleteTextures(1, &textureID);
        textureID = 0;
        std::cout << "Texture failed to load at path: " << path << std::endl;
        SOIL_free_image_data(data);
    }

    return textureID;
}


#endif //DRAW_MODEL_H
