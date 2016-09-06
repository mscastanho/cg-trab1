#include <GL/glut.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "tinyxml.h"

GLfloat gx=0,gy=0;
int keyStatus[256];

void mouse(int botao, int estado, int x, int y)
{
	printf("X: %.2f ; Y: %.2f \n",x/250.0,(250-y)/250.0);
}

void keyUp(unsigned char key, int x, int y)
{
	keyStatus[key] = 0;
}

void keyPress(unsigned char key, int x, int y)
{
	/*switch(key)
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
	*/

	keyStatus[key] = 1;
}

void display(void)
{
	/*limpar todos os pixels */
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* Desenhar um polígono branco (retângulo) */
	glColor3f(1.0,1.0,0);
	glBegin(GL_POLYGON);
		//glVertex3f(0.25+gx,0.25+gy,0.0);
		//glVertex3f(0.75+gx,0.25+gy,0.0);
		//glVertex3f(0.75+gx,0.75+gy,0.0);
		//glVertex3f(0.25+gx,0.75+gy,0.0);
		int i = 0;
			for(i = 0 ; i < 5 ; i++ ){
				glVertex3f(0.5*cos((90+i*72)*3.14/180.0)+gx,0.5*sin((90+i*72)*3.14/180.0)+gy,0.0);
				glVertex3f(0.3*cos((126+i*72)*3.14/180.0)+gx,0.3*sin((126+i*72)*3.14/180.0)+gy,0.0);
			}
		//glVertex3f(0.30901+gx,0.95105+gy,0.0);
		//glVertex3f(0.75+gx,0.25+gy,0.0);
		//glVertex3f(0.75+gx,0.75+gy,0.0);
		//glVertex3f(0.25+gx,0.75+gy,0.0);
	glEnd();

	/* Não esperar */
	//glFlush();
	glutSwapBuffers();
}

void idle (void)
{
	if( keyStatus['W'] == 1 || keyStatus['w'] == 1 )
		gy += 0.01;
	
	if( keyStatus['S'] == 1 || keyStatus['s'] == 1 )
		gy -= 0.01;
	
	if( keyStatus['D'] == 1 || keyStatus['d'] == 1 )
		gx += 0.01;
	
	if( keyStatus['A'] == 1 || keyStatus['a'] == 1 )
		gx -= 0.01;
		
	glutPostRedisplay();
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
	// zerar o vetor de status das teclas
	memset(keyStatus,256,sizeof(int));
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("hello");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);

	glutMainLoop();

	//TiXmlDocument doc("config.xml");
	/* C ANSI requer que main retorne um inteiro */
	return 0;
}

