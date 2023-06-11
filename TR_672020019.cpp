#include <windows.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#define PI 3.1415927
#include <iostream>
#include "imageloader.h"
using namespace std;
#define FPS 120
#define TO_RADIANS 3.14/180.0

//Tifano Eng Ogotan			672020019
//Natanael Jeffrey Susanto		672020027
//Bernadus Enggar Prasetya	672020032

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

GLuint _textureId;
GLuint _textureId2;
GLuint _textureId3;

 GLuint loadTexture(Image* image) {
 GLuint textureId;
 glGenTextures(1, &textureId);
 glBindTexture(GL_TEXTURE_2D, textureId);
 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
 return textureId;
}

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;
float xrot = 0.0;
float yrot = 0.0;
float xdiff = 0.0;
float ydiff = 0.0;
void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

void ngon(int n, float cx, float cy, int z, float radius, float rotAngle)
{
	double angle, angleInc;
	int k;
	if (n < 3) return;
	angle = rotAngle * 3.14159265 / 180;
	angleInc = 2 * 3.14159265 / n;
	glVertex3f(radius * cos(angle) + cx, radius * sin(angle) + cy, z);
	for (k = 0; k < n; k++)
	{
		angle += angleInc;
		glVertex3f(radius * cos(angle) + cx, radius * sin(angle) + cy, z);
	}
}
void pillar_dalam() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(250, 400, 0);
	gluCylinder(gluNewQuadric(), 10.0,10.0, 600.0, 10.0, 50);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(400, 250, 0);
	gluCylinder(gluNewQuadric(), 10.0,10.0, 600.0, 10.0, 50);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(300, 370, 0);
	gluCylinder(gluNewQuadric(), 10.0,10.0, 600.0, 10.0, 50);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(370, 300, 0);
	gluCylinder(gluNewQuadric(), 10.0,10.0, 600.0, 10.0, 50);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(155, 405, 0);
	gluCylinder(gluNewQuadric(), 10.0,10.0, 600.0, 10.0, 50);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(405, 155, 0);
	gluCylinder(gluNewQuadric(), 10.0,10.0, 600.0, 10.0, 50);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(100, 270, 0);
	gluCylinder(gluNewQuadric(), 10.0,10.0, 600.0, 10.0, 50);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(270, 100, 0);
	gluCylinder(gluNewQuadric(), 10.0,10.0, 600.0, 10.0, 50);
	glPopMatrix();
}

void pillar_luar() //tiang
{
    glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(0, 200, 0);
	gluCylinder(gluNewQuadric(), 2.0,2.0, 100.0, 10.0, 50);
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(45, 196, 0);
	gluCylinder(gluNewQuadric(), 2.0,2.0, 100.0, 10.0, 50);
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(80, 180, 0);
	gluCylinder(gluNewQuadric(), 2.0,2.0, 100.0, 10.0, 50);
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(120, 150, 0);
	gluCylinder(gluNewQuadric(), 2.0,2.0, 100.0, 10.0, 50);
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(152, 120, 0);
	gluCylinder(gluNewQuadric(), 2.0,2.0, 100.0, 10.0, 50);
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(180, 79, 0);
	gluCylinder(gluNewQuadric(), 2.0,2.0, 100.0, 10.0, 50);
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(195, 35, 0);
	gluCylinder(gluNewQuadric(), 2.0,2.0, 100.0, 10.0, 50);
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(200, 5, 0);
	gluCylinder(gluNewQuadric(), 2.0,2.0, 100.0, 10.0, 50);
	glPopMatrix();
}

void balok(float x1, float x2, float y1, float y2, float z1, float z2)
{
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);

	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);

	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y1, z2);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y2, z2);

	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y2, z1);

	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y2, z1);

	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);
}

void draw_cylinder(GLfloat radius,
	GLfloat height,
	GLfloat R,
	GLfloat G,
	GLfloat B, GLfloat R1, GLfloat G1, GLfloat B1)
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glColor3f(R, G, B);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glColor3f(R1,G1, B1);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
}

struct Motion {
	bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
	glClearColor(0.529, 0.807, 0.921, 0.0);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glutWarpPointer(width / 2, height / 2);

    Image* image = loadBMP("1.bmp");
    Image* image2 = loadBMP("2.bmp");
    Image* image3 = loadBMP("3.bmp");
    _textureId = loadTexture(image);
    _textureId2 = loadTexture(image2);
    _textureId3 = loadTexture(image3);
     delete image;
}

void tangga1() {
	glBegin(GL_QUAD_STRIP);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, -150);
	glVertex3f(0, -10, -150);
	glVertex3f(40, 0, -140);
	glVertex3f(40, -10, -140);
	glVertex3f(76, 0, -120);
	glVertex3f(76, -10, -120);
	glVertex3f(100, 0, -100);
	glVertex3f(100, -10, -100);
	glVertex3f(121, 0, -74);
	glVertex3f(121, -10, -74);
	glVertex3f(140, 0, -39);
	glVertex3f(140, -10, -39);
	glVertex3f(150, 0, 0);
	glVertex3f(150, -10, 0);
	glEnd();
}
void dasar1() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.9, 0.6);
	glVertex3f(0.0, 00.0, -680.0);
	glVertex3f(680.0, 00.0, -680.0);
	glVertex3f(0.0, 0.0, -150.0);
	glVertex3f(40.0, 0.0, -140.0);
	glVertex3f(76.0, 0.0, -120.0);
	glVertex3f(100.0, 0.0, -100.0);
	glVertex3f(121.0, 0.0, -74.0);
	glVertex3f(140.0, 0.0, -39.0);
	glVertex3f(150.0, 0.0, 0.0);
	glVertex3f(680.0, 0.0, 0.0);
	glVertex3f(680.0, 00.0, -680.0);
	glEnd();
}

