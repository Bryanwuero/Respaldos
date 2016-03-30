#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
//Bryan Arroyo Carrillo 
/*
:) CONTROLS
+zoom  = flecha arriba
-zoom = flecha abajo
*/

using namespace std;

// Global variables for window's size
int width = 800;
int height = 600;
// Global variables for moving camera
int mouseButton = 0;
bool mouseRotate = false;
bool mouseZoom = false;
bool mousePan = false;
int xClick = 0;
int yClick = 0;
int xAux = 0;
int yAux = 0;
double rotX = 0.;
double rotY = 0.;
double panX = 0.;
double panY = 0.;
double zoom = -10.;
double r=1.0;
double g=1.0;
double b=1.0;
int valor, tipo, color;
float stack = 20;
float slice = 20;

//struct de figuras creadas
struct Figure{
	int fig;
	int color;
	int type;
	double scale;
	double rotX;
	double rotY;
	double rotZ;
	double transX;
	double transY;
	double transZ;
}arr_fig[22];

int cont = 0;
int seleccion = 0;
int tmp;



void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0., zoom); // Camera inicialization
}

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (height == 0)
	{
		height = 1;
	}
	gluPerspective(25.0, (double)width / height, 0.1, 1000.0);	//proyección en perspectiva
	glMatrixMode(GL_MODELVIEW);
}

