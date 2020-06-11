// Opracowane przez: Jakub Spa³ek, Aleksandra Pyrkosz
// Realizacja zadania 1 laboratorium 5

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

GLfloat jumpPoint = 0.5f;
GLfloat alfa = 0.0;
GLfloat eyeX = 0.0;
GLfloat eyeY = 0.0;
GLfloat eyeZ = 20.0;
GLfloat pointX = jumpPoint * cos(-3.14 / 2);
GLfloat pointY = 0.0;
GLfloat pointZ = jumpPoint * sin(-3.14 / 2);

GLfloat lightPosition[] = { 100.0f, 100.0f, 50.0f, 1.0f };
GLfloat dimLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat strongLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat ambientMaterials[] = { 0.329412, 0.223529, 0.027451, 1.0 };
GLfloat diffuseMaterials[] = { 0.780392, 0.568627, 0.113725, 1.0 };
GLfloat specularMaterials[] = { 0.992157, 0.941176, 0.807843, 1.0 };
GLfloat shininessMaterials = 27.8974;

GLfloat lightRotateX = 0.0;
GLfloat lightRotateY = 0.0;

void Display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	if (alfa < 1.0)
	{
		glEnable(GL_LIGHT0);
	}

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	// materia³y
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterials);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterials);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterials);
	glMateriali(GL_FRONT, GL_SHININESS, shininessMaterials);

	glPushMatrix();

		glLoadIdentity();
		glRotatef(lightRotateX, 1.0, 0, 0);
		glRotatef(lightRotateY, 0, 1.0, 0);

		// œwiat³o ogólne
		glLightfv(GL_LIGHT0, GL_AMBIENT, dimLight); 
		glLightfv(GL_LIGHT0, GL_DIFFUSE, strongLight); 
		glLightfv(GL_LIGHT0, GL_SPECULAR, strongLight); 
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); 

	glPopMatrix();

	alfa += 0.5f;

	glPushMatrix();

		// kamera
		gluLookAt(eyeX, eyeY, eyeZ, pointX, pointY, pointZ, 0.0, 1.0, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// cube
		glColor3f(1.0, 0.6, 0.0);
		glRotatef(alfa, 0, alfa / 9, 1);
		glutSolidCube(3.0f);

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width < height && width > 0)
		glFrustum(-1.0, 1.0, -1.0 * height / width, 1.0 * height / width, 2.0, 100.0);
	else
		if (width >= height && height > 0)
			glFrustum(-1.0 * width / height, 1.0 * width / height, -1.0, 1.0, 2.0, 100.0);

	Display();
}

void Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case('+'):
		eyeZ = eyeZ - 1.0;
		break;
	case('-'):
		eyeZ = eyeZ + 1.0;
		break;
	case('w'):
		lightRotateX -= 5;
		break;
	case('s'):
		lightRotateX += 5;
		break;
	case('a'):
		lightRotateY -= 5;
		break;
	case('d'):
		lightRotateY += 5;
		break;
	case('1'):
		glEnable(GL_LIGHT0);
		break;
	case('2'):
		glDisable(GL_LIGHT0);
		break;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		eyeX = eyeX - 1.0f;
		break;
	case GLUT_KEY_RIGHT:
		eyeX = eyeX + 1.0f;
		break;
	case GLUT_KEY_UP:
		eyeY = eyeY + 1.0f;
		break;
	case GLUT_KEY_DOWN:
		eyeY = eyeY - 1.0f;
		break;
	}
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(3, TimerFunction, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Oswietlenie lokalne - Jakub Spalek, Aleksandra Pyrkosz");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKeys);

	glutTimerFunc(33, TimerFunction, 1);

	cout << "Ruch kamery: klawisze strzalek\n";
	cout << "Zoom: [+]/[-]\n";
	cout << "Ruch zrodla swiatla: [w][a][s][d]\n";
	cout << "Przelacz swiatlo ogolne: [1]/[2]\n";

	glutMainLoop();

	return 0;
}