void dasar2() {
	glBegin(GL_POLYGON);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(0.0, 00.0, -680.0);
	glVertex3f(680.0, 00.0, -680.0);
	glVertex3f(0.0, 0.0, -150.0);
	glVertex3f(40.0, 0.0, -140.0);
	glVertex3f(76.0, 0.0, -120.0);
	glVertex3f(100.0, 0.0, -100.0);
	glVertex3f(121.0, 0.0, -74.0);
	glVertex3f(140.0, 0.0, -39.0);
	glVertex3f(150.0, 0.0, 0.0);
	glVertex3f(680.0, 0.0, 0.0);
	glVertex3f(680.0, 00.0, -680.0);
	glEnd();
}
void tanggaKanan() {
	glBegin(GL_QUADS);
	glColor3f(1,1,0.8);
	balok(340,350, 0, 8, -55, -86);
	glEnd();
}
void tanggaKananP() {
	glBegin(GL_QUADS);
	glColor3f(1,1,0.8);
	balok(240,260, 72, 80, -52, -19);
	glEnd();
}
void lantaitangga1(){
    glBegin(GL_QUADS);
    glColor3f(1,1,0.9);
    balok(270,219,74,64,-100,0);
    glEnd();
}
void lantaitangga2(){
    glBegin(GL_QUADS);
    glColor3f(1,1,0.9);
    balok(400,330,149.9,110,-100,0);
    glEnd();
}
void tanggaKanan1(){
	glPushMatrix();
	tanggaKanan();
	glTranslatef(-10, 8, 0);
	tanggaKanan();
	glTranslatef(-10, 8, 0);
	tanggaKanan();
	glTranslatef(-10, 8, 0);
	tanggaKanan();
	glTranslatef(-10, 8, 0);
	tanggaKanan();
	glTranslatef(-10, 8, 0);
	tanggaKanan();
	glTranslatef(-10, 8, 0);
	tanggaKanan();
		glTranslatef(-10, 8, 0);
	tanggaKanan();

	glPopMatrix();
}
void tanggaKanan2(){
    glPushMatrix();
    tanggaKananP();
    glTranslatef(10,8,0);
    tanggaKananP();
    glTranslatef(10,8,0);
    tanggaKananP();
    glTranslatef(10,8,0);
    tanggaKananP();
    glTranslatef(10,8,0);
    tanggaKananP();
    glTranslatef(10,8,0);
    tanggaKananP();
    glTranslatef(10,8,0);
    tanggaKananP();
    glTranslatef(10,8,0);
    tanggaKananP();
    glTranslatef(10,8,0);
    tanggaKananP();
    glPopMatrix();
}
void tanggaR(){
    tanggaKanan1();
    glPushMatrix();
    glTranslatef(0,150,0);
    tanggaKanan1();
    glTranslatef(0,150,0);
    tanggaKanan1();
    glTranslatef(0,150,0);
    tanggaKanan1();
    glPopMatrix();

    tanggaKanan2();
    glPushMatrix();
    glTranslatef(0,150,0);
    tanggaKanan2();
    glTranslatef(0,150,0);
    tanggaKanan2();
    glPopMatrix();

    lantaitangga1();
    glPushMatrix();
    glTranslatef(0,150,0);
    lantaitangga1();
    glTranslatef(0,150,0);
    lantaitangga1();
    glPopMatrix();

    lantaitangga2();
    glPushMatrix();
    glTranslatef(0,150,0);
    lantaitangga2();
    glTranslatef(-5,150,0);
    lantaitangga2();
    glPopMatrix();
}
void draw() {
	glTranslatef(0, 30, 0);
	dasar1();
	tangga1();
	glLineWidth(1.0);
	glPushMatrix();
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);

	//base
	glPushMatrix();
	glTranslatef(-10, -10, 10);
	tangga1();
	dasar2();
	glTranslatef(-10, -10, 10);
	tangga1();
	dasar2();
	glTranslatef(-10, -10, 10);
	tangga1();
	dasar2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70, -39.9, -70);
	glRotatef(-90, 1, 0, 0);
	draw_cylinder(150, 10, 0.2, 0.2, 0.2,0.5,0.5,0.5);
	glTranslatef(-10, -10, -10);
	draw_cylinder(150, 10, 0.2, 0.2, 0.2, 0.5, 0.5, 0.5);
	glTranslatef(-10, -10, -10);
	draw_cylinder(150, 10, 0.2, 0.2, 0.2, 0.5, 0.5, 0.5);
	glPopMatrix();

    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
    balok(150,680,-0.1,-60,-680,60);
    balok(150,-60,-0.1,-60,-150,-680);
    glEnd();
		//tangga kanan
    tanggaR();

	//tembok depan kiri
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(100.0, 0.0, 0.0, 600.0, -220.0, -210.0);
	glEnd();
	//tembok samping kiri
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(0.0, 10.0, 0.0, 600.0, -500.0, -210.0);
	glEnd();
	//tembok samping belakang kiri
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	balok(90.0, 100.0, 0.0, 600.0, -500.0, -650.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(90.0, 100.0, 0.0, 140.0, -500.0, -400.0);
	glEnd();
	//tembok samping belakang belakang kiri
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(0.0, 100.0, 109.99, 600.0, -500.0, -490.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(0.0, 100.0, 0.0, 140.0, -395.1, -405.0);
	glEnd();
	//tembok belakang kiri
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	balok(90.0, 660.0, 0.0, 680.0, -660.0, -650.0);
	glEnd();
	//tembok depan dalam kiri
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(100.0, 90.0, 0.0, 600.0, -270.0, -220.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(100.1, 90.0, 110.0, 600.0, -270.0, -350.0);
	glEnd();

    //tembok depan kanan
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(220.0, 210.0, 0.0, 600.0, -100.0, 0.0);
	glEnd();
	//tembok samping kanan
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(500.0, 210.0, 0.0, 600.0, 0.0, -10.0);
	glEnd();
	//tembok samping belakang kanan
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	balok(500.0, 650.0, 0.0, 600.0, -90.0, -100.0);
	glEnd();
	//tembok samping belakang kanan
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(500.0, 400.0, 0.0, 140.0, -90.0, -100.0);
	glEnd();
	//tembok samping belakang belakang kanan
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(490.0, 500.0, 109.99, 600.0, 0.0, -100.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(395.1, 405.0, 0.0, 140.0, 0.0, -100.0);
	glEnd();
	//tembok belakang kanan
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	balok(660.0, 650.0, 0.0, 680.0, -90.0, -660.0);
	glEnd();
	//tembok depan dalam kanan
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	balok(270.0, 220.0, 0.0, 600.0, -100.0, -90.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1,1,0.9);
	balok(270.0, 350.0, 110.0, 600.0, -100.1, -90.0);
	glEnd();
	//tembok kiri dalam kiri (interior pojok)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(410.0, 400.0, 0.0, 120.0, -650.0, -500.0);
	glEnd();
	//tembok kanan dalam kiri (interior pojok)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(650.0, 500.0, 0.0, 120.0, -410.0, -420.0);
	glEnd();
	//tembok kiri dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(200.0, 190.0, 0.0, 120.0, -650.0, -540.0);
	glEnd();
	//tembok kiri dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(540.0, 650.0, 0.0, 120.0, -330.0, -320.0);
	glEnd();
	//tembok kiri dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(540.0, 650.0, 0.0, 120.0, -260.0, -250.0);
	glEnd();
	//tembok kiri dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(540.0, 650.0, 0.0, 120.0, -190.0, -180.0);
	glEnd();
	//tembok kiri dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(270.0, 260.0, 0.0, 120.0, -650.0, -540.0);
	glEnd();
	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(150.0, 300.0, 0.0, 120.0, -490.0, -480.0);
	glEnd();
	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(150.0, 260.0, 0.0, 120.0, -400.0, -410.0);
	glEnd();
	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	glVertex3f(300.0, 120.0, -490.0);
	glVertex3f(370.0, 120.0, -430.0);
	glVertex3f(370.0, 0.0, -430.0);
	glVertex3f(300.0, 0.0, -490.0);
	glEnd();

	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(260.0, 250.0, 0.0, 120.0, -400.0, -490.0);
	glEnd();
	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(150.0, 160.0, 0.0, 120.0, -400.0, -490.0);
	glEnd();
	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	glVertex3f(300.0, 120.0, -360.0);
	glVertex3f(370.0, 120.0, -430.0);
	glVertex3f(370.0, 0.0, -430.0);
	glVertex3f(300.0, 0.0, -360.0);
	glEnd();
	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	glVertex3f(260.0, 120.0, -400.0);
	glVertex3f(300.0, 120.0, -360.0);
	glVertex3f(300.0, 0.0, -360.0);
	glVertex3f(260.0, 0.0, -400.0);
	glEnd();

	//tembok tengah dalam kanan (interior kanan)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(400.0, 490.0, 0.0, 120.0, -260.0, -260.0);
	glEnd();
	//tembok tengah dalam kanan (interior kanan)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(490.0, 490.0, 0.0, 120.0, -160.0, -310.0);
	glEnd();
	//tembok tengah dalam kanan (interior kanan)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(400.0, 490.0, -0.01, 120.0, -160.0, -260.0);
	glEnd();
	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	glVertex3f(360.0, 120.0, -300.0);
	glVertex3f(400.0, 120.0, -260.0);
	glVertex3f(400.0, 0.0, -260.0);
	glVertex3f(360.0, 0.0, -300.0);
	glEnd();

	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	glVertex3f(360.0, 120.0, -300.0);
	glVertex3f(430.0, 120.0, -370.0);
	glVertex3f(430.0, 0.0, -370.0);
	glVertex3f(360.0, 0.0, -300.0);
	glEnd();

	//tembok tengah dalam kiri (interior kiri)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	glVertex3f(430.0, 120.0, -370.0);
	glVertex3f(490.0, 120.0, -310.0);
	glVertex3f(490.0, 0.0, -310.0);
	glVertex3f(430.0, 0.0, -370.0);
	glEnd();

	//lantai 2

	//dasarlantai2
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.9, 0.6);
    glVertex3f(0.0, 150.0, -395.0);
	glVertex3f(0.0, 150.0, -500.0);
    glVertex3f(100.0, 150.0, -395.0);
	glVertex3f(100.0, 150.0, -500.0);
	glVertex3f(100.0, 150.0, -395.0);
	glVertex3f(100.0, 150.0, -650.0);
	glVertex3f(200.0, 150.0, -395.0);
	glVertex3f(200.0, 150.0, -650.0);
	glVertex3f(250.0, 150.0, -380.0);
	glVertex3f(250.0, 150.0, -650.0);
	glVertex3f(295.0, 150.0, -355.0);
	glVertex3f(295.0, 150.0, -650.0);
	glVertex3f(328.0, 150.0, -328.0);
	glVertex3f(650.0, 150.0, -650.0);
	glVertex3f(355.0, 150.0, -295.0);
	glVertex3f(650.0, 150.0, -295.0);
	glVertex3f(380.0, 150.0, -250.0);
    glVertex3f(650.0, 150.0, -250.0);
	glVertex3f(395.0, 150.0, -200.0);
    glVertex3f(650.0, 150.0, -200.0);
	glVertex3f(395.0, 150.0, -100.0);
	glVertex3f(650.0, 150.0, -100.0);
	glVertex3f(395.0, 150.0, -100.0);
	glVertex3f(500.0, 150.0, -100.0);
	glVertex3f(395.0, 150.0, 0.0);
	glVertex3f(500.0, 150.0, 0.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 1.0,0.9);
	glVertex3f(0.0, 150.0, -395.0);
	glVertex3f(0.0, 110.0, -395.0);
	glVertex3f(100.0, 150.0, -395.0);
	glVertex3f(100.0, 110.0, -395.0);
	glVertex3f(200.0, 150.0, -395.0);
	glVertex3f(200.0, 110.0, -395.0);
	glVertex3f(250.0, 150.0, -380.0);
	glVertex3f(250.0, 110.0, -380.0);
	glVertex3f(295.0, 150.0, -355.0);
	glVertex3f(295.0, 110.0, -355.0);
	glVertex3f(328.0, 150.0, -328.0);
	glVertex3f(328.0, 110.0, -328.0);
	glVertex3f(355.0, 150.0, -295.0);
	glVertex3f(355.0, 110.0, -295.0);
	glVertex3f(380.0, 150.0, -250.0);
	glVertex3f(380.0, 110.0, -250.0);
	glVertex3f(395.0, 150.0, -200.0);
	glVertex3f(395.0, 110.0, -200.0);
	glVertex3f(395.0, 150.0, -100.0);
	glVertex3f(395.0, 110.0, -100.0);
	glVertex3f(395.0, 150.0, 0.0);
	glVertex3f(395.0, 110.0, 0.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.9, 0.6);
	glVertex3f(0.0, 110.0, -395.0);
	glVertex3f(0.0, 110.0, -500.0);
    glVertex3f(100.0, 110.0, -395.0);
	glVertex3f(100.0, 110.0, -500.0);
	glVertex3f(100.0, 110.0, -395.0);
	glVertex3f(100.0, 110.0, -650.0);
	glVertex3f(200.0, 110.0, -395.0);
	glVertex3f(200.0, 110.0, -650.0);
	glVertex3f(250.0, 110.0, -380.0);
	glVertex3f(250.0, 110.0, -650.0);
	glVertex3f(295.0, 110.0, -355.0);
	glVertex3f(295.0, 110.0, -650.0);
	glVertex3f(328.0, 110.0, -328.0);
	glVertex3f(650.0, 110.0, -650.0);
	glVertex3f(355.0, 110.0, -295.0);
	glVertex3f(650.0, 110.0, -295.0);
	glVertex3f(380.0, 110.0, -250.0);
    glVertex3f(650.0, 110.0, -250.0);
	glVertex3f(395.0, 110.0, -200.0);
    glVertex3f(650.0, 110.0, -200.0);
	glVertex3f(395.0, 110.0, -100.0);
	glVertex3f(650.0, 110.0, -100.0);
	glVertex3f(395.0, 110.0, -100.0);
	glVertex3f(500.0, 110.0, -100.0);
	glVertex3f(395.0, 110.0, 0.0);
	glVertex3f(500.0, 110.0, 0.0);
	glEnd();

    //Interior Dalam
    glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(649.99, 490.0, 149.99, 280.0, -150.0, -100.0);
	balok(150.0, 100.0, 149.99, 280.0, -649.99, -490.0 );
	balok(649.99, 490.0, 149.99, 280.0, -200.0, -350.0);
	balok(200.0, 350.0, 149.99, 280.0, -649.99, -490.0 );

	glVertex3f(500.0, 150.0, -350.0);
	glVertex3f(500.0, 280.0, -350.0);
	glVertex3f(550.0, 280.0, -400.0);
	glVertex3f(550.0, 150.0, -400.0);

	glVertex3f(550.0, 280.0, -400.0);
	glVertex3f(550.0, 150.0, -400.0);
	glVertex3f(550.0, 150.0, -450.0);
	glVertex3f(550.0, 280.0, -450.0);

	glVertex3f(350.0, 150.0, -500.0);
	glVertex3f(350.0, 280.0, -500.0);
	glVertex3f(400.0, 280.0, -550.0);
	glVertex3f(400.0, 150.0, -550.0);

	glVertex3f(450.0, 150.0, -550.0);
	glVertex3f(450.0, 280.0, -550.0);
	glVertex3f(400.0, 280.0, -550.0);
	glVertex3f(400.0, 150.0, -550.0);

	glVertex3f(550.0, 150.0, -450.0);
	glVertex3f(550.0, 280.0, -450.0);
	glVertex3f(450.0, 280.0, -550.0);
	glVertex3f(450.0, 150.0, -550.0);
	glEnd();

	//lantai 3

	//dasarlantai3
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.9, 0.6);
    glVertex3f(0.0, 300.0, -395.0);
	glVertex3f(0.0, 300.0, -500.0);
    glVertex3f(100.0, 300.0, -395.0);
	glVertex3f(100.0, 300.0, -500.0);
	glVertex3f(100.0, 300.0, -395.0);
	glVertex3f(100.0, 300.0, -650.0);
	glVertex3f(200.0, 300.0, -395.0);
	glVertex3f(200.0, 300.0, -650.0);
	glVertex3f(250.0, 300.0, -380.0);
	glVertex3f(250.0, 300.0, -650.0);
	glVertex3f(295.0, 300.0, -355.0);
	glVertex3f(295.0, 300.0, -650.0);
	glVertex3f(328.0, 300.0, -328.0);
	glVertex3f(650.0, 300.0, -650.0);
	glVertex3f(355.0, 300.0, -295.0);
	glVertex3f(650.0, 300.0, -295.0);
	glVertex3f(380.0, 300.0, -250.0);
    glVertex3f(650.0, 300.0, -250.0);
	glVertex3f(395.0, 300.0, -200.0);
    glVertex3f(650.0, 300.0, -200.0);
	glVertex3f(395.0, 300.0, -100.0);
	glVertex3f(650.0, 300.0, -100.0);
	glVertex3f(395.0, 300.0, -100.0);
	glVertex3f(500.0, 300.0, -100.0);
	glVertex3f(395.0, 300.0, 0.0);
	glVertex3f(500.0, 300.0, 0.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 1.0,0.9);
	glVertex3f(0.0, 300.0, -395.0);
	glVertex3f(0.0, 260.0, -395.0);
	glVertex3f(100.0, 300.0, -395.0);
	glVertex3f(100.0, 260.0, -395.0);
	glVertex3f(200.0, 300.0, -395.0);
	glVertex3f(200.0, 260.0, -395.0);
	glVertex3f(250.0, 300.0, -380.0);
	glVertex3f(250.0, 260.0, -380.0);
	glVertex3f(295.0, 300.0, -355.0);
	glVertex3f(295.0, 260.0, -355.0);
	glVertex3f(328.0, 300.0, -328.0);
	glVertex3f(328.0, 260.0, -328.0);
	glVertex3f(355.0, 300.0, -295.0);
	glVertex3f(355.0, 260.0, -295.0);
	glVertex3f(380.0, 300.0, -250.0);
	glVertex3f(380.0, 260.0, -250.0);
	glVertex3f(395.0, 300.0, -200.0);
	glVertex3f(395.0, 260.0, -200.0);
	glVertex3f(395.0, 300.0, -100.0);
	glVertex3f(395.0, 260.0, -100.0);
	glVertex3f(395.0, 300.0, 0.0);
	glVertex3f(395.0, 260.0, 0.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.9, 0.6);
	glVertex3f(0.0, 260.0, -395.0);
	glVertex3f(0.0, 260.0, -500.0);
    glVertex3f(100.0, 260.0, -395.0);
	glVertex3f(100.0, 260.0, -500.0);
	glVertex3f(100.0, 260.0, -395.0);
	glVertex3f(100.0, 260.0, -650.0);
	glVertex3f(200.0, 260.0, -395.0);
	glVertex3f(200.0, 260.0, -650.0);
	glVertex3f(250.0, 260.0, -380.0);
	glVertex3f(250.0, 260.0, -650.0);
	glVertex3f(295.0, 260.0, -355.0);
	glVertex3f(295.0, 260.0, -650.0);
	glVertex3f(328.0, 260.0, -328.0);
	glVertex3f(650.0, 260.0, -650.0);
	glVertex3f(355.0, 260.0, -295.0);
	glVertex3f(650.0, 260.0, -295.0);
	glVertex3f(380.0, 260.0, -250.0);
    glVertex3f(650.0, 260.0, -250.0);
	glVertex3f(395.0, 260.0, -200.0);
    glVertex3f(650.0, 260.0, -200.0);
	glVertex3f(395.0, 260.0, -100.0);
	glVertex3f(650.0, 260.0, -100.0);
	glVertex3f(395.0, 260.0, -100.0);
	glVertex3f(500.0, 260.0, -100.0);
	glVertex3f(395.0, 260.0, 0.0);
	glVertex3f(500.0, 260.0, 0.0);
	glEnd();

	//Interior Dalam
    glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.9);
	balok(649.99, 490.0, 299.99, 430.0, -150.0, -100.0);
	balok(150.0, 100.0, 299.99, 430.0, -649.99, -490.0 );
	balok(649.99, 490.0, 299.99, 430.0, -200.0, -400.0);
	balok(200.0, 400.0, 299.99, 430.0, -649.99, -490.0 );

	glVertex3f(500.0, 300.0, -400.0);
	glVertex3f(500.0, 430.0, -400.0);
	glVertex3f(550.0, 430.0, -450.0);
	glVertex3f(550.0, 300.0, -450.0);

	glVertex3f(400.0, 300.0, -500.0);
	glVertex3f(400.0, 430.0, -500.0);
	glVertex3f(450.0, 430.0, -550.0);
	glVertex3f(450.0, 300.0, -550.0);

	glVertex3f(550.0, 300.0, -450.0);
	glVertex3f(550.0, 430.0, -450.0);
	glVertex3f(450.0, 430.0, -550.0);
	glVertex3f(450.0, 300.0, -550.0);
	glEnd();



	//lantai 4

	//dasarlantai4
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.9, 0.6);
    glVertex3f(0.0, 450.0, -325.0);
	glVertex3f(0.0, 450.0, -500.0);
    glVertex3f(100.0, 450.0, -325.0);
	glVertex3f(100.0, 450.0, -500.0);
	glVertex3f(100.0, 450.0, -220.0);
	glVertex3f(100.0, 450.0, -650.0);
	glVertex3f(200.0, 450.0, -120.0);
	glVertex3f(200.0, 450.0, -650.0);
	glVertex3f(220.0, 450.0, -100.0);
	glVertex3f(220.0, 450.0, -650.0);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.9, 0.6);
    glVertex3f(325.0, 450.0, 0.0);
	glVertex3f(500.0, 450.0, 0.0);
    glVertex3f(325.0, 450.0, -100.0);
	glVertex3f(500.0, 450.0, -100.0);
	glVertex3f(220.0, 450.0, -100.0);
	glVertex3f(650.0, 450.0, -100.0);
	glVertex3f(120.0, 450.0, -200.0);
	glVertex3f(650.0, 450.0, -200.0);
	glVertex3f(100.0, 450.0, -220.0);
	glVertex3f(650.0, 450.0, -220.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.9, 0.6);
    glVertex3f(0.0, 410.0, -325.0);
	glVertex3f(0.0, 410.0, -500.0);
    glVertex3f(100.0, 410.0, -325.0);
	glVertex3f(100.0, 410.0, -500.0);
	glVertex3f(100.0, 410.0, -220.0);
	glVertex3f(100.0, 410.0, -650.0);
	glVertex3f(200.0, 410.0, -120.0);
	glVertex3f(200.0, 410.0, -650.0);
	glVertex3f(220.0, 410.0, -100.0);
	glVertex3f(220.0, 410.0, -650.0);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.9, 0.6);
    glVertex3f(325.0, 410.0, 0.0);
	glVertex3f(500.0, 410.0, 0.0);
    glVertex3f(325.0, 410.0, -100.0);
	glVertex3f(500.0, 410.0, -100.0);
	glVertex3f(220.0, 410.0, -100.0);
	glVertex3f(650.0, 410.0, -100.0);
	glVertex3f(120.0, 410.0, -200.0);
	glVertex3f(650.0, 410.0, -200.0);
	glVertex3f(100.0, 410.0, -220.0);
	glVertex3f(650.0, 410.0, -220.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.9, 0.6);
    balok(220.0, 650.0, 410.0, 450.0, -220.0, -650.0);

    glVertex3f(270.0, 410.0, -100.0);
    glVertex3f(270.0, 450.0, -100.0);
    glVertex3f(100.0, 450.0, -270.0);
    glVertex3f(100.0, 410.0, -270.0);
	glEnd();

    //Merah Lantai 4
    glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(80.0,600.0,-210.0);
	glVertex3f(80.0,550.0,-210.0);
	glVertex3f(115.0,600.0,-195.0);
	glVertex3f(115.0,550.0,-195.0);
	glVertex3f(159.0,600.0,-159.0);
	glVertex3f(159.0,550.0,-159.0);
	glVertex3f(195.0,600.0,-115.0);
	glVertex3f(195.0,550.0,-115.0);
	glVertex3f(210.0,600.0,-80.0);
	glVertex3f(210.0,550.0,-80.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100.0,600.0,-220.0);
	glVertex3f(80.0,600.0,-210.0);
	glVertex3f(120.0,600.0,-200.0);
	glVertex3f(115.0,600.0,-195.0);
	glVertex3f(160.0,600.0,-160.0);
	glVertex3f(159.0,600.0,-159.0);
	glVertex3f(200.0,600.0,-120.0);
	glVertex3f(195.0,600.0,-115.0);
	glVertex3f(220.0,600.0,-100.0);
	glVertex3f(210.0,600.0,-80.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100.0,550.0,-220.0);
	glVertex3f(80.0,550.0,-210.0);
	glVertex3f(120.0,550.0,-200.0);
	glVertex3f(115.0,550.0,-195.0);
	glVertex3f(160.0,550.0,-160.0);
	glVertex3f(159.0,550.0,-159.0);
	glVertex3f(200.0,550.0,-120.0);
	glVertex3f(195.0,550.0,-115.0);
	glVertex3f(220.0,550.0,-100.0);
	glVertex3f(210.0,550.0,-80.0);
	glEnd();

	//Merah Lantai 3
    glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(80.0,400.0,-210.0);
	glVertex3f(80.0,350.0,-210.0);
	glVertex3f(115.0,400.0,-195.0);
	glVertex3f(115.0,350.0,-195.0);
	glVertex3f(159.0,400.0,-159.0);
	glVertex3f(159.0,350.0,-159.0);
	glVertex3f(195.0,400.0,-115.0);
	glVertex3f(195.0,350.0,-115.0);
	glVertex3f(210.0,400.0,-80.0);
	glVertex3f(210.0,350.0,-80.0);
	glEnd();

    glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100.0,400.0,-220.0);
	glVertex3f(80.0,400.0,-210.0);
	glVertex3f(120.0,400.0,-200.0);
	glVertex3f(115.0,400.0,-195.0);
	glVertex3f(160.0,400.0,-160.0);
	glVertex3f(159.0,400.0,-159.0);
	glVertex3f(200.0,400.0,-120.0);
	glVertex3f(195.0,400.0,-115.0);
	glVertex3f(220.0,400.0,-100.0);
	glVertex3f(210.0,400.0,-80.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100.0,350.0,-220.0);
	glVertex3f(80.0,350.0,-210.0);
	glVertex3f(120.0,350.0,-200.0);
	glVertex3f(115.0,350.0,-195.0);
	glVertex3f(160.0,350.0,-160.0);
	glVertex3f(159.0,350.0,-159.0);
	glVertex3f(200.0,350.0,-120.0);
	glVertex3f(195.0,350.0,-115.0);
	glVertex3f(220.0,350.0,-100.0);
	glVertex3f(210.0,350.0,-80.0);
	glEnd();

	 //Merah Lantai 2
    glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100.0,170.0,-220.0);
	glVertex3f(100.0,220.0,-220.0);
	glVertex3f(132.0,170.0,-202.0);
	glVertex3f(132.0,220.0,-202.0);
	glVertex3f(160.0,170.0,-180.0);
	glVertex3f(160.0,220.0,-180.0);
	glVertex3f(180.0,170.0,-160.0);
	glVertex3f(180.0,220.0,-160.0);
	glVertex3f(202.0,170.0,-132.0);
	glVertex3f(202.0,220.0,-132.0);
	glVertex3f(220.0,170.0,-100.0);
	glVertex3f(220.0,220.0,-100.0);
	glEnd();

	//Merah Lantai 1
    glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0,150.0,-220.0);
	glVertex3f(0.0,100.0,-220.0);
	glVertex3f(0.0,150.0,-205.0);
	glVertex3f(0.0,100.0,-205.0);
	glVertex3f(40.0,150.0,-200.0);
	glVertex3f(40.0,100.0,-200.0);
	glVertex3f(80.0,150.0,-185.0);
	glVertex3f(80.0,100.0,-185.0);
	glVertex3f(125.0,150.0,-155.0);
	glVertex3f(125.0,100.0,-155.0);
	glVertex3f(155.0,150.0,-125.0);
	glVertex3f(155.0,100.0,-125.0);
	glVertex3f(185.0,150.0,-80.0);
	glVertex3f(185.0,100.0,-80.0);
	glVertex3f(200.0,150.0,-40.0);
	glVertex3f(200.0,100.0,-40.0);
	glVertex3f(205.0,150.0,0.0);
	glVertex3f(205.0,100.0,0.0);
	glVertex3f(220.0,150.0,0.0);
	glVertex3f(220.0,100.0,0.0);
	glEnd();

	//Merah Lantai 1
    glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0,150.0,-220.0);
	glVertex3f(100.0,150.0,-220.0);
	glVertex3f(0.0,150.0,-205.0);
	glVertex3f(100.0,150.0,-220.0);
	glVertex3f(40.0,150.0,-200.0);
	glVertex3f(120.0,150.0,-200.0);
	glVertex3f(80.0,150.0,-185.0);
	glVertex3f(120.0,150.0,-200.0);
	glVertex3f(125.0,150.0,-155.0);
    glVertex3f(160.0,150.0,-160.0);
	glVertex3f(155.0,150.0,-125.0);
    glVertex3f(160.0,150.0,-160.0);
	glVertex3f(185.0,150.0,-80.0);
	glVertex3f(200.0,150.0,-120.0);
	glVertex3f(200.0,150.0,-40.0);
	glVertex3f(220.0,150.0,-100.0);
	glVertex3f(205.0,150.0,0.0);
	glVertex3f(220.0,150.0,-80.0);
	glVertex3f(220.0,150.0,0.0);
	glVertex3f(220.0,150.0,-80.0);
	glEnd();

    glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 1.0, 0.6);
	glVertex3f(99.99,150.0,-220.0);
	glVertex3f(99.99,100.0,-220.0);
	glVertex3f(119.99,150.0,-200.0);
    glVertex3f(119.99,100.0,-200.0);
	glVertex3f(159.99,150.0,-159.99);
	glVertex3f(159.99,100.0,-159.99);
	glVertex3f(200.0,150.0,-119.99);
	glVertex3f(200.0,100.0,-119.99);
	glVertex3f(220.0,150.0,-99.99);
	glVertex3f(220.0,100.0,-99.99);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.6);
	glVertex3f(99.99,0.0,-220.0);
	glVertex3f(99.99,100.0,-220.0);
	glVertex3f(119.99,100.0,-200.0);
    glVertex3f(119.99,0.0,-200.0);

    glVertex3f(200.0,0.0,-119.99);
	glVertex3f(200.0,100.0,-119.99);
	glVertex3f(220.0,100.0,-99.99);
	glVertex3f(220.0,0.0,-99.99);
	glEnd();

