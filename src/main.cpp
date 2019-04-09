#include "main.h"
#include "timer.h"
#include "ball.h"
#include "boat.h"
#include "rock.h"
#include "barrel.h"
#include "cannon.h"
#include "bullet.h"
#include "gift.h"
#include "monster.h"
#include "boss.h"
#include "coin.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
mizable functions *
**************************/

int buf[10000]={};
int boostcount=0;
int cnt=0;
int cnt2=0;
int moncnt=0;
int points=0;
float health = 100;
int bosf=0;
int boost=0;
int bocnt=0;
int boscnt=0;
int Bosses=0;
int cof[50]={};
int cocnt=0;
int coins=0;
int flag=1;
float camangle=0;
float radius = 2;



Gift booster[10];
Ball ball1;
Boss boss;
Boat boat;
Rock rock[20];
Coin coin[50];
Cannon cannon;
//Barrel barrel;
Gift gift[20];
Bullet bullet[1000];
Barrel barrel[20];
Monster monster[5];
int camview=0;
int wind = 0, count_wind = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);
Timer bosso(5);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!

  if(camview==0)
  {
     float angle = boat.rotation*M_PI/180;
    glm::vec3 eye (boat.position.x+ 5*cos(angle),boat.position.y +0.25,boat.position.z-5*sin(angle) );
    glm::vec3 target (boat.position.x,boat.position.y,boat.position.z);
    glm::vec3 up (0, 1, 0);
    Matrices.view = glm::lookAt( eye, target, up );
   }
  else if(camview==1)
  {
      glm::vec3 eye (boat.position.x,20,boat.position.z);
      glm::vec3 target (boat.position.x,boat.position.y,boat.position.z);
      glm::vec3 up (-1, 0, 0);
      Matrices.view = glm::lookAt( eye, target, up );

  }
  else if(camview==2)
  {

      float angle = boat.rotation*M_PI/180;
     glm::vec3 target(boat.position.x- 5*cos(angle),boat.position.y +0.25,boat.position.z+5*sin(angle) );
     glm::vec3 eye (boat.position.x,boat.position.y,boat.position.z);
     glm::vec3 up (0, 1, 0);
     Matrices.view = glm::lookAt( eye, target, up );


  }
  else if(camview==3)
  {
      glm::vec3 eye (5,5,0);
      glm::vec3 target (boat.position.x,boat.position.y,boat.position.z);
      glm::vec3 up (0, 1, 0);
      Matrices.view = glm::lookAt( eye, target, up );
  }
      else if(camview==4)
      {
          glm::vec3 eye (radius*cos(camangle*M_PI/180),15,radius*sin(camangle*M_PI/180));
           glm::vec3 target (boat.position.x,boat.position.y,boat.position.z);
          glm::vec3 up (cos(camangle*M_PI/180), 1, sin(camangle*M_PI/180));
          Matrices.view = glm::lookAt( eye, target, up );
      }



    // Compute Camera matrix (view)
    /*Matrices.view = glm::lookAt( eye, target, up );*/ // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    boat.draw(VP);
    for(int i=0;i<10;i++)
    {
        rock[i].draw(VP);
//        barrel[i].draw(VP);
        booster[i].draw(VP);

    }
    for(int i=0;i<10;i++)
    {
        barrel[i].draw(VP);
        gift[i].draw(VP);
    }
    cannon.draw(VP);
    for(int i=0;i<1000;i++)
      if(buf[i])
        bullet[i].draw(VP);
    for(int i=0;i<5;i++)
        monster[i].draw(VP);
    if(bosf)
        boss.draw(VP);
    for(int i=0;i<50;i++)
        if(cof[i])
            coin[i].draw(VP);
}