void drawAxis(double length)
{
	glColor3f(1., 0., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(length, 0., 0.);
	glEnd();
	glColor3f(0., 1., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., length, 0.);
	glEnd();
	glColor3f(0., 0., 1.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0., length);
	glEnd();
	glColor3f(1., 1., 1.);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Moving camera
	glPushMatrix();
	glTranslatef(panX, panY, zoom);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);
	// Scene Model
	drawAxis(2.);       // Drawing global coordinate system


	//FIGUAS Y TIPOS
	// for para recorrer cada figura
	for (int i = 0; i < cont; i++){

		//COLORES (rgb)
		if (arr_fig[i].color == 25){
			glColor3f(1., 1., 1.);
		}
		if (arr_fig[i].color == 26){
			glColor3f(1., 0., 0.);
		}
		if (arr_fig[i].color == 27){
			glColor3f(0., 1., 0.);
		}
		if (arr_fig[i].color == 28){
			glColor3f(0., 0., 1.);
		}
		if (arr_fig[i].color == 29){
			glColor3f(1., 1., 0.);
		}
		if (arr_fig[i].color == 30){
			glColor3f(1., 0., 1.);
		}
		if (arr_fig[i].color == 31){
			glColor3f(0., 1., 1.);
		}

		if (arr_fig[i].fig == 1 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireSphere(1., slice, stack);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 1 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(arr_fig[i].rotX, 1, 0, 0);
			glRotatef(arr_fig[i].rotY, 0, 1, 0);
			glRotatef(arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidSphere(1., slice, stack);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 2 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireCone(1., 10, slice, stack);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 2 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidCone(1., 10, slice, stack);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 3 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireCube(10);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 3 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidCube(10);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 4 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireTorus(4, 4, slice, stack);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 4 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidTorus(4, 4, slice, stack);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 5 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireTetrahedron();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 5 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidTetrahedron();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 6 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireOctahedron();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 6 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidOctahedron();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 7 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireDodecahedron();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 7 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidDodecahedron();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 8 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireIcosahedron();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 8 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidIcosahedron();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 9 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutWireTeapot(3.0);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 9 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glutSolidTeapot(3.0);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 10 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);
			glutWireCylinder(2.0, 5.0, slice, stack);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 10 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);
			glutSolidCylinder(2.0, 5.0, slice, stack);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 11 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			GLUquadricObj *quadratic;
			quadratic = gluNewQuadric();
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
			gluDisk(quadratic, 0.5f, 1.5f, slice, stack);
			glPopMatrix();

		}
		else if (arr_fig[i].fig == 11 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			GLUquadricObj *quadratic;
			quadratic = gluNewQuadric();
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			gluDisk(quadratic, 0.5f, 1.5f, slice, stack);
			glPopMatrix();
		}
		//LINEAS Y SEGMENTOS 
		else if (arr_fig[i].fig == 12){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 13){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(-5.0, 0.0, 0.0);
			glVertex3f(5.0, 0.0, 0.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 14 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINE_STRIP);
			glVertex3f(-5.0, 5.0, 3.0);
			glVertex3f(5.0, 5.0, 3.0);
			glVertex3f(-5.0, -5.0, 3.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 14 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_TRIANGLES);
			glVertex3f(-5.0, 5.0, 3.0);
			glVertex3f(5.0, 5.0, 3.0);
			glVertex3f(-5.0, -5.0, 3.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 15 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINE_LOOP);
			glVertex3f(-5.0, 5.0, 3.0);
			glVertex3f(5.0, 5.0, 3.0);
			glVertex3f(-5.0, -5.0, 3.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 15 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_TRIANGLES);
			glVertex3f(-5.0, 5.0, 3.0);
			glVertex3f(5.0, 5.0, 3.0);
			glVertex3f(-5.0, -5.0, 3.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 16 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(-1., 0., 0.);
			glVertex3f(1., 0., 0.);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(-1., 0., 0.);
			glVertex3f(0.0, 2.0, 0.);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(1., 0., 0.);
			glVertex3f(0., 2.0, 0.);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 16 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_TRIANGLES);
			glVertex3f(2., 0.0, 0.0);
			glVertex3f(0.0, 2., 0.0);
			glVertex3f(0.0, 0.0, 2.);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 17 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(0., 1., 0.);
			glVertex3f(1.0, 0.0, 0.);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(1., 0., 0.);
			glVertex3f(2., 1., 0.);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(2., 1., 0.);
			glVertex3f(3., 0.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(3., 0., 0.);
			glVertex3f(4., 1.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(4., 1.0, 0.);
			glVertex3f(5., 0.0, 0.0);
			glEnd();

			//union de puntos 
			glBegin(GL_LINES);
			glVertex3f(0., 1.0, 0.);
			glVertex3f(2., 1.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(2., 1.0, 0.);
			glVertex3f(4., 1.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(1., 0.0, 0.);
			glVertex3f(3., 0.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(3., 0.0, 0.);
			glVertex3f(5., 0.0, 0.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 17 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(0., 1.0, 0.);
			glVertex3f(1., 0.0, 0.0);
			glVertex3f(2., 1.0, 0.0);
			glVertex3f(3., 0.0, 0.0);
			glVertex3f(4., 1.0, 0.0);
			glVertex3f(5., 0.0, 0.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 18 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glVertex3f(2.0, 1.0, 0.);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glVertex3f(1., 2., 0.);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glVertex3f(0., 3.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glVertex3f(-1., 2.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0., 0.0, 0.);
			glVertex3f(-2., 1.0, 0.0);
			glEnd();

			//union de puntos 
			glBegin(GL_LINES);
			glVertex3f(2., 1.0, 0.);
			glVertex3f(1., 2.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(1., 2.0, 0.);
			glVertex3f(0., 3.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0., 3.0, 0.);
			glVertex3f(-1., 2.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(-1., 2.0, 0.);
			glVertex3f(-2., 1.0, 0.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 18 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0., 0.0, 0.);
			glVertex3f(2., 1.0, 0.0);
			glVertex3f(1., 2.0, 0.0);
			glVertex3f(0., 3.0, 0.0);
			glVertex3f(-1., 2.0, 0.0);
			glVertex3f(-2., 1.0, 0.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 19 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glVertex3f(1.0, 1.0, 0.);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(1., 1., 0.);
			glVertex3f(3., 1., 0.);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(3., 1., 0.);
			glVertex3f(2., 0.0, 0.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(2., 0., 0.);
			glVertex3f(0.0, 0.0, 0.0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 19 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_QUADS);
			glVertex3f(0., 0.0, 0.);
			glVertex3f(1., 1.0, 0.);
			glVertex3f(3., 1.0, 0.);
			glVertex3f(2., 0.0, 0.);
			glVertex3f(0., 0.0, 0.);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 20 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 1, 0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0, 1, 0);
			glVertex3f(.5, .5, 0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(1, 1, 0);
			glVertex3f(.5, .5, 0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 20 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_QUAD_STRIP);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(0, 1, 0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 21 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(0, 3, 0);
			glVertex3f(3, 0, 0);

			glBegin(GL_LINES);
			glVertex3f(3, 0, 0);
			glVertex3f(1.5, -3, 0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(1.5, -3, 0);
			glVertex3f(-1.5, -3, 0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(-1.5, -3, 0);
			glVertex3f(-3, 0, 0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(-3, 0, 0);
			glVertex3f(0, 3, 0);
			glEnd();
			glPopMatrix();
		}
		else if (arr_fig[i].fig == 21 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_POLYGON);
			glVertex3f(0, 3, 0);
			glVertex3f(3, 0, 0);
			glVertex3f(1, -3, 0);
			glVertex3f(-1, -3, 0);
			glVertex3f(-3, 0, 0);
			glEnd();
			glPopMatrix();
		}
		//PIRAMIDES
		else if (arr_fig[i].fig == 22 && tipo == 0){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_LINES);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 3.0f);
			glVertex3f(1.0f, -1.0f, 3.0f);

			// Right
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 3.0f);
			glVertex3f(1.0f, -1.0f, -3.0f);

			// Back
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -3.0f);
			glVertex3f(-1.0f, -1.0f, -3.0f);

			// Left
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -3.0f);
			glVertex3f(-1.0f, -1.0f, 3.0f);
			//Lado 1
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 3.0f);
			glVertex3f(-1.0f, -1.0f, 3.0f);
			//Lado1
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -3.0f);
			glVertex3f(1.0f, -1.0f, -3.0f);
			//Lado2
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -3.0f);
			glVertex3f(-1.0f, -1.0f, -3.0f);
			//lado2
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 3.0f);
			glVertex3f(1.0f, -1.0f, 3.0f);
			glEnd();
			glPopMatrix();
		}

		else if (arr_fig[i].fig == 22 && tipo == 1){
			glPushMatrix();
			glScalef(.20 + arr_fig[i].scale, .20 + arr_fig[i].scale, .20 + arr_fig[i].scale);
			glRotatef(5 + arr_fig[i].rotX, 1, 0, 0);
			glRotatef(5 + arr_fig[i].rotY, 0, 1, 0);
			glRotatef(5 + arr_fig[i].rotZ, 0, 0, 1);

			glTranslatef(arr_fig[i].transX, 0, 0);
			glTranslatef(0, arr_fig[i].transY, 0);
			glTranslatef(0, 0, arr_fig[i].transZ);
			glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 3.0f);
			glVertex3f(1.0f, -1.0f, 3.0f);

			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 3.0f);
			glVertex3f(1.0f, -1.0f, -3.0f);

			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -3.0f);
			glVertex3f(-1.0f, -1.0f, -3.0f);

			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -3.0f);
			glVertex3f(-1.0f, -1.0f, 3.0f);
			glEnd();
			glPopMatrix();
		}
	}

	glPopMatrix();
	glutSwapBuffers(); // Swap buffers
}

void idle()
{
	glutPostRedisplay();    // call display
}

void mouse(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseRotate = false;
	//mouseZoom = false;
	mousePan = false;
	xClick = x;
	yClick = y;
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseRotate = true;
		xAux = rotX;
		yAux = rotY;
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		mousePan = true;
		xAux = panX;
		yAux = panY;
	}
}

