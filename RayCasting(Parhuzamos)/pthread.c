#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "texture/All_Textures.ppm"
#include "texture/sky.ppm"
#include <pthread.h>

#define PI 3.1415926535

#define THREAD_COUNT 4
#define RAY_COUNT 120


typedef struct {
    float rx, ry;
    float disH;
    float shade;
    int hmt;
    float ra;
} RayResult;

typedef struct {
    int startRay;
    int endRay;
    float ra;
    RayResult* results;
    
} RaycastThreadData;



typedef struct 
{
    int w,a,s,d;
}ButtonKeys; 

ButtonKeys Keys;




float degtorad(float a){
    return a*PI/180.0;
}

float FixAng(float a){

    if (a>359)
    {
        a-=360;
    }
    if (a<0)
    {
        a+=360;
    }
    
    

    return a;
}

float player_x , player_y , player_DeltaX, player_DeltaY, angle; // GLOBÁLIS VÁLTOZÓ


void drawplayer(){

    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(player_x, player_y);
    glEnd();


    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2i(player_x,player_y);
    glVertex2i(player_x+player_DeltaX*20, player_y+player_DeltaY*20);
    glEnd();




}

#define mapX  8 
#define mapY  8 
#define mapS 64

int mapW[]=       
{
 1,1,1,1,1,1,1,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};

int mapF[]=       
{
 1,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,
};

int mapC[]=        
{
 3,3,3,3,3,3,3,3,
 3,3,3,3,3,3,3,3,
 3,3,0,0,0,0,3,3,
 3,3,0,0,0,0,3,3,
 3,3,0,0,0,0,3,3,
 3,3,3,3,3,3,3,3,
 3,3,3,3,3,3,3,3,
 3,3,3,3,3,3,3,3,	
};


void drawMap2D(){

int x,y,x0,y0;

for (y = 0; y < mapY; y++)
{
    for (x = 0; x < mapX; x++)
    {
        
        if (mapW[y*mapX+x] > 0)
        {
            glColor3f(1,1,1);
        }else
        {
            glColor3f(0,0,0);
        }
        
        x0 = x*mapS;
        y0 = y*mapS;
        glBegin(GL_QUADS);
        glVertex2i( 0   +x0+1, 0   +y0+1); 
        glVertex2i( 0   +x0+1, mapS+y0-1); 
        glVertex2i( mapS+x0-1, mapS+y0-1);  
        glVertex2i( mapS+x0-1, 0   +y0+1);
        glEnd();

    }
    
}
}


float dist (float ax,float ay,float bx,float by, float ang){

    return(cos(degtorad(ang))*(bx-ax)-sin(degtorad(ang))*(by-ay));

}


void* raycastThread(void* arg) {
    RaycastThreadData* data = (RaycastThreadData*)arg;

    int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
                                                                     
    ra = data->ra;
    
    
    for (int r = data->startRay; r < data->endRay; r++) {
        
        //printf("%f \n" , ra);
     
 
        int vmt=0,hmt=0;                                                              

        dof=0; side=0; disV=100000;
        float Tan=tan(degtorad(ra));
        if(cos(degtorad(ra))> 0.001)
        { 
            rx=(((int)player_x>>6)<<6)+64;
            ry=(player_x-rx)*Tan+player_y; xo= 64;
            yo=-xo*Tan;
        }
        else if(cos(degtorad(ra))<-0.001)
        {
            rx=(((int)player_x>>6)<<6) -0.0001;
            ry=(player_x-rx)*Tan+player_y; xo=-64;
            yo=-xo*Tan;
        }
        else
        { 
            rx=player_x; 
            ry=player_y; 
            dof=8;
        }                                                 

        while(dof<8) 
        { 
            mx=(int)(rx)>>6; 
            my=(int)(ry)>>6;
            mp=my*mapX+mx;   

            if(mp>0 && mp<mapX*mapY && mapW[mp]>0)
            { 
                vmt=mapW[mp]-1;
                dof=8;
                disV=cos(degtorad(ra))*(rx-player_x)-sin(degtorad(ra))*(ry-player_y);
            }       
            else
            {
                rx+=xo; ry+=yo; dof+=1;
            }                                               
        } 
        vx=rx; vy=ry;

 
        dof=0;
        disH=100000;
        Tan=1.0/Tan; 

        if(sin(degtorad(ra))> 0.001)
        {
            ry=(((int)player_y>>6)<<6) -0.0001;
            rx=(player_y-ry)*Tan+player_x;
            yo=-64;
            xo=-yo*Tan;
        }
        else if(sin(degtorad(ra))<-0.001)
        {
            ry=(((int)player_y>>6)<<6)+64;
            rx=(player_y-ry)*Tan+player_x;
            yo= 64;
            xo=-yo*Tan;
        }
        else
        {
            rx=player_x;
            ry=player_y;
            dof=8;
        }                                                   
 
        while(dof<8) 
        { 
            mx=(int)(rx)>>6;
            my=(int)(ry)>>6;
            mp=my*mapX+mx;                          

            if(mp>0 && mp<mapX*mapY && mapW[mp]>0)
            { 
                hmt=mapW[mp]-1;
                dof=8;
                disH=cos(degtorad(ra))*(rx-player_x)-sin(degtorad(ra))*(ry-player_y);
            }        
            else
            {
                rx+=xo;
                ry+=yo;
                dof+=1;
            }
     
            float shade=1;
            if(disV<disH)
            {
                hmt=vmt;
                shade=0.5;
                rx=vx;
                ry=vy;
                disH=disV;
            }
    
            

            RayResult* res = &data->results[r];
            res->rx = rx;
            res->ry = ry;
            res->disH = disH;
            res->shade = shade;
            res->hmt = hmt;
            res->ra = ra;
          


            
        }
        

        ra=FixAng(ra-0.5);
    }
    

    return NULL;
}