void bullet_throw()
{
    buf[cnt]=1;
    bullet[cnt].rotation=cannon.rotation;
    bullet[cnt++].position=cannon.position;
    system(" canberra-gtk-play -f  ../resources/cannon.wav --volume=\"0.00001\"   &");

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int z = glfwGetKey(window, GLFW_KEY_Z);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int top = glfwGetKey(window, GLFW_KEY_1);
    int front = glfwGetKey(window, GLFW_KEY_2);
    int tower = glfwGetKey(window, GLFW_KEY_3);
    int bot_f = glfwGetKey(window, GLFW_KEY_5);
    int boo = glfwGetKey(window, GLFW_KEY_B);
    int a  = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int hel = glfwGetKey(window, GLFW_KEY_4);

    cnt2++;
    if(hel)
        camview=4;

    float  k=0.3;
    if(boo && boostcount>0)
    {
        boost=1;
        boostcount--;
    }

    if(boost)
    {
        k=0.75;
        bocnt++;
        if(bocnt%200 == 0)
        {
            boost=0;
            k=0.3;
        }

    }
    if(s)
        radius+=1.0;
    if(d)
        camangle+=1;
    if(a)
        camangle-=1     ;
    if(w)
        radius-=1.0;

    if(bot_f)
        camview=0;
    if(tower)
        camview=3;

    if(front)
        camview=2;

    if(top)
        camview=1;

    if(z)
    {
        cannon.rotation+=0.8;

        }

    if(m)
    {
        cannon.rotation-=0.8;

     }

    if (space && boat.position.y==0)
    {
        boat.speed=0.2;
        cannon.speed=0.2;
        system(" canberra-gtk-play -f  ../resources/jump.wav --volume=\"1\"   &");
    }

    if (left) {
        boat.rotation+=0.75;
        cannon.rotation+=0.75;

    }

    if (right) {
        boat.rotation-=0.75;
        cannon.rotation-=0.75;
    }

    if (up) {

        cannon.rotation=boat.rotation;
        boat.position.x-=k*cos(boat.rotation*M_PI/180) ;
        boat.position.z+=k*sin(boat.rotation*M_PI/180) ;
        cannon.position.x-=k*cos(cannon.rotation*M_PI/180) ;
        cannon.position.z+=k*sin(cannon.rotation*M_PI/180) ;

    }

    if (down) {
        cannon.rotation=boat.rotation;

        boat.position.x+=k*cos(boat.rotation*M_PI/180) ;
        boat.position.z-=k*sin(boat.rotation*M_PI/180) ;

        cannon.position.x+=k*cos(cannon.rotation*M_PI/180) ;
        cannon.position.z-=k*sin(cannon.rotation*M_PI/180) ;
    }

    for(int i=0;i<10;i++)
    {
        if(detect_collision(boat.bounding_box(),rock[i].bounding_box()))
        {/*
            boat.rotation+=1;
            cannon.rotation+=1.;
            boat.position.z+=3;
            cannon.position.z+=3;*/
            boat.position.x+=2;
            cannon.position.x+=2;
            system(" canberra-gtk-play -f  ../resources/rock.wav --volume=\"1\"   &");
            health-=5;

        }
    }
    for(int i=0;i<10;i++)
    {
        if(detect_collision_gift(boat.bounding_box(),gift[i].bounding_box()))
        {
            system(" canberra-gtk-play -f  ../resources/coin.wav --volume=\"1\"   &");
                gift[i].position.y=-10;
                barrel[i].position.y=-0.0999;
                if(health<=98)
                    health +=2;

        }

        if(detect_collision_boost(boat.bounding_box(),booster[i].bounding_box()))
        {
            system(" canberra-gtk-play -f  ../resources/boost.wav --volume=\"1\"   &");
                booster[i].position.y=-10;
                boostcount++;
        }
    }

    for(int i=0;i<1000;i++)
    {
        for(int j=0;j<5;j++)
         if(detect_collision_bull(bullet[i].bounding_box(),monster[j].bounding_box()) && buf[i])
         {
             system(" canberra-gtk-play -f  ../resources/enemy.wav --volume=\"1\"   &");
                        cof[cocnt]=1;
                        coin[cocnt++].set_position(monster[j].position.x,monster[j].position.y,monster[j].position.z);
                        monster[j].position.x-=50;
                        monster[j].position.z+=60;
                        bullet[i].position.y=-10;
                        points+=20;
                        moncnt++;
                        if(moncnt==3)
                        {
                            bosf=1;
                            moncnt=0;
                            boss.position.x=boat.position.x-15;
                            boss.position.z=boat.position.z;
                        }
         }

        else if(bosf)
        {   if(bosso.processTick())
                system(" canberra-gtk-play -f  ../resources/boss.wav --volume=\"1\"   &");
            if(detect_collision_bos(boss.bounding_box(),bullet[i].bounding_box()))
            {   if(boscnt!=5)
                    system(" canberra-gtk-play -f  ../resources/enemy.wav --volume=\"1\"   &");
                boscnt++;
                if(boscnt==5)    
                {   system(" canberra-gtk-play -f  ../resources/bos.wav --volume=\"1\"   &");
                    bosf=0;
                    points+=50;
                    Bosses++;
                    bullet[i].position.y=-10;
            }
            bullet[i].position.y-=10;}
        }
    }
    for(int i=0;i<50;i++)
    {
        if(cof[i] && detect_collision_coin(coin[i].bounding_box(),boat.bounding_box()))
        {
            system(" canberra-gtk-play -f  ../resources/gift.wav --volume=\"1\"   &");
                    cof[i]=0;
                    coins++;
                    if(coins>=5)
                    {
                        coins=0;
                        boostcount++;
                    }
        }
    }


    for(int i=0;i<5;i++)
    {
        if(detect_collision_mon(monster[i].bounding_box(),boat.bounding_box()))
        {
            system(" canberra-gtk-play -f  ../resources/death.wav --volume=\"1\"   &");

                boat.set_position(0,0,0);
                cannon.set_position(0,0,0);
                boat.speed=0.5;
                cannon.speed=0.5;
                health-=10;


        }
    }

    if(detect_collision_boss(boss.bounding_box(),boat.bounding_box()) && bosf)
    {
        boat.set_position(0,0,0);
        cannon.set_position(0,0,0);
        boat.speed=0.5;
        cannon.speed=0.5;
        health-=30;
    }


    if(cnt2%40==0)
    {
        for(int i=0;i<5;i++)
        {
            int a = rand()%5;
            int b=rand()%5;
            if(rand()%2)
            {
                 monster[i].position.x+=a;
                 monster[i].position.x-=b;
            }
            else
            {
                     monster[i].position.x-=a;
                     monster[i].position.x+=b;
            }
        }
    }

}