void mouseMotion(int x, int y)
{
	if (mouseRotate == true)
	{
		if (mouseButton == GLUT_LEFT_BUTTON)
		{
			if ((x - xClick + xAux) > 360.0)
			{
				xAux = xAux - 360.0;
			}
			if ((x - xClick + xAux) < 0.0)
			{
				xAux = xAux + 360.0;
			}
			if ((y - yClick + yAux) > 360.0)
			{
				yAux = yAux - 360.0;
			}
			if ((y - yClick + yAux) < 0.0)
			{
				yAux = yAux + 360.0;
			}
			rotX = x - xClick + xAux;
			rotY = y - yClick + yAux;
		}
	}
	else if (mousePan == true)
	{
		if (mouseButton == GLUT_MIDDLE_BUTTON)
		{
			panX = ((x - xClick) / 63.0) + xAux;
			panY = ((y - yClick) / (-63.0)) + yAux;
		}
	}
}

void keyboard(unsigned char k, int x, int y){
	// Rotacion
	if (k == 'a'){
		arr_fig[seleccion].rotX   += 3;
	}
	if (k == 'z'){
		arr_fig[seleccion].rotX   -= 3;
	}
	if (k == 's'){
		arr_fig[seleccion].rotY   += 3;
	}
	if (k == 'x'){
		arr_fig[seleccion].rotY   -= 3;
	}
	if (k == 'd'){
		arr_fig[seleccion].rotZ  += 3;
	}
	if (k == 'c'){
		arr_fig[seleccion].rotZ  -= 3;
	}

	//Translacion
	if (k == 'g'){
		arr_fig[seleccion].transX  += 3;
	}
	if (k == 'b'){
		arr_fig[seleccion].transX  -= 3;
	}
	if (k == 'h'){
		arr_fig[seleccion].transY  += 3;
	}
	if (k == 'n'){
		arr_fig[seleccion].transY  -= 3;
	}
	if (k == 'j'){
		arr_fig[seleccion].transZ  += 3;
	}
	if (k == 'm'){
		arr_fig[seleccion].transZ  -= 3;
	}

}

