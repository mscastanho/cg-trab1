#include <GL/glut.h>
#include <stdio.h>
#include "tinyxml.h"

GLfloat gx=0,gy=0;

void keyPress(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w':
		case 'W':
			gy += 0.01;
			break;
		case 's':
		case 'S':
			gy -= 0.01;
			break;
		case 'd':
		case 'D':
			gx += 0.01;
			break;
		case 'a':
		case 'A':
			gx -= 0.01;
			break; 
	}

	glutPostRedisplay();
}

void display(void)
{
	/*limpar todos os pixels */
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* Desenhar um polígono branco (retângulo) */
	glColor3f(0.2,0.6,1.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.25+gx,0.25+gy,0.0);
		glVertex3f(0.75+gx,0.25+gy,0.0);
		glVertex3f(0.75+gx,0.75+gy,0.0);
		glVertex3f(0.25+gx,0.75+gy,0.0);
	glEnd();

	/* Não esperar */
	glFlush();
}

void init (void)
{
	/*selecionar cor de fundo (preto) */
	glClearColor(0.0,0.0,0.0,0.0);

	/* inicializar sistema de voz */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}

int main (int argc, char** argv)
{
	/*glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("hello");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);

	glutMainLoop();
	*/

	TiXmlDocument doc("config.xml");
	/* C ANSI requer que main retorne um inteiro */
	return 0;
}