//warna bata
    glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	glVertex3f(209.5,0.0,0.0);
	glVertex3f(209.5,0.0,-100.0);
	glVertex3f(209.5,600.0,-100.0);
	glVertex3f(209.5,600.0,0.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	glVertex3f(100.0,0.0,-209.5);
	glVertex3f(0.0,0.0,-209.5);
	glVertex3f(0.0,600.0,-209.5);
	glVertex3f(100.0,600.0,-209.5);
	glEnd();

// Garis bata
for (int i = 1; i < 5; i++)
{       glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(209.0,0.0,0.0-(i*20));
        glVertex3f(209.0,600.0,0.0-(i*20));
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0+(i*20),0.0,-209);
        glVertex3f(0.0+(i*20),600.0,-209);
        glEnd();
}

for (int i = 1; i < 10; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*60),-209);
        glVertex3f(100.0,0.0+(i*60),-209);
        glEnd();

         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(209.0,0.0+(i*60),-0);
        glVertex3f(209.0,0.0+(i*60),-100);
        glEnd();
    }

    for (int i = 1; i < 20; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*30),-209);
        glVertex3f(100.0,0.0+(i*30),-209);
        glEnd();

         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(209.0,0.0+(i*30),-0);
        glVertex3f(209.0,0.0+(i*30),-100);
        glEnd();
    }


    for (int i = 1; i < 40; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*15),-209);
        glVertex3f(100.0,0.0+(i*15),-209);
        glEnd();

         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(209.0,0.0+(i*15),-0);
        glVertex3f(209.0,0.0+(i*15),-100);
        glEnd();
    }

    for (int i = 1; i < 80; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*7.5),-209);
        glVertex3f(100.0,0.0+(i*7.5),-209);
        glEnd();

         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(209.0,0.0+(i*7.5),-0);
        glVertex3f(209.0,0.0+(i*7.5),-100);
        glEnd();
    }

