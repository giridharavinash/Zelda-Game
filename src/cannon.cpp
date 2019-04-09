#include "cannon.h"
#include "main.h"



Cannon::Cannon(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 0;
    float angle=0;
    float r=0.1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     GLfloat vertex_buffer_data[360*2*3];

        for(int i=0;i<360*2*3;i++)
        {
            vertex_buffer_data[i++]= 0.5f;
            vertex_buffer_data[i++]= r*cos(angle);
            vertex_buffer_data[i++]=r*sin(angle);


            vertex_buffer_data[i++]= -4.f;
            vertex_buffer_data[i++]= r*cos(angle);
            vertex_buffer_data[i]=r*sin(angle);

            angle+=M_PI/180;
        }
    this->object = create3DObject(GL_LINES,360*2, vertex_buffer_data, color, GL_FILL);

}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

     draw3DObject(this->object);
}

void Cannon::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {


    this->speed=this->speed-0.01;
    this->position.y+=speed;
    if(this->position.y<-0.2)
        this->position.y=-0.2;

}

