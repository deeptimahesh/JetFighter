#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, float length, float width, float height, float wingspan);
    glm::vec3 position;
    float rotation;
    float width, length, height, wingspan;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float speedx, speedy;
private:
    VAO *base;
    VAO *object;
    VAO *sides;
    VAO *front;
    VAO *back;
    VAO *top;
    VAO *wings;
    VAO *tails;
};

#endif // BALL_H

#ifndef HORIZON_H
#define HORIZON_H
class Horizon {
public:
    Horizon() {}
    Horizon(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    

private:
    VAO *object;
};
#endif // HORIZON_H