//tembok samping kanan
    for (int i = 0; i < 12; i++)
    {
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(239.0,0.0+(i*50),1.0);
        glVertex3f(471.0,0.0+(i*50),1.0);
        glEnd();
    }

     for (int i = 0; i < 9; i++)
    {
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(239.0+(i*29),0.0,1.0);
        glVertex3f(239.0+(i*29),600.0,1.0);
        glEnd();
    }

     glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(239.0,0.0,0.5);
        glVertex3f(471.0,0.0,0.5);
        glVertex3f(471.0,550.0,0.5);
        glVertex3f(239.0,550.0,0.5);
        glEnd();

      glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(239.0,600.0,0.5);
        glVertex3f(471.0,600.0,0.5);
        glVertex3f(471.0,550.0,0.5);
        glVertex3f(239.0,550.0,0.5);
        glEnd();

      glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(500.0,600.0,0.5);
        glVertex3f(471.0,600.0,0.5);
        glVertex3f(471.0,0.0,0.5);
        glVertex3f(500.0,0.0,0.5);
        glEnd();
//tembok samping kiri
 for (int i = 0; i < 12; i++)
    {
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-1.0,0.0+(i*50),-239.0);
        glVertex3f(-1.0,0.0+(i*50),-471.0);
        glEnd();
    }

     for (int i = 0; i < 9; i++)
    {
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-1.0,0.0,-239-(i*29));
        glVertex3f(-1,600.0,-239-(i*29));
        glEnd();
    }
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(-0.5,0.0,-239);
        glVertex3f(-0.5,0.0,-471);
        glVertex3f(-0.5,550.0,-471);
        glVertex3f(-0.5,550.0,-239);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5,600.0,-239);
        glVertex3f(-0.5,600.0,-471);
        glVertex3f(-0.5,550.0,-471);
        glVertex3f(-0.5,550.0,-239);
        glEnd();

         glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5,600.0,-500);
        glVertex3f(-0.5,600.0,-471);
        glVertex3f(-0.5,0.0,-471);
        glVertex3f(-0.5,0.0,-500);
        glEnd();