void drawRays2D()
{


    RayResult* ray = malloc(sizeof(RayResult) * RAY_COUNT);
    RaycastThreadData* threadData = malloc(sizeof(RaycastThreadData) * THREAD_COUNT);
    pthread_t* threads = malloc(sizeof(pthread_t) * THREAD_COUNT);


    /*pthread_t threads[THREAD_COUNT];
    RaycastThreadData threadData[THREAD_COUNT];
    RayResult ray[RAY_COUNT];
    */

    int raysPerThread = RAY_COUNT / THREAD_COUNT;
    
    
    
    
    

    for (int i = 0; i < THREAD_COUNT; i++) {
        threadData[i].startRay = i * raysPerThread;
        threadData[i].endRay = (i + 1) * raysPerThread;
        threadData[i].results = ray;
        threadData[i].ra=FixAng(angle+30 -(30*i*0.5)); //-(30*i*0.5) szögeltolástól behal a program
        
        

        pthread_create(&threads[i], NULL, raycastThread, &threadData[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    for(int r = 0; r < RAY_COUNT; r++) {
        RayResult res = ray[r];
	 
  
        if(res.shade == 1)
        {
            glColor3f(0,0.8,0);
        }else{
            glColor3f(0,0.6,0);
        }
    
  

  
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(player_x,player_y);
        glVertex2i(res.rx,res.ry);
        glEnd();
    
        int ca=FixAng(angle-res.ra);
        res.disH = res.disH*cos(degtorad(ca));                            
        int lineH = (mapS*320)/(res.disH); 
        float ty_step=32.0/(float)lineH; 
        float ty_off=0; 
        if(lineH>320)
        {
            ty_off=(lineH-320)/2.0;
            lineH=320;
        }                            
            int lineOff = 160 - (lineH>>1);                                              

        //falll

        int y;
        float ty=ty_off*ty_step;
        float tx;
        if(res.shade==1)
        { 
            tx=(int)(res.rx/2.0)%32;
            if(res.ra>180)
            { 
                tx=31-tx;
            }
        }  
        else
        { 
            tx=(int)(res.ry/2.0)%32;
            if(res.ra>90 && res.ra<270)
            { 
                tx=31-tx;
            }
        }
        for(y=0;y<lineH;y++)
        {

            int pixel=((int)ty*32+(int)tx)*3+(res.hmt*32*32*3);
            int red   =All_Textures[pixel+0]*res.shade; 
            int green =All_Textures[pixel+1]*res.shade;
            int blue  =All_Textures[pixel+2]*res.shade;
            glPointSize(8);
            glColor3ub(red,green,blue);
            glBegin(GL_POINTS);
            glVertex2i(r*4+530,y+lineOff);
            glEnd();
            ty+=ty_step;
        }
 
        //padlo
        for(y=lineOff+lineH;y<320;y++)
        {
            float dy=y-(320/2.0), deg=degtorad(res.ra), raFix=cos(degtorad(FixAng(angle-res.ra)));
            tx=player_x/2 + cos(deg)*158*32/dy/raFix;
            ty=player_y/2 - sin(deg)*158*32/dy/raFix;
            int mp=mapF[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;


            int pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
            int red   =All_Textures[pixel+0]*0.7; 
            int green =All_Textures[pixel+1]*0.7;
            int blue  =All_Textures[pixel+2]*0.7;
            glPointSize(8);
            glColor3ub(red,green,blue);
            glBegin(GL_POINTS);
            glVertex2i(r*4+530,y);
            glEnd();
            ty+=ty_step;

            //plafon
            mp=mapC[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
  
            pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
            red   =All_Textures[pixel+0]; 
            green =All_Textures[pixel+1];
            blue  =All_Textures[pixel+2];
            if (mp>0)
            {
                glPointSize(8);
                glColor3ub(red,green,blue);
                glBegin(GL_POINTS);
                glVertex2i(r*4+530,320-y);
                glEnd();
            }
    
   
            ty+=ty_step;
        }

    }

    free(ray);
    free(threadData);
    free(threads);

    
}


void drawSky() {

int x, y;
for ( y = 0; y < 40; y++)
{
   for ( x = 0; x < 120; x++)
   {
        int x0 = (int)angle*2-x;
        if (x0<0)
        {
            x0+=120;
        }
        x0=x0%120;
    
        int pixel=(y*120+x0)*3;
        int red   =sky[pixel+0]; 
        int green =sky[pixel+1];
        int blue  =sky[pixel+2];
        glPointSize(4);
        glColor3ub(red,green,blue);
        glBegin(GL_POINTS);
        glVertex2i(x*4+530,y*4);
        glEnd();
   }
   
}



}


    

float frame1 = 0 , frame2=0 , fps= 0; //GLOBÁLIS VÁLTOZÓ
float frameTime = 1000.0 / 60.0; //GLOBÁLIS VÁLTOZÓ


void display()
{
    frame2=glutGet(GLUT_ELAPSED_TIME);
    fps=(frame2-frame1);
    frame1=glutGet(GLUT_ELAPSED_TIME);
    printf("FPS: %f\n", 1000.0 / fps);

    


    int x0=0; 
    if(player_DeltaX<0)
    { 
        x0=-20;
    }
    else{
        x0=20;
    }                                  
    int y0=0;
    if(player_DeltaY<0)
    {
        y0=-20;
    } else
    {
        y0=20;
    }                                   
    int ipx=player_x/64.0;
    int ipx_add_x0=(player_x+x0)/64.0;
    int ipx_sub_xo=(player_x-x0)/64.0; 
               
    int ipy=player_y/64.0;
    int ipy_add_y0=(player_y+y0)/64.0;
    int ipy_sub_yo=(player_y-y0)/64.0;

    if (Keys.w == 1)
    {
        
        if(mapW[ipy*mapX        + ipx_add_x0]==0)
        {
            player_x+=player_DeltaX*0.2*fps;
        }
        if(mapW[ipy_add_y0*mapX + ipx       ]==0)
        {
            player_y+=player_DeltaY*0.2*fps;
        }


    }
    if (Keys.s == 1)
    {
        if(mapW[ipy*mapX        + ipx_sub_xo]==0)
        { 
            player_x-=player_DeltaX*0.2*fps;
        }
        if(mapW[ipy_sub_yo*mapX + ipx       ]==0)
        { 
            player_y-=player_DeltaY*0.2*fps;
        }
    }
    if (Keys.a == 1)
    {
        angle+=0.2*fps;
        angle=FixAng(angle);
        player_DeltaX=cos(degtorad(angle));
        player_DeltaY=-sin(degtorad(angle));
        
    }
    if (Keys.d == 1)
    {
        angle-=0.2*fps;
        angle=FixAng(angle);
        player_DeltaX=cos(degtorad(angle));
        player_DeltaY=-sin(degtorad(angle));
    }
    glutPostRedisplay();





glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
drawMap2D();
drawplayer();
drawSky();
drawRays2D();
glutSwapBuffers();
}

void ButtonDown(unsigned char key, int x, int y){

    if (key =='a')
    {
        Keys.a=1;
    }
    if (key =='d')
    {
        Keys.d=1;
    }
    if (key =='w')
    {
        Keys.w=1;
    }
    if (key =='s')
    {
        Keys.s=1;
    }
    if(key=='e')            
    { 
        int x0=0; if(player_DeltaX<0)
        {
            x0=-25;
        }
        else
        {
            x0=25;
        }
        int y0=0;
        if(player_DeltaY<0)
        {
            y0=-25;
        } 
        else
        {
            y0=25;
        } 
        int ipx=player_x/64.0, ipx_add_xo=(player_x+x0)/64.0;
        int ipy=player_y/64.0, ipy_add_yo=(player_y+y0)/64.0;
        if(mapW[ipy_add_yo*mapX+ipx_add_xo]==3)
        { 
            mapW[ipy_add_yo*mapX+ipx_add_xo]=0;
        }
    }
    glutPostRedisplay();

}


void ButtonUp(unsigned char key, int x, int y){

    if (key =='a')
    {
        Keys.a =0;
    }
    if (key =='d')
    {
        Keys.d=0;
    }
    if (key =='w')
    {
        Keys.w=0;
    }
    if (key =='s')
    {
        Keys.s=0;
    }
    glutPostRedisplay();

}



void resize(int w, int h){

    glutReshapeWindow(1024, 512);

}






void init()
{
glClearColor(0.3,0.3,0.3,0.3);
gluOrtho2D(0,1024,512,0);
player_x = 300;
player_y = 300;
angle = 0;
player_DeltaX = cos(degtorad(angle));
player_DeltaY =-sin(degtorad(angle));
}




int main(int argc, char* argv[])
{

    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024 , 512);
    glutInitWindowPosition(200,200);
    glutCreateWindow("test1");

    init();


    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);
    glutMainLoop();



}
