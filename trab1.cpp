#include <GL/glut.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

GLfloat gx=0,gy=0;
int keyStatus[256];

// Parametros da janela
int larguraJanela, alturaJanela;

// Parametros referentes ao quadrado
int tamQuadrado_2,xcQuadrado,ycQuadrado;
GLfloat rQuadrado,gQuadrado,bQuadrado;

// Variavel que guarda se ja existe ou nao um quadrado na tela
bool existeQuadrado = false;

// Guarda se o botao direito esta pressionado ou nao e qual a ultima
// posicao do ponteiro do mouse.
bool botaoEsqPressionado;
int xLastBotaoEsq;
int yLastBotaoEsq;

void mouse(int botao, int estado, int x, int y)
{
	int metade = tamQuadrado_2;
	
	// Mudando a orientacao do eixo y
	y = alturaJanela - y;
	
	if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
		
		if(existeQuadrado){
		
			if( (abs(x - xcQuadrado) <= tamQuadrado_2) && (abs(y - ycQuadrado) <= tamQuadrado_2) ){
				botaoEsqPressionado = true;
				xLastBotaoEsq = x;
				yLastBotaoEsq = y;
			}
		}else{
			// Nao existe quadrado ainda
			xcQuadrado = x;
			ycQuadrado = y;
			existeQuadrado = true;
			glutPostRedisplay();
		}
	
	}
	else{
		botaoEsqPressionado = false;
		xLastBotaoEsq = -1;
		yLastBotaoEsq = -1;
	}
	
	if(botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN){
		// O botao direito do mouse foi clicado
		
		if(existeQuadrado){
			
			// Checar se o clique foi dentro do quadrado
			if( (abs(x - xcQuadrado) <= tamQuadrado_2) && (abs(y - ycQuadrado) <= tamQuadrado_2) ){
				existeQuadrado = false;
				glutPostRedisplay();
			}
			
		}
	}
	
}

void motion(int x, int y){
	
	// Mudando a orientacao do eixo y
	y = alturaJanela - y;
	
	if(botaoEsqPressionado){
		xcQuadrado = xcQuadrado + (x - xLastBotaoEsq);
		ycQuadrado = ycQuadrado + (y - yLastBotaoEsq);
		glutPostRedisplay();
		xLastBotaoEsq = x;
		yLastBotaoEsq = y;
	}
	
}

void display(void)
{
	/* Limpar todos os pixels */
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* Desenhar o quadrado */
	if(existeQuadrado){
		
		float xcNormalizado = xcQuadrado/(float) larguraJanela;
		float ycNormalizado = ycQuadrado/(float) alturaJanela;
		float tamQ_2_Normalizado = tamQuadrado_2/(float) larguraJanela;
		
		glColor3f(rQuadrado,gQuadrado,bQuadrado);
		glBegin(GL_POLYGON);
			glVertex3f(xcNormalizado+tamQ_2_Normalizado,ycNormalizado+tamQ_2_Normalizado,0.0);
			glVertex3f(xcNormalizado-tamQ_2_Normalizado,ycNormalizado+tamQ_2_Normalizado,0.0);
			glVertex3f(xcNormalizado-tamQ_2_Normalizado,ycNormalizado-tamQ_2_Normalizado,0.0);
			glVertex3f(xcNormalizado+tamQ_2_Normalizado,ycNormalizado-tamQ_2_Normalizado,0.0);
		glEnd();
	}

	/* Trocar buffers */
	glutSwapBuffers();
}

void init (int r, int g, int b)
{
	/*selecionar cor de fundo (preto) */
	glClearColor((GLfloat) r,(GLfloat) g,(GLfloat) b,0.0);

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}

int main (int argc, char** argv)
{
	
	char* filePath = NULL;
	XMLDocument configFile;
	
	// Confere se o arquivo XML foi passado como parametro de entrada
	if (argc > 1 )
		filePath = argv[1];
	else{
		cout << "Por favor entre com o arquivo XML" << endl;
		cout << "Ex: trabalhocg <caminho para config.xml>" << endl;
		return 0;
	}
	
	if(filePath != NULL){
		configFile.LoadFile(filePath);
	}
	
	if(configFile.ErrorID() != 0)
		cout << "Erro no arquivo de entrada config.xml" << endl;
	else{
		
		XMLElement* janelaElement = configFile.FirstChildElement("aplicacao")->FirstChildElement("janela");
		XMLElement* quadradoElement = configFile.FirstChildElement("aplicacao")->FirstChildElement("quadrado");
		XMLElement* fundoElement = janelaElement->FirstChildElement("fundo");

		// Lendo o tamanho da janela
		
		janelaElement->FirstChildElement("largura")->QueryIntText(&larguraJanela);
		janelaElement->FirstChildElement("altura")->QueryIntText(&alturaJanela);
	
		// Lendo o titulo da janela
		const char* tituloJanela = janelaElement->FirstChildElement("titulo")->GetText();
		
		GLfloat rFundo,gFundo,bFundo;
		
		// Lendo cor do fundo
		fundoElement->QueryFloatAttribute("corR",&rFundo);
		fundoElement->QueryFloatAttribute("corG",&gFundo);
		fundoElement->QueryFloatAttribute("corB",&bFundo);
		
		// Lendo atributos do quadrado
		int lado;
		quadradoElement->QueryIntAttribute("tamanho",&lado);
		tamQuadrado_2 = lado/2;
		quadradoElement->QueryFloatAttribute("corR",&rQuadrado);
		quadradoElement->QueryFloatAttribute("corG",&gQuadrado);
		quadradoElement->QueryFloatAttribute("corB",&bQuadrado);
		
		// zerar o vetor de status das teclas
		memset(keyStatus,256,sizeof(int));
		
		glutInit(&argc,argv);
		
		// Utilizar Double Buffer e esquema de cores RGB
		glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
		
		// Definindo o tamanho da janela a ser aberta
		glutInitWindowSize(larguraJanela,alturaJanela);
		
		// Escolher posicao da janela na tela
		glutInitWindowPosition(250,250);
		
		// Definindo o titulo da janela
		glutCreateWindow(tituloJanela);
		

		init(rFundo,gFundo,bFundo);
		
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
		glutMotionFunc(motion);
		glutMainLoop();
		
	}

	return 0;
}

