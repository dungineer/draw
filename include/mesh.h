
#ifndef DRAW_MESH_H
#define DRAW_MESH_H


#include <utility>

#include "shader.h"

struct VertexStruct {


    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

struct TextureStruct {
    static constexpr char diffuse_str[] = "texture_diffuse";
    static constexpr char specular_str[] = "texture_specular";

    unsigned int id = 0;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<VertexStruct> vertices_;
    std::vector<unsigned int> indices_;
    std::vector<TextureStruct> textures_;

    Mesh(std::vector<VertexStruct> &&vertices,
         std::vector<unsigned int> &&indices,
         std::vector<TextureStruct> &&textures);

    Mesh(const std::vector<VertexStruct> &vertices,
         const std::vector<unsigned int> &indices,
         const std::vector<TextureStruct> &textures);

    void Draw(const Shader &shader) const;

private:

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    void setupMesh();
};

Mesh::Mesh(
        std::vector<VertexStruct> &&vertices,
        std::vector<unsigned int> &&indices,
        std::vector<TextureStruct> &&textures
) {
    vertices_ = vertices;
    indices_ = indices;
    textures_ = textures;

    setupMesh();
}

Mesh::Mesh(
        const std::vector<VertexStruct> &vertices,
        const std::vector<unsigned int> &indices,
        const std::vector<TextureStruct> &textures
) {
    vertices_ = vertices;
    indices_ = indices;
    textures_ = textures;

    setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(VertexStruct), &vertices_[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), (void *)nullptr);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), (void *)offsetof(VertexStruct, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), (void *) offsetof(VertexStruct, tex_coords));

    glBindVertexArray(0);
}

void Mesh::Draw(const Shader &shader) const {
    unsigned int diffuse_n = 1;
    unsigned int specular_n = 1;
    for (unsigned int i = 0; i < textures_.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string texture_name = "material.";

        if (textures_.at(i).type == TextureStruct::diffuse_str) {
            texture_name += TextureStruct::diffuse_str;
            texture_name += std::to_string(diffuse_n);
        } else if (textures_.at(i).type == TextureStruct::specular_str) {
            texture_name += TextureStruct::specular_str;
            texture_name += std::to_string(specular_n);
        }

        shader.setUniformInt(texture_name, i);
        glBindTexture(GL_TEXTURE_2D, textures_[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

#endif //DRAW_MESH_H