//warna bata kanan kiri
    glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	glVertex3f(-0.5,0.0,-239.0);
	glVertex3f(-0.5,0.0,-210.0);
	glVertex3f(-0.5,600.0,-210.0);
	glVertex3f(-0.5,600.0,-239.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	glVertex3f(210.0,0.0,0.5);
	glVertex3f(239.0,0.0,0.5);
	glVertex3f(239.0,600.0,0.5);
	glVertex3f(210.0,600.0,0.5);
	glEnd();

// Garis bata kanan kiri
for (int i = 0; i < 6; i++)
{       glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(210.0+(i*5),0.0,1.0);
        glVertex3f(210.0+(i*5),600.0,1.0);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-1.0,0.0,-210-(i*5));
        glVertex3f(-1.0,600.0,-210-(i*5));
        glEnd();
}

for (int i = 1; i < 10; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.5,0.0+(i*60),-210);
        glVertex3f(-0.5,0.0+(i*60),-239);
        glEnd();

         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(239.0,0.0+(i*60),1.0);
        glVertex3f(210.0,0.0+(i*60),1.0);
        glEnd();
    }

    for (int i = 1; i < 20; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.5,0.0+(i*30),-219);
        glVertex3f(-0.5,0.0+(i*30),-239);
        glEnd();

         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(210.0,0.0+(i*30),1.0);
        glVertex3f(239.0,0.0+(i*30),1.0);
        glEnd();
    }


    for (int i = 1; i < 40; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(-0.5,0.0+(i*15),-219);
        glVertex3f(-0.5,0.0+(i*15),-239);
        glEnd();

         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(239.0,0.0+(i*15),1.0);
        glVertex3f(210.0,0.0+(i*15),1.0);
        glEnd();
    }

    for (int i = 1; i < 80; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*7.5),-209);
        glVertex3f(100.0,0.0+(i*7.5),-209);
        glEnd();

         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(209.0,0.0+(i*7.5),-0);
        glVertex3f(209.0,0.0+(i*7.5),-100);
        glEnd();
    }

    //warna bata kanan

    glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	glVertex3f(500.5,0.0,0.0);
	glVertex3f(500.5,0.0,-100.0);
	glVertex3f(500.5,600.0,-100.0);
	glVertex3f(500.5,600.0,0.0);
	glEnd();
	//warna bata kiri
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	glVertex3f(100.0,0.0,-500.5);
	glVertex3f(0.0,0.0,-500.5);
	glVertex3f(0.0,600.0,-500.5);
	glVertex3f(100.0,600.0,-500.5);
	glEnd();

