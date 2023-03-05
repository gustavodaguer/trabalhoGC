#include <GL/glut.h>
#include <math.h>
#define LINHAS_DO_BIGBEN 64
#define COLUNAS_DO_BIGBEN 64
#define _USE_MATH_DEFINES

int anguloTotal, anguloTotalX, ponteiroMinutos, ponteiroHoras, eixoNormal, sinalNormal;
int iluminacaoAtivada = 1;
int texturaLigada = 1;
int ativarAnimacao = 1;

int tipoMaterial = 1;
GLubyte Imagem[LINHAS_DO_BIGBEN][COLUNAS_DO_BIGBEN][3];

void geraImagemTextura()
// Funcão para carregar as texturas
{ 
	int valor;
	for (int linha = 0; linha < LINHAS_DO_BIGBEN; linha++)
	{
		for (int coluna = 0; coluna < COLUNAS_DO_BIGBEN; coluna++)
		{
			valor = (((linha & 0x2) == 0) ^ ((coluna & 0x4) == 0)) * 255;
			Imagem[linha][coluna][0] = (GLubyte)valor;
			Imagem[linha][coluna][1] = (GLubyte)valor;
			Imagem[linha][coluna][2] = (GLubyte)valor;
		}
	}
}


GLfloat *calculaNorma()
{
	static GLfloat norma[] = {0, 0, 0};
	norma[eixoNormal] = sinalNormal * 1;
	return norma;
}

void adiantaMinuto()
{
	ponteiroMinutos = (ponteiroMinutos - 5) % 360;
}

void atrasaMinuto()
{
	ponteiroMinutos = (ponteiroMinutos + 5) % 360;
}

void adiantaHora()
{
	ponteiroHoras = (ponteiroHoras - 5) % 360;
}

void atrasaHora()
{
	ponteiroHoras = (ponteiroHoras + 5) % 360;
}

void transladaSentidoHorario()
{
	anguloTotal = (anguloTotal + 10) % 360;
}

void transladaSentidoAntiHorario()
{
	anguloTotal = (anguloTotal - 10) % 360;
}

void transladaVerticalmenteCima()
{
	anguloTotalX = (anguloTotalX + 10) % 360;
}

void transladaVerticalmenteBaixo()
{
	anguloTotalX = (anguloTotalX - 10) % 360;
}

void mudaLuz() //Ativa e desativa a luz
{
	if (iluminacaoAtivada == 1)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
		iluminacaoAtivada = 0;
	}
	else if (iluminacaoAtivada == 0)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		iluminacaoAtivada = 1;
	}
}

void mudaMaterial()
// Muda as caracteristicas materias do BigBen
{
	GLfloat mat_specular[] = { 1.0 , 1.0 , 1.0 , 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat no_mat[] = { 0.0 , 0.0 , 0.0 , 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
   	GLfloat local_view[] = { 0.0 };

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_COLOR_MATERIAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (tipoMaterial == 1)
	{
		// reflexão ambiente e difusa;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		tipoMaterial++;
	}

	else if (tipoMaterial == 2)
	{
		// reflexão ambiente, difusa e especular; brilho da superficie baixo;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		tipoMaterial++;
	}

	else if (tipoMaterial == 3)
	{
		// reflexao ambiente, difusa e especular; brilho da superficie alto;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		tipoMaterial++;
	}

	else if (tipoMaterial == 4)
	{
		// reflexão ambiente e difusa ; emission;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		tipoMaterial = 1;
	}
}

void mudaTextura()
{
	if (texturaLigada == 1)
	{
		glDisable(GL_TEXTURE_2D);
		texturaLigada = 0;
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		texturaLigada = 1;
	}
}

void verificaAnimacao(){
	if(ativarAnimacao == 1) ativarAnimacao = 0;
	else if(ativarAnimacao == 0) ativarAnimacao = 1;
}


void animacao(int resposta) 
//Animação do ponteiro do relógio
{
	if (ativarAnimacao == 0)
		return;

	glutPostRedisplay();
	ponteiroMinutos = (ponteiroMinutos - 1) % 360;

	if (ponteiroMinutos % 60 == 0)
	{
		ponteiroHoras = ((ponteiroHoras - 6) % 360);
	}
	
	glutTimerFunc(1000 / 60, animacao, resposta);
}

void desenhaCirculo(double raio)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float angulo = 2 * M_PI * i / 360;
		float x = raio * cos(angulo);
		float y = raio * sin(angulo);
		glVertex2f(x+0.25 , y);
	}
	glEnd();
}

