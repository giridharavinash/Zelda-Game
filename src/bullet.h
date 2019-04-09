#include "main.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BULLET_H
