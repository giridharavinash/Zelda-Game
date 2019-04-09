#include "boat.h"
#include "main.h"

int count =0;

Boat::Boat(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

          2.f,-0.99f,1.f,
          -2.f,-0.99f,1.f,
        -2.f,-0.99f,-1.f,
        -2.f,-0.99f,-1.f,
        2.f,-0.99f,-1.f,
        2.f,-0.99f,1.f,

        -2.f,-0.99f,-1.f,
        -2.f,-0.99f,1.f,
        -4.f,-0.99f,0.f
        };
    GLfloat vertex_buffer_data1[]={
        -3.f,-0.5f,-2.f,
        3.f,-0.5f,-2.f,
        2.f,-0.99f,-1.f,
        -3.f,-0.5f,-2.f,
        -2.f,-0.99f,-1.f,
        2.f,-0.99f,-1.f,


        -3.f,-0.5f,2.f,
        3.f,-0.5f,2.f,
        2.f,-0.99f,1.f,
        -3.f,-0.5f,2.f,
        -2.f,-0.99f,1.f,
        2.f,-0.99f,1.f
    };
    GLfloat vertex_buffer_data2[]={
        3.f,-0.5f,2.f,
        3.f,-0.5f,-2.f,
        2.f,-0.99f,-1.f,
        3.f,-0.5f,2.f,
        2.f,-0.99f,1.f,
        2.f,-0.99f,-1.f,




        -4.0f,-0.99f,0.f,
        -2.f,-0.99f,-1.f,
        -3.f,-0.5f,-2.f,



        -4.0f,-0.99f,0.f,
        -2.f,-0.99f,1.f,
        -3.f,-0.5f,2.f,


        -4.0f,-0.99f,0.f,
        -4.f,-0.5f,0.f,
        -3.f,-0.5f,-2.f,

        -4.0f,-0.99f,0.f,
        -4.f,-0.5f,0.f,
        -3.f,-0.5f,2.f

  };

    GLfloat vertex_buffer_data3[]={

        0.55f,-0.99f,0.1f,
        0.55f,-0.99f,-0.1f,
        0.55f,3.f,-0.1f,

        0.55f,-0.99f,0.1f,
        0.55f,3.f,0.1f,
        0.55f,3.f,-0.1f,
    };

    GLfloat vertex_buffer_data4[]={

        0.55f,0.f,0.0f,
        2.5f,0.f,1.f,
        0.55f,3.f,0.0f

    };


    this->object[0] = create3DObject(GL_TRIANGLES,3*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES,4*3, vertex_buffer_data1, COLOR_BOAT, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES,6*3, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES,2*3, vertex_buffer_data3, COLOR_RED, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES,1*3, vertex_buffer_data4, COLOR_RED, GL_FILL);

}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<5;i++)
     draw3DObject(this->object[i]);
}

void Boat::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {


    this->speed=this->speed-0.01;
    this->position.y+=speed;
    if(this->position.y<0)
        this->position.y=0;

}


bounding_box_t Boat::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z=this->position.z;
    bounding_box_t bbox = { x, y, z};
    return bbox;
}

