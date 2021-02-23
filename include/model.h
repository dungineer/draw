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
            : directory_(path) {
        loadModel(path);
    }

    void Draw(Shader shader);

private:
    std::vector<Mesh> meshes_;
    std::filesystem::path directory_;
    std::vector<TextureStruct> textures_loaded;

    void loadModel(const std::filesystem::path &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<TextureStruct> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);

    static unsigned int TextureFromFile(const std::string &path, bool gamma = false);
};

void Model::loadModel(const std::filesystem::path &path) {
    Assimp::Importer import;

    const aiScene *scene = import.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory_ = path.parent_path().string();

    processNode(scene->mRootNode, scene);
}

void Model::Draw(Shader shader) {
    for (auto &mesh : meshes_) {
        mesh.draw(shader);
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

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<VertexStruct> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureStruct> textures;


    for (auto i = 0; i < mesh->mNumVertices; i++) {
        VertexStruct vertex{};

        vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
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

    for (auto i = 0; i < mesh->mNumFaces; i++) {
        for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
            indices.push_back(mesh->mFaces[i].mIndices[j]);
        }
    }

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
    }

    return Mesh(vertices, indices, textures);
}

std::vector<TextureStruct>
Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName) {
    std::vector<TextureStruct> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::cout << "Wanted Tex: " << str.C_Str(); //
        std::filesystem::path texPath = str.C_Str();
        texPath = "models/backpack/" + texPath.filename().string();
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded.at(j).path.c_str(), texPath.string().c_str()) == 0) {
                std::cout << " Loaded Tex: " << textures_loaded[j].path << std::endl;
                textures.push_back(textures_loaded.at(j));
                skip = true;
                break;
            }
        }
        if (!skip) {
            TextureStruct texture;
            texture.id = TextureFromFile(texPath.string());
            texture.type = typeName;
            texture.path = texPath.string();
            std::cout << " Loaded Tex: " << texture.path << std::endl; //
            textures.push_back(texture);

            textures_loaded.push_back(texture);
        }
    }
    return textures;
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
        std::cout << "Texture failed to load at path: " << path << std::endl;
        SOIL_free_image_data(data);
    }

    return textureID;
}


#endif //DRAW_MODEL_H
