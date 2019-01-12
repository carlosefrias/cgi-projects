// G1_Ilum.cpp : Defines the entry point for the console application.
//

#include <glui.h>
#include <math.h>
#include "RGBpixmap.h"

// dimensoes e localizacao da janela
#define DIMX 500
#define DIMY 500
#define INITIALPOS_X 200
#define INITIALPOS_Y 200

const int TRUE  = 1;
const int FALSE = 0;

float xy_aspect;

// matriz de transf. geometrica utilizada pelo botao esferico
float view_rotate[16] = { 1,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          0,0,0,1 };

// vector de posicao utilizado pelo botao de afastamento
float obj_pos[] = { 0.0, 0.0, 0.0 };

// declarações para os tres eixos (cilindros)
double axis_radius_begin =  0.2;
double axis_radius_end   =  0.0;
double axis_lenght       = 16.0;
int axis_nslices = 8;
int axis_nstacks = 1;

// declaracoes para as paredes
float mat1_shininess[] = {128.0}; 
float mat1_specular[] = {0.3, 0.3, 0.3, 1.0};	/* specular reflection. */
float mat1_diffuse[] =  {0.7, 0.7, 0.7, 1.0};	/* diffuse reflection. */
float mat1_ambient[] =  {0.7, 0.7, 0.7, 1.0};	/* ambient reflection. */
double dimx = 10.0;
double dimy =  6.0;
double dimz = 10.0;

// declarações para o cilindro 1
double cyl1_radius =  1.0;
double cyl1_height = 10.0;
int    cyl1_slices =   11;
int	   cyl1_smooth = FALSE;

// declarações para o cilindro 2
double cyl2_radius =  2.0;
double cyl2_height = 10.0;
int    cyl2_slices =   11;
int	   cyl2_smooth = TRUE;

// declarações para a fonte de luz LIGHT0;
float light0_position[]  = {0.0, 3.0, 4.0, 1.0}; // nao necessaria...
float light0_ambient[] =   {0.0, 0.0, 0.0, 1.0}; // sem componente ambiente
float light0_diffuse[] =   {6.0, 6.0, 6.0, 1.0};
float light0_specular[] =  {6.0, 6.0, 6.0, 1.0};
float light0_kc = 0.0;
float light0_kl = 1.0;
float light0_kq = 0.0;
double light0x = dimx/2.0;
double light0y = 4;
double light0z = dimz/2.0;
double symb_light0_radius = 0.4;
int symb_light0_slices = 8;
int symb_light0_stacks =16;

// fonte (global) de luz ambiente 
float light_ambient[] = {0.6, 0.6, 0.6, 1.0}; /* Set the background ambient lighting. */


// variaveis para a janela
int main_window;
GLUI  *glui2;


RGBpixmap pixmap;



void myCylinder(double radius, double height, int slices, int smooth)
{
	const double pi = acos(-1.0);
	// para completar...
	double x1, y1, x0=radius, y0=0, a=2*pi/slices, a2=a/2;
	for (int i=1;i<=slices;i++){
		x1=radius*cos(i*a);
		y1=radius*sin(i*a);
		glBegin(GL_POLYGON);
 			glNormal3d(cos(a2),sin(a2),0.0);
			glVertex3d(x0,y0,height);
			glVertex3d(x0,y0,0.0);
			glVertex3d(x1,y1,0.0);
			glVertex3d(x1,y1,height);
		glEnd();
		a2+=a;
		x0=x1;
		y0=y1;
	}
}


