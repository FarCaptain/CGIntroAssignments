#include <bits/stdc++.h>
#include <windows.h>
#include <GL/glut.h>
using namespace std;

float window_width = 800.0;		//window size
float window_height = 600.0;
int pointsCounter = 0;		// Counter for the points

// Point class for points with x and y
class Point {
	public: float x, y;
	void setxy(float x1, float y1)
	{ x = x1; y = y1; }
};

Point points[21]; //allow a max number of 20 points

void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,window_width,0.0,window_height);
}

//Draw the point out when the user clicks on the screen
void drawPoint(int x, int y)
{
	glPointSize(10.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}


void drawLine(Point point1, Point point2,int cl)
{
	glLineWidth(1.0);
	if(cl==-1)glColor3f(1.0, 1.0, 1.0);
	else if(cl ==0)glColor3f(1.0, 0.0, 0.0);
	else if(cl ==1)glColor3f(0.0, 1.0, 0.0);
	else if(cl ==2)glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex2f(point1.x, point1.y);
		glVertex2f(point2.x, point2.y);
	glEnd();
	glFlush();
}


long long pr[21];

void preProceed()
{
    pr[0] = 1;
    for(int i=1;i<21;++i){
        pr[i] = pr[i-1]*i;
    }
}

int C(int n, int m)
{
    int res = pr[n]/pr[m]/pr[n-m];
    return res;
}

double qpow(double a, int x)
{
    if(x==0)return 1;
    double ans = 1;
    while(x){
        if(x&1) ans *= a;
        a*=a;
        x>>=1;
    }
    return ans;
}

double Bern(int i, int n, double t)
{
    return 1.0*C(n,i)*qpow(t,i)*qpow(1-t,n-i);
}

//Draw the Beaier Curve
Point drawBezier(int n,double t)
{
	Point p;
	p.x = 0; p.y = 0;
	for(int i=0;i<n;i++){
        double b = Bern(i,n-1,t);
        p.x += points[i].x*Bern(i,n-1,t);
        p.y += points[i].y*Bern(i,n-1,t);
	}
	return p;
}
int color;
//myGlutMouse Function
void myGlutMouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		points[pointsCounter].setxy((float)x,(float)(window_height - y));	//y coordinate is backward
		pointsCounter++;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
        for ( int i = 0; i < pointsCounter; i++)
        {
				drawPoint(points[i].x, points[i].y);	//draw the points

        }
        for ( int i = 0; i < pointsCounter -1; i++)
        {
            drawLine(points[i], points[i+1],-1);		//draw the lines
        }

        if(pointsCounter<3)return;//cant draw curves

        Point oldPoint = points[0];

        for(double t = 0.0;t <= 1; t += 0.005)
        {
            Point nextPoint = drawBezier(pointsCounter, t);
            drawLine(oldPoint, nextPoint,color);
            oldPoint = nextPoint;
        }
        if(pointsCounter>20)pointsCounter = 0;
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        //switch color
        color = (color+1)%3;
    }
}




void myGlutDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);				// Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);		//Set display mode.
	glutInitWindowPosition( 50, 30 );				//Set top-left display-window position.
	glutInitWindowSize(window_width, window_height);	//Set display-window width and height;
	glutCreateWindow("Check This Out!");				//Create display window with the a given caption for the title bar.
	glutMouseFunc(myGlutMouse);
	glutDisplayFunc(myGlutDisplay);

    color = 0;
    preProceed();
	init();
	glutMainLoop();
	return 0;
}
