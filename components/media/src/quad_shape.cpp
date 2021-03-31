#include <quad_shape.h>


namespace {
    constexpr float DEFAULT_QUAD_VERTICES[] = {
            0.0F, 1.0F, 0.0F, 1.0F,
            1.0F, 0.0F, 1.0F, 0.0F,
            0.0F, 0.0F, 0.0F, 0.0F,

            0.0F, 1.0F, 0.0F, 1.0F,
            1.0F, 0.0F, 1.0F, 0.0F,
            1.0F, 1.0F, 1.0F, 1.0F
    };
}

QuadShape::QuadShape() {
    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(DEFAULT_QUAD_VERTICES), DEFAULT_QUAD_VERTICES, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    VAO_ = VAO;
}

void QuadShape::draw() const {
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