void tick_elements() {
    ball1.tick();
    boat.tick();
    cannon.tick();
    for(int i=0;i<1000;i++)
        if(buf[i])
            bullet[i].tick();
    for(int i=0;i<10;i++)
    {
        gift[i].tick();
        booster[i].speed = 10;
        booster[i].tick();
    }
    for(int i=0;i<5;i++)
        monster[i].tick();
    if(bosf)
    {
        boss.tick();

    }
    for(int i=0;i<50;i++)
       if(cof[i])
        coin[i].tick();



    ////////////////////////////////////////////

    if(!wind && rand()%1000==0)
    {
        system(" canberra-gtk-play -f  ../resources/wind.wav --volume=\"1\"   &");
        wind = 1;
    }

    if(wind){

        count_wind++;
        if(count_wind%100==0)
            wind=0;

        if(rand()%2)
        {
                 boat.rotation+=1;
                cannon.rotation=boat.rotation;
                boat.position.x-=.2*cos(boat.rotation*M_PI/180) ;
                boat.position.z+=.2*sin(boat.rotation*M_PI/180) ;
                cannon.position.x-=.2*cos(cannon.rotation*M_PI/180) ;
                cannon.position.z+=.2*sin(cannon.rotation*M_PI/180) ;
        }
//        else
//        {
//            boat.rotation-=1;
//            cannon.rotation=boat.rotation;

//            boat.position.x+=.3*cos(boat.rotation*M_PI/180) ;
//            boat.position.z-=.3*sin(boat.rotation*M_PI/180) ;

//            cannon.position.x+=.3*cos(cannon.rotation*M_PI/180) ;
//            cannon.position.z-=.3*sin(cannon.rotation*M_PI/180) ;
//        }
    }
    //////////////////////////////////////////////////////////

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, COLOR_WATER);
    boat =Boat(0,0,COLOR_RED);
    for(int i=0;i<20;i++)
    {
        int a= rand()%90;
        int b=rand()%100 ;
        if(rand()%2)
          rock[i] = Rock(-a,0,-b,COLOR_BLACK);
        else
             rock[i] = Rock(-a,0,b,COLOR_BLACK);

    }
    for(int i=0;i<10;i++)
    {
        int a = rand()%70;
        int b=rand()%80;
        if(rand()%2)
        {
            barrel[i] = Barrel(-a,0,-b,COLOR_BOAT);
            gift[i] = Gift(-a,-0.65,-b,COLOR_RED);
            booster[i] = Gift(-a+25,-0.99,-b-25,COLOR_BOSS);
        }
        else
        {
            barrel[i] = Barrel(-a,0,b,COLOR_BOAT);
            gift[i] = Gift(-a,-0.65,b,COLOR_RED);
            booster[i] = Gift(-a+25,-0.99,b+25,COLOR_BOSS);
        }
    }



     cannon= Cannon(0,-0.2,0,COLOR_CANNON);
       for(int i=0;i<1000;i++)
            bullet[i] = Bullet(0,-0.2,0,COLOR_BLACK);
    for(int i=0;i<5;i++)
    {
        int a = rand()%90;
        int b = rand()%80;
       if(rand()%2)
         monster[i] = Monster(-a,-0.7,-b,COLOR_BLACK);
       else
           monster[i] = Monster(-a,-0.7,b,COLOR_BLACK);

    }
        boss = Boss(boat.position.x-7,-0.7,boat.position.z,COLOR_RED);
        for(int i=0;i<50;i++)
            coin[i] = Coin(-5,-0.5,-5,COLOR_COIN);

        // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (0,255,255,0); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