// Garis bata kanan
for (int i = 1; i < 5; i++)
{       glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(501.0,0.0,0.0-(i*20));
        glVertex3f(501.0,600.0,0.0-(i*20));
        glEnd();

}

for (int i = 1; i < 10; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*60),-501);
        glVertex3f(100.0,0.0+(i*60),-501);
        glEnd();


    }

    for (int i = 1; i < 20; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*30),-501);
        glVertex3f(100.0,0.0+(i*30),-501);
        glEnd();

    }


    for (int i = 1; i < 40; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*15),-501);
        glVertex3f(100.0,0.0+(i*15),-501);
        glEnd();

    }

    for (int i = 1; i < 80; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0,0.0+(i*7.5),-501);
        glVertex3f(100.0,0.0+(i*7.5),-501);
        glEnd();


    }


//garis bata kiri

for (int i = 1; i < 5; i++)
{

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0+(i*20),0.0,-501);
        glVertex3f(0.0+(i*20),600.0,-501);
        glEnd();
}

for (int i = 1; i < 10; i++)
    {


         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(501.0,0.0+(i*60),-0);
        glVertex3f(501.0,0.0+(i*60),-100);
        glEnd();
    }

    for (int i = 1; i < 20; i++)
    {


         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(501.0,0.0+(i*30),-0);
        glVertex3f(501.0,0.0+(i*30),-100);
        glEnd();
    }


    for (int i = 1; i < 40; i++)
    {


         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(501.0,0.0+(i*15),-0);
        glVertex3f(501.0,0.0+(i*15),-100);
        glEnd();
    }

    for (int i = 1; i < 80; i++)
    {



         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(501.0,0.0+(i*7.5),-0);
        glVertex3f(501.0,0.0+(i*7.5),-100);
        glEnd();
    }

//jendela kanan
glColor3f(1.0, 0.479, 0.3377);
	glVertex3f(209.5,0.0,0.0);
	glVertex3f(209.5,0.0,-100.0);
	glVertex3f(209.5,600.0,-100.0);
	glVertex3f(209.5,600.0,0.0);

glBegin(GL_QUADS);
glColor3f(1.0, 0.0, 0.0);
balok(209.0,204.0,100.0,110.0,-80.0,-20.0);
balok(209.0,204.0,510.0,520.0,-80.0,-20.0);
balok(209.0,204.0,100.0,520.0,-80.0,-75.0);
balok(209.0,204.0,100.0,520.0,-20.0,-25.0);
glColor3f(1.0, 1.0, 1.0);
balok(209.0,207.0,110.0,510.0,-25.0,-75.0);
glEnd();
//jendela kiri

glBegin(GL_QUADS);
glColor3f(1.0, 0.0, 0.0);
balok(80.0,20.0,100.0,110.0,-209.0,-204.0);
balok(80.0,20.0,510.0,520.0,-209.0,-204.0);
balok(80.0,75.0,100.0,520.0,-209.0,-204.0);
balok(20.0,25.0,100.0,520.0,-209.0,-204.0);
glColor3f(1.0, 1.0, 1.0);
balok(25.0,75.0,110.0,510.0,-209.0,-207.0);
glEnd();
//kanan belakang
glBegin(GL_QUADS);
glColor3f(1.0, 0.0, 0.0);
balok(502.0,507.0,100.0,110.0,-80.0,-20.0);
balok(502.0,507.0,510.0,520.0,-80.0,-20.0);
balok(502.0,507.0,100.0,520.0,-80.0,-75.0);
balok(502.0,507.0,100.0,520.0,-20.0,-25.0);
glColor3f(1.0, 1.0, 1.0);
balok(502.0,507.0,110.0,510.0,-25.0,-75.0);
glEnd();
//kiri belakang

glBegin(GL_QUADS);
glColor3f(1.0, 0.0, 0.0);
balok(80.0,20.0,100.0,110.0,-502.0,-507.0);
balok(80.0,20.0,510.0,520.0,-502.0,-507.0);
balok(80.0,75.0,100.0,520.0,-502.0,-507.0);
balok(20.0,25.0,100.0,520.0,-502.0,-507.0);
glColor3f(1.0, 1.0, 1.0);
balok(25.0,75.0,110.0,510.0,-502.0,-505.0);
glEnd();

pillar_dalam();
pillar_luar();


