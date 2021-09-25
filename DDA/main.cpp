#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#define Pi acos(-1)
#include<bits/stdc++.h>
using namespace std;


void DDALine(int x0,int y0, int x1, int y1)
{
    int dx = x1-x0;
    int dy = y1-y0;
    double k;

    if(abs(dx)<=abs(dy)){
        if(dy==0)k=1;//dx==dy==0
        else k = dx*1.0/dy;//dx==0
        double x = x0;
        for(int y=y0;y<=y1;y++){
            //drawPixel(int(x+0.5),y);
            glVertex2i(int(x+0.5),y);
            x += k;
        }
    }
    else{//if(dy==0)k==0
        double k = dy*1.0/dx;
        double y = y0;
        for(int x=x0;x<=x1;x++){
            //cout << x<<" "<<int(y+0.5)<<endl;
            glVertex2i(x,int(y+0.5));
            y += k;
        }
    }
}
void RenderScence()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_POINTS);

    DDALine(0,0,1000,500);
    DDALine(-1000,-1000,0,0);
    DDALine(0,0,500,1000);

    glEnd();
    glFlush();
}

void SetupRC()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void ChangeSize(GLsizei W, GLsizei H)
{
    glViewport(0,0,W,H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0,1000.0,-1000.0,1000.0,1.0,-1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main()
{
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("CheckThisOut!");

    glutDisplayFunc(RenderScence);
    glutReshapeFunc(ChangeSize);
    SetupRC();
    glutMainLoop();
    return 0;
}
