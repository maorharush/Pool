#include <GL/glut.h>
#include<math.h>


#define CAMERA_UP 'i'
#define CAMERA_DOWN 'k'
#define CAMERA_LEFT 'j'
#define CAMERA_RIGHT 'l'
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

int rot_x = 90, rot_z = 90, rot_y=90;
float xt = 0.0, yt = 0.0, zt = 0.0;
double color1 = 0.3, color2 = 0.0, color3 = 0.3;
const float DEG2RAD = 3.14159 / 180;
struct Ball
{
	double x;
	double y;
	double z;
	double v;
	double d;
	bool f1, f2, f3, f4;
	bool active;
	double red, green, blue;
};
Ball ball[10];  //drawball
void drawBall(Ball ball) {
	glTranslatef(ball.x, 0, ball.z);
	glutSolidSphere(0.3, 32, 32);
	glTranslatef(-ball.x, 0, -ball.z);
}

void border() {
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0, 0, -5);
	glVertex3f(0, 0.5, -5);
	glVertex3f(0, 0.5, 5);
	glVertex3f(0, 0, 5);

	glNormal3f(1, 0, 0);
	glVertex3f(-0.5, 0, -5);
	glVertex3f(-0.5, 0.5, -5);
	glVertex3f(-0.5, 0.5, 5);
	glVertex3f(-0.5, 0, 5);

	glNormal3f(0, 1, 0);
	glVertex3f(0, 0.5, -5);
	glVertex3f(-0.5, 0.5, -5);
	glVertex3f(-0.5, 0.5, 5);
	glVertex3f(0, 0.5, 5);

	glNormal3f(0, 0, 1);
	glVertex3f(0, 0.5, 5);
	glVertex3f(-0.5, 0.5, 5);
	glVertex3f(-0.5, 0, 5);
	glVertex3f(0, 0, 5);

	glNormal3f(0, 0, 1);
	glVertex3f(0, 0.5, -5);
	glVertex3f(-0.5, 0.5, -5);
	glVertex3f(-0.5, 0, -5);
	glVertex3f(0, 0, -5);
	glEnd();
}

