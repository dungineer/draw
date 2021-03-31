#ifndef DRAW_ABSTRACT_SHAPE_H
#define DRAW_ABSTRACT_SHAPE_H


class AbstractShape {
public:
    AbstractShape() = default;

    AbstractShape(const AbstractShape &) = delete;

    virtual ~AbstractShape() = default;

    virtual void draw() const = 0;
};


#endif //DRAW_ABSTRACT_SHAPE_H