//depan kuning
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 0.0);
glVertex3f(100.0,350.0,-220);
glVertex3f(220.0,350.0,-100);
glVertex3f(220.0,600.0,-100);
glVertex3f(100.0,600.0,-220);
glEnd();

//garis bata depan

for (int i = 1; i < 7; i++)
{

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(100.0,300.0+(i*50),-219.5);
        glVertex3f(220.0,300.0+(i*50),-99.5);
        glEnd();
}

for (int i = 1; i < 7; i++)
    {


         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(100.0+(i*20),600.0,-219.5+(i*20));
        glVertex3f(100.0+(i*20),350.0,-219.5+(i*20));
        glEnd();
    }

    for (int i = 1; i < 20; i++)
    {


         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(501.0,0.0+(i*30),-0);
        glVertex3f(501.0,0.0+(i*30),-100);
        glEnd();
    }


    for (int i = 1; i < 40; i++)
    {


         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(501.0,0.0+(i*15),-0);
        glVertex3f(501.0,0.0+(i*15),-100);
        glEnd();
    }

    for (int i = 1; i < 80; i++)
    {



         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(501.0,0.0+(i*7.5),-0);
        glVertex3f(501.0,0.0+(i*7.5),-100);
        glEnd();
    }



//bata belakang kanan kiri warna
    glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	balok(500.0, 620.0, 0.0, 600.0, -80.0, -90.0);
	glEnd();
    glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	balok(90.0, 80.0, 0.0, 600.0, -500.0, -620.0);
	glEnd();

// Garis bata kanan
for (int i = 0; i < 7; i++)
{       glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(500.0+(i*20),0.0,-79.5);
        glVertex3f(500.0+(i*20),600.0,-79.5);
        glEnd();

}

for (int i = 1; i < 10; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(500.0,0.0+(i*60),-79.5);
        glVertex3f(620.0,0.0+(i*60),-79.5);
        glEnd();


    }

    for (int i = 1; i < 20; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(500.0,0.0+(i*30),-79.5);
        glVertex3f(620.0,0.0+(i*30),-79.5);
        glEnd();

    }


    for (int i = 1; i < 40; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(500.0,0.0+(i*15),-79.5);
        glVertex3f(620.0,0.0+(i*15),-79.5);
        glEnd();

    }

    for (int i = 1; i < 80; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(500.0,0.0+(i*7.5),-79.5);
        glVertex3f(620.0,0.0+(i*7.5),-79.5);
        glEnd();


    }

    // Garis bata kiri
for (int i = 0; i < 7; i++)
{       glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(79.5,0.0,-500-(i*20));
        glVertex3f(79.5,600.0,-500-(i*20));
        glEnd();

}

for (int i = 1; i < 10; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(79.5,0.0+(i*60),-500);
        glVertex3f(79.5,0.0+(i*60),-620);
        glEnd();


    }

    for (int i = 1; i < 20; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(79.5,0.0+(i*30),-500);
        glVertex3f(79.5,0.0+(i*30),-620);
        glEnd();

    }


    for (int i = 1; i < 40; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(79.5,0.0+(i*15),-500);
        glVertex3f(79.5,0.0+(i*15),-620);
        glEnd();

    }

    for (int i = 1; i < 80; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(79.5,0.0+(i*7.5),-500);
        glVertex3f(79.5,0.0+(i*7.5),-620);
        glEnd();


    }

//tembok belakang kiri bata warna
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	balok(110.0, 640.0, 20.0, 580.0, -670.0, -660.0);
	glEnd();

// Garis bata kiri
for (int i = 0; i < 27; i++)
{       glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(110.0+(i*20),20.0,-670.5);
        glVertex3f(110.0+(i*20),580.0,-670.5);
        glEnd();

}

for (int i = 1; i < 10; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(110.0,20.0+(i*60),-670.5);
        glVertex3f(640.0,20.0+(i*60),-670.5);
        glEnd();


    }

    for (int i = 1; i < 18; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(110.0,20.0+(i*30),-670.5);
        glVertex3f(640.0,20.0+(i*30),-670.5);
        glEnd();

    }


    for (int i = 1; i < 35; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(110.0,20.0+(i*15),-670.5);
        glVertex3f(640.0,20.0+(i*15),-670.5);
        glEnd();

    }

    for (int i = 1; i < 75; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(110.0,20.0+(i*7.5),-670.5);
        glVertex3f(640.0,20.0+(i*7.5),-670.5);
        glEnd();


    }


    //tembok belakang kanan bata warna
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.479, 0.3377);
	balok(670.0, 660.0, 20.0, 580.0, -110.0, -640.0);
	glEnd();

// Garis bata kanan
for (int i = 0; i < 27; i++)
{       glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(670.5,20.0,-110.0-(i*20));
        glVertex3f(670.5,580.0,-110.0-(i*20));
        glEnd();

}

for (int i = 1; i < 10; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(670.5,20.0+(i*60),-640.5);
        glVertex3f(670.5,20.0+(i*60),-110.5);
        glEnd();


    }

    for (int i = 1; i < 18; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(670.5,20.0+(i*30),-640.5);
        glVertex3f(670.5,20.0+(i*30),-110.5);
        glEnd();

    }


    for (int i = 1; i < 35; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(670.5,20.0+(i*15),-640.5);
        glVertex3f(670.5,20.0+(i*15),-110.5);
        glEnd();

    }

    for (int i = 1; i < 75; i++)
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(670.5,20.0+(i*7.5),-640.5);
        glVertex3f(670.5,20.0+(i*7.5),-110.5);
        glEnd();


    }

    //depan kaca
glBegin(GL_QUADS);
glColor4f(0.5,0.3, 0.3, 0.3);
glVertex3f(100.0,350.0,-220);
glVertex3f(220.0,350.0,-100);
glVertex3f(220.0,0.0,-100);
glVertex3f(100.0,0.0,-220);
glEnd();

//kaca atas
for (int i = 0; i < 6; i++){
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(104.5+(i*20),650.0,-214.5+(i*20));
glVertex3f(119.5+(i*20),650.0,-199.5+(i*20));
glVertex3f(119.5+(i*20),600.0,-199.5+(i*20));
glVertex3f(104.5+(i*20),600.0,-214.5+(i*20));
glEnd(); }
//depan kuning
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 0.0);
glVertex3f(100.0,680.0,-220);
glVertex3f(220.0,680.0,-100);
glVertex3f(220.0,600.0,-100);
glVertex3f(100.0,600.0,-220);
glEnd();

//garis bata kaca
for (int i = 1; i < 7; i++)
    {


         glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(100.0+(i*20),150.0,-219.5+(i*20));
        glVertex3f(100.0+(i*20),350.0,-219.5+(i*20));
        glEnd();
    }