//sides
void borderSides() {
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(-5, 0, 5);
	glVertex3f(-5, 0.5, 5);
	glVertex3f(5, 0.5, 5);
	glVertex3f(5, 0, 5);

	glNormal3f(0, 0, 1);
	glVertex3f(-5, 0, 4.5);
	glVertex3f(-5, 0.5, 4.5);
	glVertex3f(5, 0.5, 4.5);
	glVertex3f(5, 0, 4.5);

	glNormal3f(0, 1, 0);
	glVertex3f(-5, 0.5, 4.5);
	glVertex3f(5, 0.5, 4.5);
	glVertex3f(5, 0.5, 5);
	glVertex3f(-5, 0.5, 5);
	glEnd();
}
//inside
void border3() {
	glBegin(GL_QUADS);
	// Front	  		
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5, 0);
	glVertex3f(4, 0.5, 0);
	glVertex3f(4, 0, 0);

	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(4, 0.5, 0.5);
	glVertex3f(4, 0, 0.5);

	glNormal3f(0, 1, 0);
	glVertex3f(0, 0.5, 0);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(4, 0.5, 0.5);
	glVertex3f(4, 0.5, 0);

	glNormal3f(1, 0, 0);
	glVertex3f(4, 0, 0.5);
	glVertex3f(4, 0.5, 0.5);
	glVertex3f(4, 0.5, 0);
	glVertex3f(4, 0, 0);
	glNormal3f(1, 0, 0);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, 0.5, 0);
	glVertex3f(0, 0, 0);
	glEnd();
}
void leg() {
	glBegin(GL_QUADS);
	// Front	  		
	glNormal3f(0, 0, 0.5);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -5, 0.5);
	glVertex3f(0.5, -5, 0.5);
	glVertex3f(0.5, 0, 0.5);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(-0.5, -5, -0.5);
	glVertex3f(0.5, -5, -0.5);
	glVertex3f(0.5, 0, -0.5);

	// Left side
	glNormal3f(-0.5, 0, 0);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -5, 0.5);
	glVertex3f(-0.5, -5, -0.5);
	glVertex3f(-0.5, 0, -0.5);

	// Right side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, -5, 0.5);
	glVertex3f(0.5, -5, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glEnd();
}
void drawCircle()
{
	double x1 = 90, xt = 5 * cos(90.0 / 180), yt = 5 * sin(90.0 / 180), a, x, y;
	glBegin(GL_POLYGON); /// glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 720; i++) {
		a = 3.14 * i;
		x = cos(a / 360);
		y = sin(a / 360);
		glVertex3d(x, 0, y);
	}
	glEnd();
}
void repaintBalls() {
	ball[0].z = 2;
	ball[0].red = 0.58; ball[0].green = 0; ball[0].blue = 0.83;
	ball[1].z = 3;
	ball[1].red = 0.64; ball[1].green = 0.16; ball[1].blue = 0.16;
	ball[2].z = 6;
	ball[2].red = 0.16; ball[2].green = 0.36; ball[2].blue = 0.8;
	ball[3].z = 5; ball[3].x = -5;
	ball[3].red = 0.9; ball[3].green = 0.9; ball[3].blue = 0.9;
	ball[4].z = 4.8; ball[4].x = 5;
	ball[4].red = 0.31; ball[4].green = 0.58; ball[4].blue = 0.80;
	ball[5].z = 2.5; ball[5].x = 4;
	ball[5].red = 0.51; ball[5].green = 0.51; ball[5].blue = 0.51;
	ball[6].z = 3; ball[6].x = -4;
	ball[6].red = 0.51; ball[6].green = 0.51; ball[6].blue = 0.51;
	ball[7].z = 5; ball[7].x = -4.3;
	ball[7].red = 1; ball[7].green = 0.5; ball[7].blue = 0.0;
	ball[8].z = 6.5; ball[8].x = -7;
	ball[8].red = 0.64; ball[8].green = 0.16; ball[8].blue = 0.16;
	ball[9].z = 1; ball[9].x = -8;
	ball[9].red = 0.58; ball[9].green = 0; ball[9].blue = 0.83;
}
void drawAllBalls()
{
	repaintBalls();
	////////////////////////////////////////////balls:
	/* 1 */ glColor3f(ball[0].red, ball[0].green, ball[0].blue);
	drawBall(ball[0]);
	/* 2 */   glColor3f(ball[1].red, ball[1].green, ball[1].blue);
	drawBall(ball[1]);
	glColor3f(ball[2].red, ball[2].green, ball[2].blue);
	drawBall(ball[2]);

	//fourth ball - orange
	glColor3f(ball[3].red, ball[3].green, ball[3].blue);
	drawBall(ball[3]);
	//fifth ball - blue
	glColor3f(ball[4].red, ball[4].green, ball[4].blue);
	drawBall(ball[4]);
	//sixth ball - gray
	glColor3f(ball[5].red, ball[5].green, ball[5].blue);
	drawBall(ball[5]);
	//seventh ball - gray
	glColor3f(ball[6].red, ball[6].green, ball[6].blue);
	drawBall(ball[6]);
	//eighth ball - orange
	glColor3f(ball[7].red, ball[7].green, ball[7].blue);
	drawBall(ball[7]);
	//ninth ball - red
	glColor3f(ball[8].red, ball[8].green, ball[8].blue);
	drawBall(ball[8]);
	//tenth ball - purple
	glColor3f(ball[9].red, ball[9].green, ball[9].blue);
	drawBall(ball[9]);
}




