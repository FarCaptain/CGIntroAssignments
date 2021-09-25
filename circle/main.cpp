#include<windows.h>
#include<iostream>
#include<stdlib.h>
#include<gl/glut.h>
#include<math.h>
using namespace std;



void DDACircle(int x0, int y0, int r)
{
	float x, y, dx, dy;
	x = x0 + r;
	y = y0;

	glVertex2f(x, y);
    for(float i = 0; i <= 6.2831852; i += 0.1) {
        dx = -r * sin(i);
        dy = r * cos(i);
        x = x + dx;
        y = y + dy;
        glVertex2f(x, y);
    }
}

void drawpixel(int x, int y)
{
    glVertex2i(x, y);
    glVertex2i(-x, y);
    glVertex2i(x, -y);
    glVertex2i(-x, -y);
    glVertex2i(y, x);
    glVertex2i(-y, x);
    glVertex2i(y, -x);
    glVertex2i(-y, -x);
}

void draw(int xc ,int yc ,int x ,int y)
{
    drawpixel(xc+x,yc+y);
}

void Bresenham_Circle(int xc , int yc , int r)
{
    int x, y, d;
    x = 0;
    y = r;
    d = 3 - 2 * r;
    draw(xc, yc, x, y);
    while(x < y){
       if(d < 0){
            d = d + 4 * x + 6;
       }
       else{
            d = d + 4 * ( x - y ) + 10;
            y--;
       }
       x++;
       draw(xc, yc, x , y);
   }
}

void AngleDDA(int xc , int yc , int r)
{
    int x, y, d;
    x = 0;
    y = r;
    draw(xc , yc, x , y);
    while(x < y){

        draw(xc, yc, x, y);
    }
}

void Render()
{
    glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
    //a diamond
    Bresenham_Circle(0,0,600);
    Bresenham_Circle(0,0,500);

    Bresenham_Circle(200,200,110);
    Bresenham_Circle(200,-200,110);
    Bresenham_Circle(-200,200,110);
    Bresenham_Circle(-200,-200,110);

    glEnd();
	glFlush();
}

//¸Ãº¯ÊýÓÃÓÚÉèÖÃäÖÈ¾×´Ì¬
void SetupRC()
{
	glClearColor(0.3f, 0.4f, 0.2f, 1.0f);//Ä¨²èflavor
}

void ChangeSize(GLsizei W, GLsizei H)
{
	glViewport(0, 0, W, H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1200, 1200, -1200, 1200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("A Tiny Button..");
	glutDisplayFunc(Render);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
	return 0;
}
