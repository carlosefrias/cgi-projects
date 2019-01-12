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

unsigned int mili_secs = 50;

float xy_aspect;

// matriz de transf. geometrica utilizada pelo botao esferico
float view_rotate[16] = { 1,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          0,0,0,1 };

// vector de posicao utilizado pelo botao de afastamento
float obj_pos[] = { 0.0, 0.0, 0.0 };

// declara��es para os tres eixos (cilindros)
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

// declara��es para o cilindro 2 (cilindro etatico)
double cyl2_radiusb =  3.0;
double cyl2_radiust =  1.0;
double cyl2_height = 10.0;
int    cyl2_slices =   11;
int    cyl2_stacks =    4;
int	   cyl2_smooth = FALSE;
double cyl2_posx   = 0.0;
double cyl2_posy   = 2.0;
double cyl2_posz   = 3.0;

// declara��es para o cilindro 1  (cilindro animado),
double cyl1_radiusb =  1.5;
double cyl1_radiust =  0.5;
double cyl1_height  = 10.0;
int    cyl1_slices =   11;
int    cyl1_stacks =    4;
int	   cyl1_smooth = FALSE;
double cyl1_posx   = 0.0;
double cyl1_posy   = 0.0;
double cyl1_posz   = 0.0;
// respectivas transformacoes...
double cyl1_rotx  = 0.0;
double cyl1_roty  = 0.0;
double cyl1_rotz  = 0.0;
double cyl1_scalex = 1.0;
double cyl1_scaley = 1.0;
double cyl1_scalez = 1.0;
double cyl1_transx = 0.0;
double cyl1_transy = 0.0;
double cyl1_transz = 0.0;
// e incrementos de transforma��es
double delta_alfa  = 1.0;	// incremento em graus para um total de 360
double percent_alfa= delta_alfa/360.0;
double delta_rotx  = 0.0;
double delta_roty  = delta_alfa;
double delta_rotz  = 0.0;
double delta_scalex = pow(cyl2_radiusb/cyl1_radiusb,percent_alfa);
double delta_scaley = delta_scalex;
double delta_scalez = pow(cyl2_height/cyl1_height,percent_alfa);
double delta_transx = (cyl2_posx-cyl1_posx)*percent_alfa;
double delta_transy = (cyl2_posy-cyl1_posy)*percent_alfa;
double delta_transz = (cyl2_posz-cyl1_posz)*percent_alfa;


// declara��es para a fonte de luz LIGHT0;
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

const int animacao = TRUE;

void myUpdateTransforms(int dummy)
{
	if (animacao)
	{
		cyl1_rotx  += delta_rotx;
		cyl1_roty  +=delta_roty;
		cyl1_rotz +=delta_rotz;
		// cyl1_scalex;
		// cyl1_scaley;
		// cyl1_scalez;
		// cyl1_transx;
		// cyl1_transy;
		// cyl1_transz; 
		if (cyl1_roty < 360.0)
			glutTimerFunc(mili_secs, myUpdateTransforms, 0);
	}
}