void display(void)
{
	// ****** declaracoes internas 'a funcao display() ******
	
	float temp;
	double normal[3], normal_lenght;

	GLUquadric* glQ;	// nec. p/ criar sup. quadraticas (cilindros, esferas...)

	// ****** fim de todas as declaracoes da funcao display() ******



	glQ = gluNewQuadric();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	// inicializacoes da matriz de visualizacao
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .1, 50.0 );

	//inicializacoes da matriz de transformacoes geometricas
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	// afasta a cena de 25 unidades mais a distância...
	glTranslated(0.0,0.0,-25.0);
	// ...decorrente da utilizacao do botao de afastamento
    glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );    

	// roda a cena para ficar em perspectiva
	glRotated(20.0, 1.0,0.0,0.0 );		// 20 graus em torno de X
	glRotated(-45.0, 0.0,1.0,0.0 );		//-45 graus em torno de Y

	// aplica efeito do botao de rotacao
	glMultMatrixf( view_rotate );

	// permissao de atribuicao directa de cores
	// para objectos que nao tem material atribuido
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Actualizacao da posicao da fonte de luz
	light0_position[0] = light0x;	// por razoes de eficiencia, os restantes 
	light0_position[1] = light0y;	// parametros _invariaveis_ da LIGHT0 estao
	light0_position[2] = light0z;	// definidos na rotina inicializacao
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// esfera que simboliza a LIGHT0
	glColor3f(1.0,1.0,0.0);		// cor amarela
	gluQuadricOrientation( glQ, GLU_INSIDE);
	glPushMatrix();
	glTranslated(light0x,light0y,light0z);
	gluSphere(glQ, symb_light0_radius, symb_light0_slices, symb_light0_stacks);
    glPopMatrix();
	gluQuadricOrientation( glQ, GLU_OUTSIDE);


	// cilindro representativo do eixo X
	glColor3f(1.0,0.0,0.0);		// vermelho
	glPushMatrix();
	glRotated(90.0, 0.0,1.0,0.0 );
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();

	// cilindro representativo do eixo Y
	glColor3f(0.0,1.0,0.0);		// verde
	glPushMatrix();
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();
	
	// cilindro representativo do eixo Z
	glColor3f(0.0,0.0,1.0);		// azul
	glPushMatrix();
	// nao necessita rotacao... glRotated(...);
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();

	// inibicao de atribuicao directa de cores
	glDisable(GL_COLOR_MATERIAL);


	// define caracteristicas de iluminação do material a utilizar
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat1_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat1_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat1_ambient);

	// desenha os cilindros
	myCylinder(cyl1_radius, cyl1_height, cyl1_slices, cyl1_smooth);
	myCylinder(cyl2_radius, cyl2_height, cyl2_slices, cyl2_smooth);


	glEnable(GL_TEXTURE_2D);	// descomentar quando se utilizarem texturas

	// desenha a "parede" do plano XY
/*	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glVertex3d( 0.0,  0.0,  0.0);
		glVertex3d(dimx,  0.0,  0.0);
		glVertex3d(dimx, dimy,  0.0);
		glVertex3d( 0.0, dimy,  0.0);
	glEnd();
*/
	
     // desenha a "parede" do plano XY

     glBindTexture(GL_TEXTURE_2D, 1);     // activa a textura 1 (feup)

     glBegin(GL_POLYGON);

          glNormal3d(0.0,0.0,1.0);

          glTexCoord2f(0.0,0.0); glVertex3d( 0.0,  0.0,  0.0);

          glTexCoord2f(1.0,0.0); glVertex3d(dimx,  0.0,  0.0);

          glTexCoord2f(1.0,1.0); glVertex3d(dimx, dimy,  0.0);

          glTexCoord2f(0.0,1.0); glVertex3d( 0.0, dimy,  0.0);

     glEnd();

	// desenha a "parede" do plano ZY
	// a completar...
	glBegin(GL_POLYGON);
		glNormal3d(1.0,0.0,0.0);
		glVertex3d( 0.0, 0.0,  0.0);
		glVertex3d( 0.0, dimy, 0.0);
		glVertex3d( 0.0, dimy, dimz);
		glVertex3d( 0.0, 0.0, dimz);
	glEnd();

	// desenha o chao
	// a completar...
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glVertex3d( 0.0, 0.0,  0.0);
		glVertex3d( 0.0, 0.0, dimz);
		glVertex3d( dimx, 0.0, dimz);
		glVertex3d( dimx, 0.0, 0.0);
	glEnd();

	// desenha a piramide
	// a completar...
	glBegin(GL_POLYGON);
		glNormal3d(0.3,0.3,0.3);
		glVertex3d( dimx/2, 0.0,  0.0);
		glVertex3d( 0.0, dimy/2, 0.0);
		glVertex3d( 0.0, 0.0, dimz/2);
	glEnd();
	glBegin(GL_POLYGON);
		glNormal3d(-0.3,0.3,0.3);
		glVertex3d( 0.0, 0.0, dimz/2);
		glVertex3d( 0.0, dimy/2, 0.0);
		glVertex3d( -dimx/2, 0.0,  0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glNormal3d(-0.3,0.3,-0.3);
		glVertex3d( dimx/2, 0.0, 0.0);
		glVertex3d( 0.0, dimy/2, 0.0);
		glVertex3d( -dimx/2, 0.0,  0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glNormal3d(0.3,0.3,-0.3);
		glVertex3d( dimx/2, 0.0, 0.0);
		glVertex3d( 0.0,0.0,-dimz/2);
		glVertex3d( 0.0, dimy/2,0.0);
	glEnd();	
	glBegin(GL_POLYGON);
		glNormal3d(-0.3,0.3,-0.3);
		glVertex3d( -dimx/2, 0.0, 0.0);
		glVertex3d( 0.0,dimy/2, 0.0);
		glVertex3d( 0.0, 0.0, -dimz/2);
	glEnd();
	//   e' necessário calcular a normal a cada triangulo!


	glDisable(GL_TEXTURE_2D);		// descomentar quando se utilizarem texturas


	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
   
	glFlush();
}


/* Mouse handling */
void processMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{	 
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{	
	}
	
	glutPostRedisplay();
	
}

void processMouseMoved(int x, int y)
{
	
	// pedido de refrescamento da janela
	glutPostRedisplay();				

}

void processPassiveMouseMoved(int x, int y)
{

	// pedido de refrescamento da janela
	glutPostRedisplay();				
}

void reshape(int w, int h)
{
	int tx, ty, tw, th;

	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	xy_aspect = (float)tw / (float)th;

	glutPostRedisplay();

}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:		// tecla de escape termina o programa
         exit(0);
         break;
   }
}


