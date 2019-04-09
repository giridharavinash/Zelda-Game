#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 5;
    float r=0.3;
    float angle=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[360*2*3];

       for(int i=0;i<360*2*3;i++)
       {
           vertex_buffer_data[i++]= 0.05f;
           vertex_buffer_data[i++]= r*cos(angle);
           vertex_buffer_data[i++]=r*sin(angle);


           vertex_buffer_data[i++]= -0.05f;
           vertex_buffer_data[i++]= r*cos(angle);
           vertex_buffer_data[i]=r*sin(angle);

           angle+=M_PI/180;
       }
angle=0;

       GLfloat vertex_buffer_data1[360*9];
       for(int i=0;i<360*9;i++)
       {
               vertex_buffer_data1[i++]=0.05f;
               vertex_buffer_data1[i++]=0.f;
               vertex_buffer_data1[i++]=0.f;

               vertex_buffer_data1[i++]=0.05f;
               vertex_buffer_data1[i++]=r*cos(angle);
               vertex_buffer_data1[i++]=r*sin(angle);


               vertex_buffer_data1[i++]=0.05f;
               vertex_buffer_data1[i++]= r*cos(angle+M_PI/180);
               vertex_buffer_data1[i]=r*sin(angle+M_PI/180);

              angle+=M_PI/180;
        }


       GLfloat vertex_buffer_data2[360*9];
       for(int i=0;i<360*9;i++)
       {
               vertex_buffer_data2[i++]=-0.05f;
               vertex_buffer_data2[i++]=0.f;
               vertex_buffer_data2[i++]=0.f;

               vertex_buffer_data2[i++]=-0.05f;
               vertex_buffer_data2[i++]=r*cos(angle);
               vertex_buffer_data2[i++]=r*sin(angle);


               vertex_buffer_data2[i++]=-0.05f;
               vertex_buffer_data2[i++]= r*cos(angle+M_PI/180);
               vertex_buffer_data2[i]=r*sin(angle+M_PI/180);

              angle+=M_PI/180;
        }




   this->object[0] = create3DObject(GL_LINES,360*2, vertex_buffer_data, COLOR_BOSS, GL_FILL);
    this->object[1]=  create3DObject(GL_TRIANGLES,360*3, vertex_buffer_data1, color, GL_FILL);
       this->object[2]= create3DObject(GL_TRIANGLES,360*3, vertex_buffer_data2, color, GL_FILL);


}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);

}

void Coin::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Coin::tick() {
    this->rotation += this->speed;


    // this->position.y -= speed;
}
bounding_box_t Coin::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z=this->position.z;
    bounding_box_t bbox = { x, y, z};
    return bbox;
}

