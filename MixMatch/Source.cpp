#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

int flag = 0;
float window_width = 800.0f;
float window_height = 800.0f;
int formerX = -1; //initial point coordinates
int formerY = -1;
int cSwitch = 1;

using namespace std;

float normX(float x) {
	return ((float)x) / window_width * 2.0f - 1.0f;
}
float normY(float y) {
	return 1.0f - ((float)y) / window_height * 2.0f;
}

float getRadius(int initX, int initY, int x, int y) {
	return
		sqrt((y - initY) * (y - initY) + (x - initX) * (x - initX));
}


void drawPoint(int x, int y) {

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f((x - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0),
		-(y - glutGet(GLUT_WINDOW_HEIGHT) / 2.0) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0));
	glEnd();
	glFlush();
}

//Drawing a Line using bresenhams's Algorithm

void drawLine(int x0, int y0, int x1, int y1) {

	if (x0 == x1) {
		if (y0 < y1) {
			while (y0 < y1) {
				drawPoint(x0, y0 + 1);
				y0 = y0 + 1;
			}
		}
		else if (y1 < y0) {
			while (y1 < y0) {
				drawPoint(x0, y1 + 1);
				y1 = y1 + 1;
			}
		}
	}

	else {
		glPointSize(5);
		glBegin(GL_POINTS);

		float deltax = x1 - x0;
		float deltay = y1 - y0;
		float error = 0.0f;
		float deltaerr = abs(deltay / deltax);
		int y = y0;

		bool checkifIncrease = (x1 >= x0) ? true : false;
		for (int x = x0; (checkifIncrease) ? (x < x1) : (x > x1); (checkifIncrease) ? (x++) : (x--)) {
			glVertex2f((x - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0),
				-(y - glutGet(GLUT_WINDOW_HEIGHT) / 2.0) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0));

			error = error + deltaerr;
			while (error >= 0.5) {
				glVertex2f((x - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0),
					-(y - glutGet(GLUT_WINDOW_HEIGHT) / 2.0) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0));
				y = y + (y1 - y0) / abs(y1 - y0);

				error = error - 1.0f;
			}
		}
		glEnd();
		glFlush();
	}




}

//Drawing a Rectangle given two corners
void drawRectangle(int x1, int y1, int x0, int y0) {


	drawLine(x0, y0, x1, y0);
	drawLine(x0, y0, x0, y1);
	drawLine(x1, y0, x1, y1);
	drawLine(x0, y1, x1, y1);

	if (y0 < y1) {
		while (y0 < y1) {

			drawPoint(x0, y0);
			drawPoint(x1, y0);
			y0 = y0 + 1;
		}
	}

	else if (y1 < y0) {
		while (y1 < y0) {

			drawPoint(x0, y1);
			drawPoint(x1, y1);
			y1 = y1 + 1;
		}
	}
}
//Drawing circle using Mid-point Algorithm
void drawCircle(int cX, int cY) {
	glPointSize(5);
	glBegin(GL_POINTS);

	int radius = getRadius(formerX, formerY, cX, cY);
	int x0 = formerX;
	int y0 = formerY;
	int x = radius;
	int y = 0;
	int p0 = 1 - x;

	while (y <= x) {
		glVertex2f(normX((float)x + x0), normY((float)(y + y0)));
		glVertex2f(normX((float)y + x0), normY((float)(x + y0)));
		glVertex2f(normX((float)-x + x0), normY((float)(y + y0)));
		glVertex2f(normX((float)-y + x0), normY((float)(x + y0)));
		glVertex2f(normX((float)-x + x0), normY((float)(-y + y0)));
		glVertex2f(normX((float)-y + x0), normY((float)(-x + y0)));
		glVertex2f(normX((float)x + x0), normY((float)(-y + y0)));
		glVertex2f(normX((float)y + x0), normY((float)(-x + y0)));
		y++;
		if (p0 <= 0)
			p0 += 2 * y + 1;
		else {
			x--;
			p0 += 2 * (y - x) + 1;
		}
	}
	glEnd();
	glFlush();

	formerX = -1;
	formerY = -1;
}

#define pi 3.142857
int edge = 5;

void draw_polygon(int x1, int y1, int x2, int y2)
{
	float x, y, m, n;
	x = x1;
	y = y1;
	float a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	float interior = (pi * (edge - 2) / edge);
	float k = pi - interior;

	for (int j = 0; j < edge; j++)
	{
		m = x;
		n = y;
		drawLine(m, n, m + a * cos(k * j), n + a * sin(k * j));
		x = m + a * cos(k * j);
		y = n + a * sin(k * j);
	}
}


void display(void)
{
	glFlush();
}

void clearScreen() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (int x = 0; x < window_width; x++) {
		for (int y = 0; y < window_height; y++) {
			glVertex2f(normX((float)x), normY((float)y));
		}
	}
	glEnd();
	glFlush();
}


int brushSize = 2;
void drawBrush(int x, int y)
{
	for (int i = 0; i < brushSize; i++)
	{
		int randX = rand() % (brushSize + 1) - brushSize / 2 + x;
		int randY = rand() % (brushSize + 1) - brushSize / 2 + y;
		drawPoint(randX, randY);
	}

}

int eraserSize = 1;
void erase(int x, int y)
{

	for (int i = -eraserSize; i <= eraserSize; i++)
	{
		for (int j = -eraserSize; j <= eraserSize; j++)
		{
			drawPoint(x + i, y + j);
		}
	}
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
	case 'q':
		exit(0);
		break;

	case 'b':
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case 'g':
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case 'r':
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case 'c':
		clearScreen();

	default:
		break;
	}
}


bool z = true;