for (int i = 0; i < 3; i++)
{

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(100.0,150.0+(i*100),-219.5);
        glVertex3f(220.0,150.0+(i*100),-99.5);
        glEnd();
}
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    ngon(100,70.0,70.0,-206.99,226.0,0.1);
    glEnd();

    //Lantai4 merah kanan kiri
    glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	balok(215.0, 205.0, 550.0, 600.0, -100.0, 0.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	balok(100.0, 0.0, 550.0, 600.0, -215.0, -205.0);
	glEnd();

	//base atap
    glBegin(GL_QUADS);
	glColor3f(0.9, 0.9, 0.9);
	balok(220.0, 680.0, 680.0, 690.0, -680.0, -70.0);
	glEnd();
    //base atap
    glBegin(GL_QUADS);
	glColor3f(0.9, 0.9, 0.9);
	balok(220.0, 70.0, 680.0, 690.0, -680.0, -220.0);
	glEnd();
    //base atap
    glBegin(GL_TRIANGLES);
    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(70.0,690.0,-220.0);
    glVertex3f(220.0,690.0,-70.0);
    glVertex3f(220.0,690.0,-220.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(70.0,680.0,-220.0);
    glVertex3f(220.0,680.0,-70.0);
    glVertex3f(220.0,680.0,-220.0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(70.0,680.0,-220.0);
    glVertex3f(220.0,680.0,-70.0);
    glVertex3f(220.0,690.0,-70.0);
    glVertex3f(70.0,690.0,-220.0);
    glEnd();

    // atap
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.693, 0.546);
    glVertex3f(650.0,690.0,-650.0);
    glVertex3f(660.0,690.0,-100.0);
    glVertex3f(375.0,890.0,-375.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.693, 0.546);
    glVertex3f(650.0,690.0,-650.0);
    glVertex3f(100.0,690.0,-650.0);
    glVertex3f(375.0,890.0,-375.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.693, 0.546);
    glVertex3f(230.0,690.0,-100.0);
    glVertex3f(660.0,690.0,-100.0);
    glVertex3f(375.0,890.0,-375.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.693, 0.546);
    glVertex3f(100.0,690.0,-230.0);
    glVertex3f(100.0,690.0,-650.0);
    glVertex3f(375.0,890.0,-375.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.693, 0.546);
    glVertex3f(100.0,690.0,-230.0);
    glVertex3f(230.0,690.0,-100.0);
    glVertex3f(375.0,890.0,-375.0);
    glEnd();

    //atap atas kiri
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	balok(100.0, 80.0, 680.0, 600.0, -660.0, -210.5);
	glEnd();

    //atap atas kiri
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	balok(99.9, 80.5, 680.0, 600.0, -220.0, -210.0);
	glEnd();

    //atap atas kanan
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	balok(210.5, 660.0, 680.0, 600.0, -100.0, -80.0);
	glEnd();
	//atap atas kanan
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	balok(210.0, 220.0, 680.0, 600.0, -99.9, -80.5);
	glEnd();

	//Base
	glBegin(GL_QUADS);
	glColor3f(0.9, 0.9, 0.9);
	balok(0.0, 100.0, 600.0, 600.5, -210.0, -500.0);
	balok(210.0, 500.0, 600.0, 600.5, 0.0, -100.0);
	glEnd();\
	//atap tiang hitam
	glBegin(GL_QUAD_STRIP);
	glColor4f(0.9, 0.9, 0.9,0.5);
	glVertex3f(-20.0, 100.0, -205.0);
	glVertex3f(-10.0, 100.0, -100.0);
	glVertex3f(0.0, 100.0, -205.0);
	glVertex3f(0.0, 100.0, -100.0);
	glVertex3f(40.0, 100.0, -200.0);
	glVertex3f(25.0, 100.0, -95.0);
	glVertex3f(80.0, 100.0, -185.0);
	glVertex3f(45.0, 100.0, -90.0);
	glVertex3f(125.0, 100.0, -155.0);
	glVertex3f(65.0, 100.0, -80.0);
	glVertex3f(155.0, 100.0, -125.0);
	glVertex3f(80.0, 100.0, -65.0);
	glVertex3f(185.0, 100.0, -80.0);
	glVertex3f(90.0, 100.0, -45.0);
	glVertex3f(200.0, 100.0, -40.0);
	glVertex3f(95.0, 100.0, -25.0);
	glVertex3f(205.0, 100.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(205.0, 100.0, 20.0);
	glVertex3f(100.0, 100.0, 10.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-20.0, 100.0, -205.0);
	glVertex3f(-10.0, 100.0, -100.0);
	glVertex3f(0.0, 100.0, -205.0);
	glVertex3f(0.0, 100.0, -100.0);
	glVertex3f(40.0, 100.0, -200.0);
	glVertex3f(25.0, 100.0, -95.0);
	glVertex3f(80.0, 100.0, -185.0);
	glVertex3f(45.0, 100.0, -90.0);
	glVertex3f(125.0, 100.0, -155.0);
	glVertex3f(65.0, 100.0, -80.0);
	glVertex3f(155.0, 100.0, -125.0);
	glVertex3f(80.0, 100.0, -65.0);
	glVertex3f(185.0, 100.0, -80.0);
	glVertex3f(90.0, 100.0, -45.0);
	glVertex3f(200.0, 100.0, -40.0);
	glVertex3f(95.0, 100.0, -25.0);
	glVertex3f(205.0, 100.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(205.0, 100.0, 20.0);
	glVertex3f(100.0, 100.0, 10.0);
	glEnd();


    //Logo UKSW
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId); //perhatikan teksture_Id berapa yg ingin anda panggil (menentukan foto mana yg akan kalian pakai untuk sisi ini)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(45.0,95.0,-207.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(95.0,95.0,-207.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(95.0,45.0,-207.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(45.0,45.0,-207.0);
    glEnd();

    //Gambar Dalam
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2); //perhatikan teksture_Id berapa yg ingin anda panggil (menentukan foto mana yg akan kalian pakai untuk sisi ini)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(305.0,147.2,-345);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(345.0,147.5,-305.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(345.0,112.5,-305.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(305.0,112.5,-345.0);
    glEnd();

    //Fakultas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3); //perhatikan teksture_Id berapa yg ingin anda panggil (menentukan foto mana yg akan kalian pakai untuk sisi ini)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 1.0f,1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(109.9,495.0,-210.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(210.0,495.0,-109.9);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(210.0,455.0,-109.9);
    glTexCoord2f(0.0f, 0.0f);
	glVertex3f(109.9,455.0,-210.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);

	glFlush();
	//cout << "X_GESER = " << x_geser << "	Y_GESER = " << y_geser << "	Z_GESER = " << z_geser << endl;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera();
	draw();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 16.0 / 9.0, 2, 10000);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
	glutPostRedisplay();
	glutWarpPointer(width / 2, height / 2);
	glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
	int dev_x, dev_y;
	dev_x = (width / 2) - x;
	dev_y = (height / 2) - y;
	yaw += (float)dev_x / 20.0;
	pitch += (float)dev_y / 20.0;
}

void camera() {
	if (motion.Forward) {
		camX += cos((yaw + 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
	}
	if (motion.Backward) {
		camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
	}
	if (motion.Left) {
		camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
	}
	if (motion.Right) {
		camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
	}
	if (motion.Naik) {
		terbang -= 2.0;
	}
	if (motion.Turun) {
		terbang += 2.0;
	}

	if (pitch >= 70)
		pitch = 70;
	if (pitch <= -90)
		pitch = -90;


	glRotatef(-pitch, 1.0, 0.0, 0.0);
	glRotatef(-yaw, 0.0, 1.0, 0.0);

	glTranslatef(-camX, -terbang, -350 - camZ);
	if (terbang < 25)
		terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'W':
	case 'w':
		motion.Forward = true;
		break;
	case 'A':
	case 'a':
		motion.Left = true;
		break;
	case 'S':
	case 's':
		motion.Backward = true;
		break;
	case 'D':
	case 'd':
		motion.Right = true;
		break;
	case 'E':
	case 'e':
		motion.Naik = true;
		break;
	case 'Q':
	case 'q':
		motion.Turun = true;
		break;
	case '6':
		x_geser += 0.5;
		break;
	case '4':
		x_geser -= 0.5;
		break;
	case '8':
		y_geser += 0.5;
		break;
	case '2':
		y_geser -= 0.5;
		break;
	case '9':
		z_geser -= 0.5;
		break;
	case '1':
		z_geser += 0.5;
		break;
	case '`': // KELUAR DARI PROGRAM
		exit(1);
	}
}

void keyboard_up(unsigned char key, int x, int y) {
	switch (key) {
	case 'W':
	case 'w':
		motion.Forward = false;
		break;
	case 'A':
	case 'a':
		motion.Left = false;
		break;
	case 'S':
	case 's':
		motion.Backward = false;
		break;
	case 'D':
	case 'd':
		motion.Right = false;
		break;
	case 'E':
	case 'e':
		motion.Naik = false;
		break;
	case 'Q':
	case 'q':
		motion.Turun = false;
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("TR GRAFKOM 672020019 672020027 672020032");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(passive_motion);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	glutMainLoop();
	return 0;
}