void draw()
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -15);
	
	glRotatef(rot_x, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);
	/*********/
	for (int i = 0; i < 10; i++)
	{
		ball[i].v = 0.000350;
	}
	glBegin(GL_QUADS);
	// Floor
	glColor3f(0.15, 0.23, 0.23);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-10, -5, -15);
	glVertex3f(10, -5, -15);
	glVertex3f(10, -5, 15);
	glVertex3f(-10, -5, 15);
	//table
	glColor3f(0.2, 0.7, 0.3);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-5, 0, -5);
	glVertex3f(5, 0, -5);
	glVertex3f(5, 0, 5);
	glVertex3f(-5, 0, 5);
	glEnd();
	glTranslatef(-4.5, 0, -4.5);
	leg();
	glTranslatef(9, 0, 0);
	leg();
	glTranslatef(0, 0, 9);
	leg();
	glTranslatef(-9, 0, 0);
	leg();
	glTranslatef(4.5, 0, -4.5);
	glTranslatef(xt, yt, zt);
	glColor3f(0.3, 0.5, 0.4);
	glColor3f(0.958, 0.673, 0.523);
	glTranslatef(xt + 5, yt, zt);
	border();
	glTranslatef(xt - 10, yt, zt);
	border();
	glTranslatef(xt + 5, yt, zt);
	borderSides();
	glTranslatef(xt, yt, zt - 9.5);
	borderSides();
	glTranslatef(xt + 1, yt, zt + 7.5);
	border3();
	glTranslatef(xt - 6.5, yt, zt);
	border3();
	glTranslatef(xt, yt, zt + 4);
	border3();
	glTranslatef(xt + 5, yt, zt - 2);
	border3();
	//black circle
	glTranslatef(2, 0.1, 3);
	glColor3f(0, 0, 0);
	drawCircle();
	//black circle
	glTranslatef(2, 0.1, -6.2);
	glColor3f(0, 0, 0);
	drawCircle();

	drawAllBalls();



	glutSwapBuffers();			// display the output
}
void changeBallControl(int ballNum) {
	int i;
	//repaintBalls();
	draw();
	ball[ballNum].red = 1;
	ball[ballNum].blue = 1;
	ball[ballNum].green = 1;
	ball[ballNum].active = true;
	for (i = 0; i < 10; i++)if (i != ballNum) ball[i].active = false;


}

void idle()
{
	for (int i = 0; i < 10; i++) {
		if (ball[i].f1 == true)
			ball[i].z += ball[i].v;
		else if (ball[i].f2 == true)
			ball[i].z -= ball[i].v;
		else if (true && ball[i].f3)
			ball[i].x -= ball[i].v;
		else if (ball[i].f4 == true)
			ball[i].x += ball[i].v;
	}
	draw();
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	GLfloat mat_ambdif[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 80.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif);	// set both amb and diff components
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);			// set specular
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		// set shininess
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);			// set light "position", in this case direction
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);			// active material changes by glColor3f(..)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
}
void keyboard(unsigned char key, int x, int y)
{
	if (key == 02) exit(1);
	//changing rotation keystroks and adding new one
	if (key == CAMERA_UP) {
		rot_z += 5;
		rot_z %= 360;
	}
	if (key == CAMERA_RIGHT) {
		rot_x += 5;
		rot_z %= 360;
	}

	if (key == CAMERA_DOWN) {
		rot_z -= 5;
		rot_z %= 360;
	}
	if (key == CAMERA_LEFT) {
		rot_x -= 5;
		rot_x %= 360;
	}

	if (key >= '0' && key <= '9') {
		changeBallControl(key - 48);
	}
	if (key == KEY_UP) {
		for (int i = 0; i<10; i++) {
			if (ball[i].active == true)
			{
				ball[i].f1 = true;
				ball[i].f2 = false;
				ball[i].f3 = false;
				ball[i].f4 = false;
			}
		}
	}
	if (key == KEY_DOWN) {

	}
	if (key == KEY_LEFT) {

	}
	if (key == KEY_RIGHT) {
		
	}
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	// RGB display, double-buffered, with Z-Buffer
	glutInitWindowSize(500, 500);					// 500 x 500 pixels
	glutCreateWindow("3D");
	glutDisplayFunc(draw);
	// Set the display function
	glutKeyboardFunc(keyboard);					// Set the keyboard function
	
	init();
	glutIdleFunc(idle);
	glutMainLoop();	
	// Start the main event loop
}