void mouse(int btn, int state, int x, int y) {
	switch (btn) {

	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {

			switch (cSwitch) {

			case 5:
				drawPoint(x, y);
				break;
			case 6:
				if (z == true) {

					formerX = x;
					formerY = y;

					z = false;
				}
				else {
					drawLine(x, y, formerX, formerY);
					z = true;
				}
				break;
			case 7:
				if (z == true) {

					formerX = x;
					formerY = y;


					z = false;
				}
				else {
					drawRectangle(x, y, formerX, formerY);
					z = true;
				}
				break;
			case 8:
				if (formerX == -1 && formerY == -1) {
					formerX = x;
					formerY = y;
					break;
				}
				drawCircle(x, y);
				break;
			case 9:
				if (formerX == -1 && formerY == -1) {
					formerX = x;
					formerY = y;
					break;
				}
				draw_polygon(x, y, formerX, formerY);
				break;

			case 11:
				erase(x, y);
				break;
			case 17:
				if (formerX == -1 && formerY == -1) {
					formerX = x;
					formerY = y;
					break;
				}
				drawBrush(x, y);
				break;

			case 1:
				break;


			}
		}

		break;

	}



}

void motion(int x, int y) {
	drawPoint(x, y);
}

void randColour(int value) {
	switch (value) {
	case 0:
		glColor3f(0.0f, 0.5f, 1.0f);//baby Blue 
		break;

	case 1:
		glColor3f(1.0f, 0.5f, 0.0f);//Orange
		break;

	case 2:
		glColor3f(1.0f, 0.0f, 1.0f); //pink
		break;

	case 3:
		glColor3f(1.0f, 1.0f, 0.1f); //Yellow
		break;
	case 4:
		glColor3f(0.0f, 1.0f, 1.0f); //cyan
		break;
	}

}


void menu(int value) {
	switch (value) {
	case 0:
		glColor3f(1.0f, 0.0f, 0.0f); //Red
		break;

	case 1:
		glColor3f(0.0f, 1.0f, 0.0f); //Green
		break;

	case 2:
		glColor3f(0.0f, 0.0f, 1.0f); //Blue
		break;

	case 3:
		glColor3f(1.0f, 1.0f, 1.0f); //white
		break;

	case 5:
		cSwitch = 5;//Point
		break;
	case 6:
		cSwitch = 6;//line
		break;

	case 7:
		cSwitch = 7;//Rectangle
		break;

	case 8:
		cSwitch = 8;//Circle
		break;
	case 9:
		cSwitch = 9; //polygon
		break;
	case 11:
		glColor3f(0.0, 0.0, 0.0);
		eraserSize = 4;
		cSwitch = 11;
		break;
	case 12:
		glColor3f(0.0, 0.0, 0.0);
		eraserSize = 15;
		cSwitch = 11;
		break;
	case 13:
		glColor3f(0.0, 0.0, 0.0);
		eraserSize = 25;
		cSwitch = 11;
		break;
	case 14:
		clearScreen();
		break;
	case 15:
		exit(0);
		break;
	case 16:
		randColour(rand() % 5);
		break;
	case 17:
		cSwitch = 17;
		break;
	case 18:
		brushSize = 8;
		cSwitch = 17;
		break;
	case 19:
		brushSize = 16;
		cSwitch = 17;
		break;
	case 20:
		brushSize = 24;
		cSwitch = 17;
		break;
	case 21:
		edge = 6;
		cSwitch = 9; //hexagon
		break;
	}
}

void glutCallbacks() {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
}

void initMenu() {

	int submenu1, submenu2, submenu3, submenu4;

	submenu1 = glutCreateMenu(menu); //color menu
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);
	glutAddMenuEntry("White", 3);
	glutAddMenuEntry("Random Colour", 16);


	submenu2 = glutCreateMenu(menu); //shape menu
	glutAddMenuEntry("Point", 5);
	glutAddMenuEntry("Line", 6);
	glutAddMenuEntry("Rectangle", 7);
	glutAddMenuEntry("Circle", 8);
	glutAddMenuEntry("Pentagon", 9);
	glutAddMenuEntry("Hexagon", 21);

	submenu3 = glutCreateMenu(menu); //Eraser size
	glutAddMenuEntry("Small", 11);
	glutAddMenuEntry("Medium", 12);
	glutAddMenuEntry("Large", 13);

	submenu4 = glutCreateMenu(menu); // Brush size
	glutAddMenuEntry("2x", 17);
	glutAddMenuEntry("8x", 18);
	glutAddMenuEntry("16x", 19);
	glutAddMenuEntry("24x", 20);

	glutCreateMenu(menu); //main menu
	glutAddSubMenu("Colours", submenu1);
	glutAddSubMenu("Shapes", submenu2);
	glutAddSubMenu("Eraser", submenu3);
	glutAddSubMenu("AirBrush", submenu4);

	glutAddMenuEntry("ClearScreen", 14);
	glutAddMenuEntry("Exit", 15);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(500,20);
	glutCreateWindow("MixMatch");
	cout << "Guide to MixMatch" << endl;
	cout << "Right Click to Browse Menu!" << endl;
	cout << "Select color from color menu or use 'r', 'g', 'b' keys for red, blue and green." << endl;
	cout << "Line: First and Second click specify the 2 end pts of line." << endl;
	cout << "Circle: First click: Centre, second click: pt on circle." << endl;
	cout << "Rectangle: First and second click specify the endpoints of diagonal." << endl;
	cout << "Polygon: Two clicks specify the edge length." << endl;
	cout << "Press 'c' to clear the screen." << endl;
	cout << "Press 'q' to quit." << endl;
	clearScreen();
	glutCallbacks();
	initMenu();
	glutMainLoop();
	return(0);
}