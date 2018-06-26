#include <GL/glut.h>
#include<math.h>
int rot_x = 90, rot_z = 90;
float xt = 0.0, yt = 0.0, zt = 0.0;
double color1 = 0.3, color2 = 0.0, color3 = 0.3;
const float DEG2RAD = 3.14159 / 180;
struct kadur
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
kadur our_balls[10];  //drawball
void drawBall(kadur ball) {
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
void border2() {
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
	double x1 = 90, xt = 5 * cos(90.0 / 180), yt = 5 * sin(90.0 / 180), r, a, x, y;
	glBegin(GL_POLYGON); /// glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 720; i++) {
		a = 3.14 * i;
		x = cos(a / 360);
		y = sin(a / 360);
		glVertex3d(x, 0, y);
	}
	glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(1);
	if (key == 'r') {
		rot_z += 5;
		rot_z %= 360;
	}
	if (key == 't') {
		rot_x += 5;
		rot_x %= 360;
	}
	if (key == '0')
	{
		our_balls[0].active = true;
		our_balls[1].active = false;
		our_balls[2].active = false;
		our_balls[0].red = 1;
		our_balls[0].green = 1;
		our_balls[0].blue = 1;

	}

	if (key == 'w')
	{
		for (int i = 0; i<10; i++) {
			if (our_balls[i].active == true)
			{
				our_balls[i].f1 = true;
				our_balls[i].f2 = false;
				our_balls[i].f3 = false;
				our_balls[i].f4 = false;
			}
		}
	}

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
		our_balls[i].v = 0.000350;
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
	border2();
	glTranslatef(xt, yt, zt - 9.5);
	border2();
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
	////////////////////////////////////////////balls:
	/* 1 */ glColor3f(our_balls[0].red, our_balls[0].green, our_balls[0].blue);
	drawBall(our_balls[0]);
	/* 2 */   glColor3f(our_balls[1].red, our_balls[1].green, our_balls[1].blue);
	drawBall(our_balls[1]);
	glColor3f(our_balls[2].red, our_balls[2].green, our_balls[2].blue);
	drawBall(our_balls[2]);

	//fourth ball - orange
	glColor3f(our_balls[3].red, our_balls[3].green, our_balls[3].blue);
	drawBall(our_balls[3]);
	//fifth ball - blue
	glColor3f(our_balls[4].red, our_balls[4].green, our_balls[4].blue);
	drawBall(our_balls[4]);
	//sixth ball - gray
	glColor3f(our_balls[5].red, our_balls[5].green, our_balls[5].blue);
	drawBall(our_balls[5]);
	//seventh ball - gray
	glColor3f(our_balls[6].red, our_balls[6].green, our_balls[6].blue);
	drawBall(our_balls[6]);
	//eighth ball - orange
	glColor3f(our_balls[7].red, our_balls[7].green, our_balls[7].blue);
	drawBall(our_balls[7]);
	//ninth ball - red
	glColor3f(our_balls[8].red, our_balls[8].green, our_balls[8].blue);
	drawBall(our_balls[8]);
	//tenth ball - purple
	glColor3f(our_balls[9].red, our_balls[9].green, our_balls[9].blue);
	drawBall(our_balls[9]);



	glutSwapBuffers();			// display the output
}
void idle()
{
	for (int i = 0; i < 10; i++) {
		if (our_balls[i].f1 == true)
			our_balls[i].z += our_balls[i].v;
		else if (our_balls[i].f2 == true)
			our_balls[i].z -= our_balls[i].v;
		else if (true && our_balls[i].f3)
			our_balls[i].x -= our_balls[i].v;
		else if (our_balls[i].f4 == true)
			our_balls[i].x += our_balls[i].v;
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
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		// set specular
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		// set shininess
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);		// set light "position", in this case direction
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);		// active material changes by glColor3f(..)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
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
	our_balls[0].z = 2;
	our_balls[0].red = 0.58; our_balls[0].green = 0; our_balls[0].blue = 0.83;
	our_balls[1].z = 3;
	our_balls[1].red = 0.64; our_balls[1].green = 0.16; our_balls[1].blue = 0.16;
	our_balls[2].z = 6;
	our_balls[2].red = 0.16; our_balls[2].green = 0.36; our_balls[2].blue = 0.8;
	our_balls[3].z = 5; our_balls[3].x = -5;
	our_balls[3].red = 0.9; our_balls[3].green = 0.9; our_balls[3].blue = 0.9;
	our_balls[4].z = 4.8; our_balls[4].x = 5;
	our_balls[4].red = 0.31; our_balls[4].green = 0.58; our_balls[4].blue = 0.80;
	our_balls[5].z = 2.5; our_balls[5].x = 4;
	our_balls[5].red = 0.51; our_balls[5].green = 0.51; our_balls[5].blue = 0.51;
	our_balls[6].z = 3; our_balls[6].x = -4;
	our_balls[6].red = 0.51; our_balls[6].green = 0.51; our_balls[6].blue = 0.51;
	our_balls[7].z = 5; our_balls[7].x = -4.3;
	our_balls[7].red = 1; our_balls[7].green = 0.5; our_balls[7].blue = 0.0;
	our_balls[8].z = 6.5; our_balls[8].x = -7;
	our_balls[8].red = 0.64; our_balls[8].green = 0.16; our_balls[8].blue = 0.16;
	our_balls[9].z = 1; our_balls[9].x = -8;
	our_balls[9].red = 0.58; our_balls[9].green = 0; our_balls[9].blue = 0.83;
	init();
	glutIdleFunc(idle);
	glutMainLoop();							// Start the main event loop
}