void desenhaMeioTelhado() 
// Desenha o corpo do telhado
{
	eixoNormal = 2;
	sinalNormal = 1;

	glColor3f(0.7569, 0.5765, 0.4196);

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.15, 1.6, -0.1);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(0.85, 1.6, -0.1);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.85, 2.0, -0.1);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0.15, 2.0, -0.1);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-0.05, 0, 0.25);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.15, 1.6, -0.1);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(0.85, 1.6, -0.1);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.85, 2.0, -0.1);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0.15, 2.0, -0.1);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-0.05, 0, 0.95);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.15, 1.6, -0.1);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0.85, 1.6, -0.1);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.85, 2.0, -0.1);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(0.15, 2.0, -0.1);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.7);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.15, 1.6, -0.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.85, 1.6, -0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.85, 2.0, -0.1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.15, 2.0, -0.1);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

}

void desenhaTelhado()
{

	// Primeiro andar de telhado
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.196, 0.333, 0.431);
	glVertex3f(0.15, 1.6, -0.1);
	glNormal3f(0, 1 / M_SQRT2, 1 / M_SQRT2);
	glVertex3f(-0.1, 1.2, 0.1);
	glVertex3f(1.1, 1.2, 0.1);
	glVertex3f(0.85, 1.6, -0.1);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.85, 1.6, -0.1);
	glNormal3f(1 / M_SQRT2, 1 / M_SQRT2, 0);
	glVertex3f(1.1, 1.2, 0.1);
	glVertex3f(1.1, 1.2, -1.1);
	glVertex3f(0.85, 1.6, -0.8);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.85, 1.6, -0.8);
	glNormal3f(0, -1 / M_SQRT2, -1 / M_SQRT2);
	glVertex3f(1.1, 1.2, -1.1);
	glVertex3f(-0.1, 1.2, -1.1);
	glVertex3f(0.15, 1.6, -0.8);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.15, 1.6, -0.8);
	glNormal3f(-1 / M_SQRT2, -1 / M_SQRT2, 0);
	glVertex3f(-0.1, 1.2, -1.1);
	glVertex3f(-0.1, 1.2, 0.1);
	glVertex3f(0.15, 1.6, -0.1);
	glEnd();

	glPopMatrix();

	// chama a função que desenha a parte entre os dois telhados
	desenhaMeioTelhado();

	// Segundo andar de telhado
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.196, 0.333, 0.431);
	glVertex3f(0.5, 2.8, -0.4);
	glNormal3f(0, 1 / M_SQRT2, 1 / M_SQRT2);
	glVertex3f(0.15, 2.0, -0.1);
	glVertex3f(0.85, 2.0, -0.1);
	glNormal3f(1 / M_SQRT2, 1 / M_SQRT2, 0);
	glVertex3f(0.85, 2.0, -0.8);
	glNormal3f(0, -1 / M_SQRT2, -1 / M_SQRT2);
	glVertex3f(0.15, 2.0, -0.8);
	glNormal3f(-1 / M_SQRT2, -1 / M_SQRT2, 0);
	glVertex3f(0.15, 2.0, -0.1);
	glEnd();
	glPopMatrix();
}

void desenhaRelogio()
{
	//Círculo do relogio
	glPushMatrix();
	desenhaCirculo(0.40);
	glPushMatrix();
	glTranslatef(0.25, 0, 0.1);
	gluCylinder(gluNewQuadric(), 0.40, 0.40, 0.1, 32, 32);
	glPopMatrix();

	glTranslatef(0, 0, 0.2);
	desenhaCirculo(0.40);
	glTranslatef(0.25, 0, 0.01);

	//Ponteiro de Minuto
	glPushMatrix();
	glRotatef(ponteiroMinutos, 0, 0, 1);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0.3, 0);
	glVertex3f(-0.03, 0, 0);
	glVertex3f(0.03, 0, 0);
	glVertex3f(0, 0.3, 0);
	glEnd();
	glPopMatrix();

	//Ponteiro de Hora
	glPushMatrix();
	glRotatef(ponteiroHoras, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(0, 0.20, 0);
	glVertex3f(0.03, 0, 0);
	glVertex3f(-0.03, 0, 0);
	glVertex3f(0, 0.20, 0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}


void desenhaParedeMeio() 
//Desenha a parte da torre onde fica o relógio
{
	
	if(sinalNormal > 0) {
		glPushMatrix();
		glBegin(GL_POLYGON);
		glNormal3fv(calculaNorma());
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.1, 0, 0.2);
		glTexCoord2f(0.8f, 0.0f);
		glVertex3f(1.1, 1.2, 0.2);
		glTexCoord2f(0.8f, 0.8f);
		glVertex3f(-0.1, 1.2, 0.2);
		glTexCoord2f(0.0f, 0.8f);
		glVertex3f(-0.1, 0, 0.2);
		
		glEnd();
		glPopMatrix();

		sinalNormal = -1 * sinalNormal;

	} else if (sinalNormal < 0) {

		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(-1, 0, 0);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1, 0, 0.2);
		glTexCoord2f(0.8f, 0.0f);
		glVertex3f(1.1, 0, 0.2);
		glTexCoord2f(0.8f, 0.8f);
		glVertex3f(1.1, 1.2, 0.2);
		glTexCoord2f(0.0f, 0.8f);
		glVertex3f(-0.1, 1.2, 0.2);
		
		glEnd();
		glPopMatrix();

		sinalNormal = -1 * sinalNormal;
	}
}

