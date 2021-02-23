//
// Created by AlNov on 07.02.2021.
//

#ifndef DRAW_TEXTURE_H
#define DRAW_TEXTURE_H

#include <SOIL/SOIL.h>
#include <GL/glew.h>


class Texture {
public:
    explicit Texture(const std::string &texturePath1, const std::string &texturePath2, const std::string &texturePath3) {
        int width = 0;
        int height = 0;

        // First
        unsigned char *image = SOIL_load_image(
                texturePath1.c_str(), &width, &height, nullptr, SOIL_LOAD_RGB
        );
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);

        // Second
        image = SOIL_load_image(
                texturePath2.c_str(), &width, &height, nullptr, SOIL_LOAD_RGB
        );
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);

        // Third
        image = SOIL_load_image(
                texturePath3.c_str(), &width, &height, nullptr, SOIL_LOAD_RGB
        );
        glGenTextures(1, &texture3);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);
    }

    void use(GLuint program) const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(program, "material.diffuse"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(program, "material.specular"), 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glUniform1i(glGetUniformLocation(program, "material.emission"), 2);
    }

private:
    GLuint texture1 = 0;
    GLuint texture2 = 0;
    GLuint texture3 = 0;
};


#endif //DRAW_TEXTURE_H
