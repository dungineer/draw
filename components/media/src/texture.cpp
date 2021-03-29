#include <texture.h>

unsigned int Texture2D::loadImage_(const std::filesystem::path &tex_path) {
    int w = 0;
    int h = 0;

    unsigned int texID = 0;

    auto image = SOIL_load_image(tex_path.string().c_str(), &w, &h, nullptr, SOIL_LOAD_RGB);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);

    return texID;
}

void Texture2D::use() const {
    int curr_program = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &curr_program);

    for (size_t i = 0; i < textures_.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures_[i].first);
        glUniform1i(glGetUniformLocation(static_cast<unsigned int>(curr_program), textures_[i].second.c_str()), i);
    }

    glActiveTexture(GL_TEXTURE0);
}