void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  


  glutPostRedisplay();

  /****************************************************************/
  /*            This demonstrates GLUI::sync_live()               */
  /*   We change the value of a variable that is 'live' to some   */
  /*   control.  We then call sync_live, and the control          */
  /*   associated with that variable is automatically updated     */
  /*   with the new value.  This frees the programmer from having */
  /*   to always remember which variables are used by controls -  */
  /*   simply change whatever variables are necessary, then sync  */
  /*   the live ones all at once with a single call to sync_live  */
  /****************************************************************/

//  glui->sync_live();

}

void inicializacao()
{

	glFrontFace(GL_CCW);		/* Front faces defined using a counterclockwise rotation. */
	glDepthFunc(GL_LEQUAL);		/* Por defeito e GL_LESS */
	glEnable(GL_DEPTH_TEST);	/* Use a depth (z) buffer to draw only visible objects. */
	glEnable(GL_CULL_FACE);		/* Use face culling to improve speed. */
	glCullFace(GL_BACK);		/* Cull only back faces. */

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);  // define luz ambiente
	glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	
	
	// por defeito a cor de fundo e o preto
	//glClearColor(1.0,1.0,1.0,1.0);    // cor de fundo a branco/****/

	// parametros de iluminacao
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  light0_kc);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    light0_kl);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light0_kq);

	// direccao e posicao estao na rotina display()
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);/***/
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);/***/
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);/***/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_FLAT);				// GL_FLAT / GL_SMOOTH

	glPolygonMode(GL_FRONT, GL_FILL);	// preence a face da frente dos poligonos
	//glPolygonMode(GL_FRONT, GL_LINE);	// desenha arestas dos poligonos /***/

	// leitura dos ficheiros de imagem e
	//   respectiva inicialização de texturas;
	//   descomentar aquando da utilização de texturas.

	pixmap.readBMPFile("feup.bmp");
	pixmap.setTexture(1);

	pixmap.readBMPFile("tile.bmp");
	pixmap.setTexture(2);

	pixmap.readBMPFile("clamp.bmp");
	pixmap.setTexture(3);

	pixmap.readBMPFile("mandril.bmp");
	pixmap.setTexture(4);

}



int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (DIMX, DIMY);
	glutInitWindowPosition (INITIALPOS_X, INITIALPOS_Y);
	main_window = glutCreateWindow (argv[0]);
 
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc (keyboard);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseMoved);
	glutPassiveMotionFunc(processPassiveMouseMoved);   
   

	/*** Create the bottom subwindow ***/
	glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
	glui2->set_main_gfx_window( main_window );

	GLUI_Rotation *view_rot = glui2->add_rotation( "Rotacao", view_rotate );
	view_rot->set_spin( 1.0 );
	glui2->add_column( false );

	GLUI_Translation *trans_z = 
	glui2->add_translation( "Zoom", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .02 );


	/* We register the idle callback with GLUI, not with GLUT */
	GLUI_Master.set_glutIdleFunc( myGlutIdle );
   
	inicializacao();
   
	glutMainLoop();

	return 0;
}