void desenhaParedeMeioBaixo() 
//Desenha a parte de baixo da torre onde fica o relógio
{
	
	glPushMatrix();
	glBegin(GL_POLYGON);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0, -1.1);
	glTexCoord2f(0.8f, 0.0f);
	glVertex3f(1.1, 0, -1.1);
	glTexCoord2f(0.8f, 0.8f);
	glVertex3f(1.1, 0, 0.1);
	glTexCoord2f(0.0f, 0.8f);
	glVertex3f(-0.1, 0, 0.1);
	
	glEnd();
	glPopMatrix();

	sinalNormal = -1 * sinalNormal;

}

void desenhaParteMeio() 
//Função que chama a função que cria as "paredes" da parte de cima da torre
{
	eixoNormal = 2;
	sinalNormal = 1;

	glPushMatrix();
	glTranslatef(0, 0, -0.1);
	desenhaParedeMeio();
	glPopMatrix();

	sinalNormal = -1;

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.1);
	desenhaParedeMeio();
	glPopMatrix();

	sinalNormal = 1;

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.9);
	desenhaParedeMeio();
	glPopMatrix();

	sinalNormal = -1;

	glPushMatrix();
	glTranslatef(0, 0, -0.9);
	desenhaParedeMeio();
	glPopMatrix();

	sinalNormal = 1;

	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(0, -0.1, -0.2);
	desenhaParedeMeio();
	glPopMatrix();

}

void desenhaParteBaixo() 
//Desenha a parte de baixo da torre
{
	eixoNormal = 2;
	sinalNormal = 1;

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -1, -1);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(1, -1, -1);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(0, -1, 0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -1);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glVertex3f(0, 3, 0);
	glVertex3f(1, 3, 0);
	glVertex3f(1, 3, -1);
	glVertex3f(0, 3, -1);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();
}

void desenhaTorre()
{
	//Chama a função que desenha o corpo da torre
	desenhaParteBaixo();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	//Chama a função que desenha a parte onde tem o relógio
	desenhaParteMeio();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	//Chama a função que desenha o telhado
	desenhaTelhado();
	glTranslatef(0.5, 2.2, -0.4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.25, 3.6, 0.01);
	// Chama função que desenha o relógio
	desenhaRelogio();
	glPopMatrix();
}

void iniciar(void)
{
	glClearColor(0, 0, 0, 0);
	geraImagemTextura();
	//Funções de textura
	glTexImage2D(GL_TEXTURE_2D, 0, 3, COLUNAS_DO_BIGBEN, LINHAS_DO_BIGBEN, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, Imagem);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Abilita a textura
	glEnable(GL_TEXTURE_2D);

	//Corrige textura na mudança de perspectiva
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Inicia iluminação e textura padrão
	mudaLuz();
	mudaTextura();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0.7569, 0.5765, 0.4196);

	glPushMatrix();
	glRotatef(anguloTotal, 0, 1, 0);
	glRotatef(anguloTotalX, 1, 0, 0);
	glTranslatef(0, -2, 2);
	desenhaTorre();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -5);
	
}

void arrow_keys ( int a_keys, int x, int y )  
{
	switch ( a_keys ) 
	{
	case GLUT_KEY_RIGHT:
		//Move a torre no sentido Horario
		transladaSentidoHorario();
		break;
	case GLUT_KEY_LEFT:
		//Move a torre no sentido Anti Horario
		transladaSentidoAntiHorario();
		break;
	case GLUT_KEY_DOWN:
		//Rota a torre no eixo z para frente
		transladaVerticalmenteCima();
		break;
	case GLUT_KEY_UP:
		//Rota a torre no eixo z para tras
		transladaVerticalmenteBaixo();
		break;
	}
}

void opcoesTeclado(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'm':
		//Move o ponteiro de minuto pra frente
		adiantaMinuto();
		break;
	case 'M':
		//Move o ponteiro de minuto pra tras
		atrasaMinuto();
		break;
	case 'h':
		//Move o ponteiro de hora pra frente
		adiantaHora();
		break;
	case 'H':
		//Move o ponteiro de hora pra tras
		atrasaHora();
		break;
	case 'z':
		//Muda as caracteristicas materiais do Big Ben
		mudaMaterial();
		break;
	case 'i':
		//Liga e desliga a luz
		mudaLuz();
		break;
	case 't':
		//Muda a textura do Big Ben
		mudaTextura();
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void opcoesMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		//Pausa e despausa o relógio
		verificaAnimacao();
		animacao(0);
	} else if (button == GLUT_RIGHT_BUTTON){
		verificaAnimacao();
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	iniciar();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(opcoesTeclado);
	glutMouseFunc(opcoesMouse);
	glutSpecialFunc (arrow_keys);
	glutMainLoop();
	return 0;
}