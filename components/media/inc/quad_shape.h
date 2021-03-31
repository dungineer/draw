#ifndef DRAW_QUAD_SHAPE_H
#define DRAW_QUAD_SHAPE_H


#include <GL/glew.h>

#include <abstract_shape.h>


class QuadShape : public AbstractShape {
public:
    QuadShape();

    ~QuadShape() {
        glDeleteVertexArrays(1, &VAO_);
    }

    void draw() const override;

private:
    unsigned int VAO_{};
};


#endif //DRAW_QUAD_SHAPE_H