//        if(bosso.processTick() || flag==1)
//         {
//            flag=0;
//            system(" canberra-gtk-play -f  ../resources/SEASHORE.wav --volume=\"1\"   &");
//           }
        if (t60.processTick()) {
            //////////////////////////

                        string Result;
                        stringstream convert;
                        //cout << "nonedit score:" << score << endl;
                        convert << points;
                        Result = convert.str();

                        const char *one = "Score: ";
                        const char *two = Result.c_str();
                        const char *three = "   Bosses-Killed: ";
                        string Result1;
                        stringstream convert1;
                        convert1 << Bosses;
                        Result1 = convert1.str();
                        const char *four = Result1.c_str();
                        const char *five = "  Health: ";
                        string Result2;
                        stringstream convert2;
                        convert2<<health;
                        Result2 = convert2.str();
                        const char * six = Result2.c_str();
                        string Result3;
                        stringstream convert3;
                        convert3<<boostcount;
                        Result3 = convert3.str();
                        const char * seven = "  Boosts Remaining: ";
                         const char * eight = Result3.c_str();

                        string total( string(one) + two + string(three) + four +string(five) + six + string(seven) + eight );
                        glfwSetWindowTitle(window, total.c_str());


             ////////////////////////////////









            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        if(health<=0)
            break;

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (sqrt(pow(a.x-b.x,2)+pow(a.z-b.z,2))<=5.2 && a.y==b.y);

}

bool detect_collision_gift(bounding_box_t a, bounding_box_t b) {
    return (sqrt(pow(a.x-b.x,2)+pow(a.z-b.z,2))<=4 && b.y>=-1);
}

bool detect_collision_bull(bounding_box_t a, bounding_box_t b) {
      return (sqrt(pow(a.x-b.x,2)+pow(a.z-b.z,2))<=0.5 && a.y>-1);

}

bool detect_collision_mon(bounding_box_t a, bounding_box_t b) {
      return (sqrt(pow(a.x-b.x,2)+pow(a.z-b.z,2))<=5.2);

}

bool detect_collision_bos(bounding_box_t a, bounding_box_t b) {
      return (b.x>a.x && b.x<a.x+4 && b.y>a.y-0.5 && b.y<a.y+0.9);

}

bool detect_collision_boss(bounding_box_t a, bounding_box_t b) {
      return (abs(a.x-b.x)<=6 && b.y>-1 && b.y<1);

}

bool detect_collision_boost(bounding_box_t a, bounding_box_t b) {
      return (b.y>-1 && abs(b.x-a.x)<=3.75 && abs(b.z-a.z)<=2 && a.y==0);

}

bool detect_collision_coin(bounding_box_t a, bounding_box_t b) {
      return (abs(a.x-b.x)<4 && abs(a.z-b.z)<3);

}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
   Matrices.projection = glm::infinitePerspective(glm::radians(90.0f), 4.0f,0.1f);
}
