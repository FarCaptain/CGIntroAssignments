#include<GL/glut.h>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

int theta;
int moveX = 0;
int des = 0;
const double fab = 0.001;
void initBlending()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

double dx,dz;//cube pos
double sx=0,sz=5;//ball pos
void initLighting() {
    GLfloat ambient[] = { 0.5, 0.3, 0.3, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat position[] = {dx,-5+0.15,dz, 1.0 };
    GLfloat emission[] = {1.0,1.0,0.0,1.0};
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };
    glShadeModel(GL_SMOOTH);
    //设置环境光
    //glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    //设置漫射光
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    glLightfv(GL_LIGHT0, GL_EMISSION, emission);
    //设置光源位置
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    //启动光照
    glEnable(GL_LIGHTING);
    //启用光源
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
}

//画球
void drawBall(double R, double x, double y,double z) {
	glPushMatrix();
	glTranslated(x,y,z);
    glutSolidSphere(R,20,20);
	glPopMatrix();
}


//画长方体
void drawCube(double l, double w, double h, double x, double y, double z) {
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(l, w, h);
	glutSolidCube(1);
	glPopMatrix();
}

double ch[2];
double gap = 0.1;
bool delay,mov=false;
void display(void) {
	//清除缓冲区颜色
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//圆点放坐标中心
	glLoadIdentity();
	//从哪个地方看
	gluLookAt(-2.0, -1.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotated(theta, 0, 1, 0);


    GLfloat map_mat_ambient[]  = {0.5f, 0.5f, 0.0f, 1.0f};
    GLfloat map_mat_diffuse[]  = {0.5f, 0.5f, 0.0f, 1.0f};
    GLfloat map_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat map_mat_emission[] = {1.0f, 1.0f, 0.0f, 1.0f};
    GLfloat map_mat_shininess  = 0.0f;
    glMaterialfv(GL_FRONT,GL_AMBIENT,map_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   map_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  map_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  map_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, map_mat_shininess);
	glColor4f(1.0, 1.0, 1.0,0.6);
	drawCube(20,0.3,20,0,-5,0);

	//glColor4f(0.5, 0.0, 0.6,0.1);
    dx = min(dx,9.0);
    dx = max(dx,-9.0);
    dz = min(dz,9.0);
    dz = max(dz,-9.0);

    GLfloat cub_mat_ambient[]  = {0.0f, 0.5f, 0.5f, 1.0f};
    GLfloat cub_mat_diffuse[]  = {0.0f, 0.5f, 0.5f, 1.0f};
    GLfloat cub_mat_specular[] = {0.0f, 0.0f, 0.1f, 1.0f};
    GLfloat cub_mat_emission[] = {0.0f, 0.7f, 0.7f, 1.0f};
    GLfloat cub_mat_shininess  = 0.5f;
    glMaterialfv(GL_FRONT,GL_AMBIENT,cub_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   cub_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  cub_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  cub_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, cub_mat_shininess);

    drawCube(2,2,2,dx,-5+1.2,dz);
    if(sx>=9.0||sx<=-9.0)ch[0] = -ch[0];
    if(sz>=9.0||sz<=-9.0)ch[1] = -ch[1];
//    if(mov&&!delay&&abs(dx-sx)-2<=fab&&abs(dz-sz)-2<=fab){
//        ch[0] = 0;
//        ch[1] = 0;
//    }
    sx+=ch[0],sz+=ch[1];

    GLfloat bal_mat_ambient[]  = {0.5f, 0.0f, 0.0f, 1.0f};
    GLfloat bal_mat_diffuse[]  = {0.5f, 0.0f, 0.0f, 1.0f};
    GLfloat bal_mat_specular[] = {0.0f, 0.0f, 0.1f, 1.0f};
    GLfloat bal_mat_emission[] = {0.5f, 0.0f, 0.1f, 1.0f};
    GLfloat bal_mat_shininess  = 0.1f;
    glMaterialfv(GL_FRONT,GL_AMBIENT,bal_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   bal_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  bal_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  bal_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, bal_mat_shininess);
	drawBall(1,sx,-5+1.2,sz);
	glPopMatrix();
    glutSwapBuffers();
}
//鼠标点击事件
bool ifdown;
void mouseClick(int btn, int state, int x, int y) {
    cout << x<<" "<<y<<endl;
    ifdown=false;
    if(btn==GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN)ifdown = true;
        moveX = x;
    }
    if(btn==GLUT_RIGHT_BUTTON){

    }
}

// 鼠标移动事件
void mouseMove(int x, int y) {
    if(ifdown){
        int dt = x - moveX;
        theta += dt;
        glutPostRedisplay();
        moveX = x;
    }
}

//键盘事件
void keyPressed(unsigned char key, int x, int y) {
    delay = false;
    gap = 0.1;
    if(abs(dx-sx)<2&&abs(dz-sz)<2)delay=true,gap=0,mov=true;
    switch (key) {
    case 'a':
        if(delay)ch[0]=-0.05;
        dx-=gap;
        break;
    case 'd':
        if(delay)ch[0]=0.05;
        dx+=gap;
        break;
    case 'w':
        if(delay)ch[1]=-0.05;
        dz-=gap;
        break;
    case 's':
        if(delay)ch[1]=0.05;
        dz+=gap;
		break;
	}
	delay = false;
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 50);
	glMatrixMode(GL_MODELVIEW);
}

void idleFunc()
{
    Sleep(10);
    glutPostRedisplay(); //重新调用绘制函数

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);//?
	glutCreateWindow(argv[0]);
	glutReshapeFunc(reshape);
	//initBlending();
	initLighting();
	glutDisplayFunc(display);
	glutIdleFunc(idleFunc);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	return 0;
}
