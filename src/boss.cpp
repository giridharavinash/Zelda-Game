#include "boss.h"
#include "main.h"

Boss::Boss(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.5;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

                4.f,0.9f,5.f,
                4.f,0.9f,-5.f,
                4.f,-0.5f,4.f,

                4.f,-0.5f,-4.f,
                4.f,0.9f,-5.f,
                4.f,-0.5f,4.f,


                   0.f,0.9f,5.f,
                   0.f,0.9f,-5.f,
                   0.f,-0.5f,4.f,

                    0.f,-0.5f,-4.f,
                    0.f,0.9f,-5.f,
                   0.f,-0.5f,4.f,


                4.f,0.9f,5.f,
                0.f,0.9f,5.f,
                4.f,-0.5f,4.f,

                0.f,-0.5f,4.f,
                0.f,0.9f,5.f,
                4.f,-0.5f,4.f,


                4.f,0.9f,-5.f,
                4.f,-0.5,-4.f,
                0.f,0.9f,-5.f,

                0.f,-0.5f,-4.f,
                4.f,-0.5,-4.f,
                0.f,0.9f,-5.f,


                4.f,0.9f,5.f,
                4.f,0.9f,-5.f,
                0.f,0.9f,5.f,


                0.f,0.9f,-5.f,
                4.f,0.9f,-5.f,
                0.f,0.9f,5.f,
  };

    GLfloat vertex_buffer_data1[]={

                4.1f,0.4f,3.f,
                4.1f,0.4f,0.f,
                4.1f,0.1f,1.5f,

                4.1f,0.4f,-3.f,
                4.1f,0.4f,0.f,
                4.1f,0.1f,-1.5f


    } ;
    float r=0.3;
    float angle=0;

    GLfloat vertex_buffer_data2[360*9];
    for(int i=0;i<360*9;i++)
    {
            vertex_buffer_data2[i++]=4.2f;
            vertex_buffer_data2[i++]=1.2f;
            vertex_buffer_data2[i++]=2.f;

            vertex_buffer_data2[i++]=4.2f;
            vertex_buffer_data2[i++]=1.2f+r*cos(angle);
            vertex_buffer_data2[i++]=2.f+ r*sin(angle);


            vertex_buffer_data2[i++]=4.2f;
            vertex_buffer_data2[i++]= 1.2f+ r*cos(angle+M_PI/180);
            vertex_buffer_data2[i]=2.f+r*sin(angle+M_PI/180);

           angle+=M_PI/180;
     }

    GLfloat vertex_buffer_data3[360*9];
    for(int i=0;i<360*9;i++)
    {
            vertex_buffer_data3[i++]=4.2f;
            vertex_buffer_data3[i++]=1.2f;
            vertex_buffer_data3[i++]=-2.f;

            vertex_buffer_data3[i++]=4.2f;
            vertex_buffer_data3[i++]=1.2f+r*cos(angle);
            vertex_buffer_data3[i++]=-2.f+ r*sin(angle);


            vertex_buffer_data3[i++]=4.2f;
            vertex_buffer_data3[i++]= 1.2f+ r*cos(angle+M_PI/180);
            vertex_buffer_data3[i]=-2.f+r*sin(angle+M_PI/180);

           angle+=M_PI/180;
     }





    this->object[0] = create3DObject(GL_TRIANGLES,10*3, vertex_buffer_data, COLOR_BOSS , GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES,2*3, vertex_buffer_data1, COLOR_RED , GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES,360*3, vertex_buffer_data2, COLOR_RED , GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES,360*3, vertex_buffer_data3, COLOR_RED , GL_FILL);

}

void Boss::draw(glm::mat4 VP) {
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

void Boss::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss::tick() {

    this->speed=this->speed-0.01;
    this->position.y+=speed;
    if(this->position.y<-0.7)
     {

        this->position.y=-0.7;
        this->speed=0.5;
    }
//    if(rand()%2 && rand()%100==0)
//    {
//        this->position.z+=2;
//    }
//    else if(rand()%50==0)
//        this->position.z-=2;



    // this->position.y -= speed;
}
bounding_box_t Boss::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z=this->position.z;
    bounding_box_t bbox = { x, y, z};
    return bbox;
}

