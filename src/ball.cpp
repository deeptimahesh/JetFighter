#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z, float length, float width, float height, float wingspan) {
    this-> position = glm::vec3(x, y, z);
    this-> height = height;
    this-> width = width;
    this-> length = length;
    this-> wingspan = wingspan;
    this-> rotation = 0;
    this-> speedy = 0.07;
    this-> speedx = 0.05;

    float w = width / 2, l = length / 2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat wings_buffer_data[] = {
        -w, 0.45f, l-0.8f,
        -w-wingspan, 0.45f, l - 0.3f,
        -w, 0.45f, -l,

        w, 0.45f, l - 0.8f,
        w+wingspan, 0.45f, l - 0.3f,
        w, 0.45f, -l,

        -w-wingspan, 0.45f, l - 0.3f,
        -w, 0.2f, l-0.8f,
        -w, 0.2f, -l,

        w, 0.2f, l - 0.8f,
        w+wingspan, 0.45f, l - 0.3f,
        w, 0.2f, -l, 

        -w, 0.45f, l-0.8f,        
        -w, 0.2f, l-0.8f,
        -w-wingspan, 0.45f, l - 0.3f,

        -w, 0.45f, -l,
        -w, 0.2f, -l,
        -w-wingspan, 0.45f, l - 0.3f,    

        w, 0.45f, l - 0.8f,
        w, 0.2f, l - 0.8f,
        w+wingspan, 0.45f, l - 0.3f,

        w, 0.45f, -l,
        w, 0.2f, -l, 
        w+wingspan, 0.45f, l - 0.3f,

    };

    this->wings = create3DObject(GL_TRIANGLES, 3*8, wings_buffer_data, COLOR_BLACK, GL_FILL);
    
    static const GLfloat tail_buffer_data[] = {
        -w - 0.15, 0.45f, l-0.2f,
        -w-(wingspan/3)-0.15f, 0.45f, l - 0.1f,
        -w-0.15f, 0.45f, -l + 1.6f,

        w+0.15f, 0.45f, l - 0.2f,
        w+(wingspan/3)+0.15f, 0.45f, l - 0.1f,
        w+0.15f, 0.45f, -l + 1.6f,

        -w-(wingspan/3) - 0.15f, 0.45f, l - 0.1f,
        -w-0.15f, 0.2f, l-0.2f,
        -w-0.15f, 0.2f, -l + 1.6f,

        w + 0.15f, 0.2f, l - 0.2f,
        w+(wingspan/3)+0.15f, 0.45f, l - 0.1f,
        w+0.15f, 0.2f, -l + 1.6f, 

        -w-0.15f, 0.45f, l-0.2f,        
        -w-0.15f, 0.2f, l-0.2f,
        -w-(wingspan/3)-0.15f, 0.45f, l - 0.1f,

        -w-0.15f, 0.45f, -l + 1.6f,
        -w-0.15f, 0.2f, -l + 1.6f,
        -w-(wingspan/3)-0.15f, 0.45f, l - 0.1f,    

        w+0.15f, 0.45f, l - 0.2f,
        w+0.15f, 0.2f, l - 0.2f,
        w+(wingspan/3)+0.15f, 0.45f, l - 0.1f,

        w+0.15f, 0.45f, -l + 1.6f,
        w+0.15f, 0.2f, -l + 1.6f, 
        w+(wingspan/3)+0.15f, 0.45f, l - 0.1f,

        

    };

    this->tails = create3DObject(GL_TRIANGLES, 3*8, tail_buffer_data, COLOR_RED, GL_FILL);
    
    static const GLfloat base_buffer_data[] = {
        -w, 0.0f, -l,
        w, 0.0f, -l,
        -w, 0.0f, l,
        -w, 0.0f, l,
        w, 0.0f, l,
        w, 0.0f, -l
        
    };

    this->base = create3DObject(GL_TRIANGLES, 2*3, base_buffer_data, COLOR_GREEN, GL_FILL);

    static const GLfloat top_buffer_data[] = {
        -w, height, -l,
        w, height, -l,
        -w, height, l,
        -w, height, l,
        w, height, l,
        w, height, -l
    };  
    this->top = create3DObject(GL_TRIANGLES, 2*3, top_buffer_data, COLOR_RED, GL_FILL);

    static const GLfloat sides_rect[] = {
            -w, 0.0f, -l,
            -w, 0.0f, l,
            -w - 0.7f * w, height, -l,
            -w - 0.7f * w, height, -l,
            -w - 0.7f * w, height, l,
            -w, 0.0f, l,

            w, 0.0f, -l,
            w, 0.0f, l,
            w + 0.7f * w, height, -l,
            w + 0.7f * w, height, -l,
            w + 0.7f * w, height, l,
            w, 0.0f, l,
    };

    this->sides = create3DObject(GL_TRIANGLES, 4*3, sides_rect, COLOR_BLACK, GL_FILL);

    static const GLfloat back_trgs[] = {
            -w, 0.0f, -l,
            w, 0.0f, -l,
            -w - 0.7f * w, height, -l,
            -w - 0.7f * w, height, -l,
            w + 0.7f * w, height, -l,
            w, 0.0f, -l,
    };

    this->back = create3DObject(GL_TRIANGLES, 2 * 3, back_trgs, COLOR_BLACK, GL_FILL);

    static const GLfloat front_trgs[] = {
            -w, 0.0f, l,
            w, 0.0f, l,
            -w - 0.7f * w, height, l,
            -w - 0.7f * w, height, l,
            w + 0.7f * w, height, l,
            w, 0.0f, l,
    };

    this->front = create3DObject(GL_TRIANGLES, 2 * 3, front_trgs, COLOR_BLACK, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->sides);
    draw3DObject(this->front);
    draw3DObject(this->base);
    draw3DObject(this->back);
    draw3DObject(this->top);
    draw3DObject(this->wings);
    draw3DObject(this->tails);
    //draw3DObject(this->object);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}


Horizon::Horizon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // flat square with 2 triangles => 2*3 = 6 vertices
    static const GLfloat vertex_buffer_data[] = {
        50.5f, 50.6f, 0.0f,
        50.5f, -1.5f, 0.0f,
        -50.5f, -1.5f, 0.0f,
        50.5f, 50.6f, 0.0f,
        -50.5f, 50.6f, 0.0f,
        -50.5f, -1.5f, 0.0f,
        
        //if you want different colors, have to keep track of their points and move it too :/
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Horizon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Horizon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Horizon::tick() {
    //this->rotation += speed;
    //this->position.x += ball1.position.x;
    
}