void specialkeyboard(int key, int x, int y){
	cout << "Key = " << key << "x = " << x << "y = " << y << endl;
	if (key == 101){
		zoom = zoom + .5;
	}
	else if (key == 103){
		zoom = zoom - .5;
	}
	else if (key == 100){//Flecha izq para escalar -
		arr_fig[seleccion].scale = arr_fig[seleccion].scale - .3;
	}
	else if (key == 102){// Flecha der para escalar +
		arr_fig[seleccion].scale = arr_fig[seleccion].scale + .3;
	}
	else if (key == 114){
		slice = slice - 2;
	}
	else if (key == 112){
		slice = slice + 2;
	}
	else if (key == 107){// Tecla 1 para cambiar de figura
		if (cont > 0){
			arr_fig[seleccion].color = 25;
			seleccion = (++seleccion) % cont;
			cout << "figura seleccionada " << seleccion << endl;
			arr_fig[seleccion].color = 31;
		}
	}
	glutPostRedisplay();
}

// funcion para mandar llamar las figuras de struct
void pintarFigura(int valor){
	Figure paint = {valor, 25, .20, 0., 0., 0., 0., 0., 0.};
	arr_fig[cont] = paint;
	cont++;

}

void menu(int value){
	//FIGURAS 
	if (value == 1){
		valor = 1;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 2){
		valor = 2;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 3){
		valor = 3;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 4){
		valor = 4;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 5){
		valor = 5;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 6){
		valor = 6;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 7){
		valor = 7;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 8){
		valor = 8;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 9){
		valor = 9;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 10){
		valor = 10;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 11){
		valor = 11;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 12){
		valor = 12;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 13){
		valor = 13;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 14){
		valor = 14;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 15){
		valor = 15;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 16){
		valor = 16;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 17){
		valor = 17;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 18){
		valor = 18;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 19){
		valor = 19;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 20){
		valor = 20;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 21){
		valor = 21;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	else if (value == 22){
		valor = 22;
		glutDisplayFunc(display);
		pintarFigura(value);
	}
	//TIPOS (wire, solid)
	else if (value == 23){
		tipo = 0;
	}
	else if (value == 24){
		tipo = 1;
	}
	//COLORES (rgb)
	else if (value == 25){
		arr_fig[seleccion].color = value;
		cout << "color value" << arr_fig[seleccion].color << endl;
	}
	else if (value == 26){
		arr_fig[seleccion].color = value;
		cout << "color value" << arr_fig[seleccion].color << endl;
	}
	else if (value == 27){
		arr_fig[seleccion].color = value;
	}
	else if (value == 28){
		arr_fig[seleccion].color = value;
	}
	else if (value == 29){
		arr_fig[seleccion].color = value;
	}
	else if (value == 30){
		arr_fig[seleccion].color = value;
	}
	else if (value == 31){
		arr_fig[seleccion].color = value;
	}

}

int main(int argc, char** argv)
{
	// Init Window (GLUT)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Paint GLUT");

	// Callback functions registration (GLUT)
	glutDisplayFunc(display);		// display scene function
	glutReshapeFunc(reshape);		// reshape window function
	glutIdleFunc(idle);				// idle function
	glutMouseFunc(mouse);			// processing mouse events function
	glutMotionFunc(mouseMotion);	// processing mouse motion function
	glutSpecialFunc(specialkeyboard); // function of the arrows
	glutKeyboardFunc(keyboard);     // funcion of the keyboard 


	int subMenuA = glutCreateMenu(menu);
	glutAddMenuEntry("Esfera", 1);
	glutAddMenuEntry("Cono", 2);
	glutAddMenuEntry("Cubo", 3);
	glutAddMenuEntry("Toroide", 4);
	glutAddMenuEntry("Tetrahedro", 5);
	glutAddMenuEntry("Octahedro", 6);
	glutAddMenuEntry("Dodecahedro", 7);
	glutAddMenuEntry("Icosahedro", 8);
	glutAddMenuEntry("Tetera", 9);
	glutAddMenuEntry("Cilindro", 10);
	glutAddMenuEntry("Disco", 11);

	int subMenuB = glutCreateMenu(menu);
	glutAddMenuEntry("Punto", 12);
	glutAddMenuEntry("Segmento", 13);
	glutAddMenuEntry("Line Strip", 14);
	glutAddMenuEntry("Line loop", 15);
	glutAddMenuEntry("Triangulo", 16);
	glutAddMenuEntry("Triangulo Strip", 17);
	glutAddMenuEntry("Triangulo Fan", 18);
	glutAddMenuEntry("Quad", 19);
	glutAddMenuEntry("Quad strip", 20);
	glutAddMenuEntry("Poligono", 21);

	int subMenuC = glutCreateMenu(menu);
	glutAddMenuEntry("Piramide Base Rectangular", 22);

	int subMenuD = glutCreateMenu(menu);
	glutAddMenuEntry("wired", 23);
	glutAddMenuEntry("solid", 24);

	int subMenuE = glutCreateMenu(menu);
	glutAddMenuEntry("blanco", 25);
	glutAddMenuEntry("rojo", 26);
	glutAddMenuEntry("verde", 27);
	glutAddMenuEntry("azul", 28);
	glutAddMenuEntry("amarillo", 29);
	glutAddMenuEntry("rosa", 30);
	glutAddMenuEntry("aqua", 31);

	int ppalMenu = glutCreateMenu(menu);
	glutAddSubMenu("Figuras", subMenuA);
	glutAddSubMenu("Lieas", subMenuB);
	glutAddSubMenu("Piramides", subMenuC);
	glutAddSubMenu("Tipo", subMenuD);
	glutAddSubMenu("Color", subMenuE);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	init();							// init OpenGL context


	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutMainLoop();					// Main loop waiting for events!
	return 0;
}
