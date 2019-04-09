#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 10;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

        0.75f,0.3f,1.f,
        0.75f,0.3f,-1.f,
        0.5f,-0.5f,0.75f,


        0.5f,-0.5f,-0.75f,
        0.75f,0.3f,-1.f,
        0.5f,-0.5f,0.75f,



        -0.5f,0.3f,1.f,
        -0.5f,0.3f,-1.f,
        0.f,-0.5f,0.75f,


        0.f,-0.5f,-0.75f,
        -0.5f,0.3f,-1.f,
        0.f,-0.5f,0.75f,


        0.75f,0.3f,1.f,
        0.5f,-0.5f,0.75f,
        -0.5f,0.3f,1.f,


        0.f,-0.5f,0.75f,
        0.5f,-0.5f,0.75f,
        -0.5f,0.3f,1.f,



        0.75f,0.3f,-1.f,
        0.5f,-0.5f,-0.75f,
        -0.5f,0.3f,-1.f,

        0.f,-0.5f,-0.75f,
        0.5f,-0.5f,-0.75f,
        -0.5f,0.3f,-1.f,


        0.75f,0.3f,1.f,
        -0.5f,0.3f,1.f,
        -0.5f,0.3f,-1.f,


        0.75f,0.3f,1.f,
        0.75f,0.3f,-1.f,
        -0.5f,0.3f,-1.f,

    };
    float angle=0;
    float r = 0.4;

    GLfloat vertex_buffer_data1[360*5*2*3] ;
    for(int i=0;i<360*5*2*3;i++)
    {
        vertex_buffer_data1[i++]= r*cos(angle);
        vertex_buffer_data1[i++]= 0.3f;
        vertex_buffer_data1[i++]=r*sin(angle);


        vertex_buffer_data1[i++]= r*cos(angle);
        vertex_buffer_data1[i++]= 0.6f;
        vertex_buffer_data1[i]=r*sin(angle);

        angle+=M_PI/(90*5*2);
    }
angle=0;
    GLfloat vertex_buffer_data2[360*9];
    for(int i=0;i<360*9;i++)
    {
            vertex_buffer_data2[i++]=0.0f;
            vertex_buffer_data2[i++]=0.6f;
            vertex_buffer_data2[i++]=0.0f;

            vertex_buffer_data2[i++]=r*cos(angle);
            vertex_buffer_data2[i++]=0.6f;
            vertex_buffer_data2[i++]= r*sin(angle);


            vertex_buffer_data2[i++]= r*cos(angle+M_PI/180);
            vertex_buffer_data2[i++]= 0.6f;
            vertex_buffer_data2[i]=r*sin(angle+M_PI/180);

           angle+=M_PI/180;
     }


    GLfloat vertex_buffer_data3[]={

        0.25f,0.25f,1.f,
        0.25,0.f,0.75f,
        0.25f,0.1f,2.f,

        0.25f,0.25f,-1.f,
        0.25,0.f,-0.75f,
        0.25f,0.1f,-2.f,
    };







   this->object[0] = create3DObject(GL_TRIANGLES,10*3, vertex_buffer_data, color, GL_FILL);
    this->object[1] = create3DObject(GL_LINES,360*5*2, vertex_buffer_data1, COLOR_BOAT, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES,360*3, vertex_buffer_data2, COLOR_BARREL, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES,2*3, vertex_buffer_data3, COLOR_RED, GL_FILL);

}

void Monster::draw(glm::mat4 VP) {
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
    draw3DObject(this->object[3]);

}

void Monster::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Monster::tick() {
    this->rotation += speed;


    // this->position.y -= speed;
}
bounding_box_t Monster::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z=this->position.z;
    bounding_box_t bbox = { x, y, z};
    return bbox;
}