void display(void)
{
	// ****** declaracoes internas 'a funcao display() ******
	
	GLUquadric* glQ;	// nec. p/ criar sup. quadraticas (cilindros, esferas...)

	// ****** fim de todas as declaracoes da funcao display() ******



	glQ = gluNewQuadric();
	gluQuadricTexture( glQ,  GL_TRUE);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	// inicializacoes da matriz de visualizacao
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .1, 50.0 );

	//inicializacoes da matriz de transformacoes geometricas
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	// afasta a cena de 25 unidades mais a dist�ncia...
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
	/***/

	// inibicao de atribuicao directa de cores


	// define caracteristicas de ilumina��o do material a utilizar
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat1_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat1_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat1_ambient);

	// desenhar as figuras necess�rias
	//desenha o plano xoy
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	glRectd(0.0,0.0,dimx,dimy);
	glPopMatrix();
	//desenha o plano yoz	
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	glRotated(-90,0,1,0);
	glRectd(0.0,0.0,dimx,dimy);
	glPopMatrix();	
	//desenha o plano xoz	
	glColor3f(0.0,1.0,1.0);
	glPushMatrix();
	glRotated(90,1,0,0);
	glRectd(0.0,0.0,dimx,dimz);
	glPopMatrix();
	//desenha o tampo da mesa
	double dim_cubo=4.0;
	glColor3f(0.0,0.0,1.0);
	glPushMatrix();
	glTranslated(dim_cubo/2,dim_cubo/2,dim_cubo/2);
	glScaled(1, 0.125, 1 );
	glutSolidCube(dim_cubo);
	glPopMatrix();
	//Desenha as patas da mesa
	glColor3f(0.0,1.0,0.0);		// verde
	glPushMatrix();
	glRotated(-90.0, 1.0,0.0,0.0 );
	glTranslated(dim_cubo/6,-dim_cubo/6,0);
	gluCylinder(glQ, 0.2, 0.2, dim_cubo/2, 4*axis_nslices, axis_nstacks);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	glRotated(-90.0, 1.0,0.0,0.0 );
	glTranslated(dim_cubo-dim_cubo/6,-dim_cubo/6,0);
	gluCylinder(glQ, 0.2, 0.2, dim_cubo/2, 4*axis_nslices, axis_nstacks);
	glPopMatrix();
	glPushMatrix();	
	glColor3f(0.0,1.0,0.0);
	glRotated(-90.0, 1.0,0.0,0.0 );
	glTranslated(dim_cubo-dim_cubo/6,-(dim_cubo-dim_cubo/6),0);
	gluCylinder(glQ, 0.2, 0.2, dim_cubo/2, 4*axis_nslices, axis_nstacks);
	glPopMatrix();
	glPushMatrix();	
	glColor3f(0.0,1.0,0.0);
	glRotated(-90.0, 1.0,0.0,0.0 );
	glTranslated(dim_cubo/6,-(dim_cubo-dim_cubo/6),0);
	gluCylinder(glQ, 0.2, 0.2, dim_cubo/2, 4*axis_nslices, axis_nstacks);
	glPopMatrix();
	//Desenho do rel�gio
	glPushMatrix();	
	glColor3f(0.0,1.5,1.0);
	glTranslated(dim_cubo/2,dim_cubo/2+1,dim_cubo/2);
	gluCylinder(glQ, 1, 1, 0.2, 10*axis_nslices, axis_nstacks);
	glPopMatrix();
	glPushMatrix();	
	glColor3f(0.0,1.5,1.0);	
	glTranslated(dim_cubo/2,dim_cubo/2+1,dim_cubo/2);
	gluDisk(glQ, 0, 1, 25, 25+0.1);
	glPopMatrix();
	glPushMatrix();	
	glColor3f(0.0,1.5,1.0);	
	glTranslated(dim_cubo/2,dim_cubo/2+1,dim_cubo/2+0.2);
	gluDisk(glQ, 0, 1, 25, 25-0.1);
	glPopMatrix();
	//Desenho dos ponteiros
	//ponteiro dos minutos
	glColor3f(1.0,0.0,0.0);		// vermelho
	glPushMatrix();
	glRotated(-90.0, 1.0,0.0,0.0);
	glTranslated(dim_cubo/2,-dim_cubo/2-0.2,dim_cubo/2+1);
	gluCylinder(glQ, 0.1, axis_radius_end, 0.7, 10, axis_nstacks);
	glPopMatrix();
	//ponteiro das horas
	glColor3f(0.0,1.0,0.0);	
	glPushMatrix();	
	glRotated(-90.0, 1.0,0.0,0.0);
	glTranslated(dim_cubo/2,-dim_cubo/2-0.2,dim_cubo/2+1);
	gluCylinder(glQ, 0.1, axis_radius_end, 0.4, 10, axis_nstacks);
	glPopMatrix();	
	//ponteiro dod segundos
	glColor3f(0.0,0.0,1.0);	
	glPushMatrix();	
	glRotated(-90.0, 1.0,0.0,0.0);
	glTranslated(dim_cubo/2,-dim_cubo/2-0.2,dim_cubo/2+1);
	gluCylinder(glQ, 0.1, axis_radius_end, 0.9, 10, axis_nstacks);
	myUpdateTransforms(1);
	glPopMatrix();
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
	//glEnable(GL_CULL_FACE);		/* Use face culling to improve speed. */
	//glCullFace(GL_BACK);		/* Cull only back faces. */

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);  // define luz ambiente
	glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	
	
	// por defeito a cor de fundo e o preto
	//glClearColor(1.0,1.0,1.0,1.0);    // cor de fundo a branco

	// parametros de iluminacao
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  light0_kc);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    light0_kl);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light0_kq);

	// direccao e posicao estao na rotina display()
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);				// GL_FLAT / GL_SMOOTH

	glPolygonMode(GL_FRONT, GL_FILL);	// preence a face da frente dos poligonos
	//glPolygonMode(GL_FRONT, GL_LINE);	// desenha arestas dos poligonos

	// leitura dos ficheiros de imagem e
	//   respectiva inicializa��o de texturas;
	//   descomentar aquando da utiliza��o de texturas.

	pixmap.readBMPFile("feup.bmp");
	pixmap.setTexture(1);

	pixmap.readBMPFile("mandril.bmp");
	pixmap.setTexture(2);

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
   
	glutTimerFunc(mili_secs, myUpdateTransforms, 0);

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
   
    /* Set time zone from TZ environment variable. If TZ is not set,
     * the operating system is queried to obtain the default value 
     * for the variable. 
     */

	glutMainLoop();

	return 0;
}
