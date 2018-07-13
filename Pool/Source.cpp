#include<stdlib.h>
#include <GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define BallRadius 0.5

void create_Cube(double x, double y, double z);

typedef struct point {
	double x;
	double y;
	double z;
}point;

/*  כדור המשחק */
typedef struct sphire {

	point ball_point;
	int right, left;
	int in, out;

}sphire;

/* החומות שבאמצע השולחן */
typedef struct fence {

	point BotLeftPoint;
	point TopRightPoint;

}fence;

char str[50], *str2;
int s = 0;
int rotate = 0, rotate2 = 85, rotate3 = 0;
double aC, xC, zC, ball_speed = 0.015;
sphire b;
fence fences[5];


/*  איתחול ערכים למבנים */
void fillStructs()
{
	b.ball_point.x = 7;
	b.ball_point.y = 0;
	b.ball_point.z = 10.5;

	b.right = 0;
	b.left = 0;
	b.in = 0;
	b.out = 0;

	fences[0].BotLeftPoint.x = -6;
	fences[0].BotLeftPoint.z = 8.7;
	fences[0].TopRightPoint.x = 10;
	fences[0].TopRightPoint.z = 8.3;

	fences[1].BotLeftPoint.x = -8;
	fences[1].BotLeftPoint.z = 4;
	fences[1].TopRightPoint.x = 4;
	fences[1].TopRightPoint.z = 3.5;

	fences[2].BotLeftPoint.x = -5;
	fences[2].BotLeftPoint.z = 0;
	fences[2].TopRightPoint.x = 9.5;
	fences[2].TopRightPoint.z = -0.5;

	fences[3].BotLeftPoint.x = -10;
	fences[3].BotLeftPoint.z = -3.8;
	fences[3].TopRightPoint.x = 4.5;
	fences[3].TopRightPoint.z = -4.3;

	fences[4].BotLeftPoint.x = -4;
	fences[4].BotLeftPoint.z = -7.8;
	fences[4].TopRightPoint.x = 10;
	fences[4].TopRightPoint.z = -8.3;
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(1);

	if (key == 'w') {
		b.in = 0;
		b.out = 1;
	}
	if (key == 's') {
		b.out = 0;
		b.in = 1;
	}

	if (key == 'd') {
		b.right = 1;
		b.left = 0;
	}
	if (key == 'a') {
		b.left = 1;
		b.right = 0;
	}

	if (key == 'l') {
		rotate += 5;
		rotate %= 360;
	}
	if (key == 'i') {
		rotate2 += 5;
		rotate2 %= 360;
	}
	if (key == 'k') {
		rotate2 -= 5;
		rotate2 %= 360;
	}
	if (key == 'j') {
		rotate -= 5;
		rotate %= 360;
	}
	if (key == 'n') {
		rotate3 += 5;
		rotate3 %= 360;
	}
	if (key == 'm') {
		rotate3 -= 5;
		rotate3 %= 360;
	}

	glutPostRedisplay();
}

/* ציור השולחן */
void draw_table()
{
	glColor3f(0.4, 0.3, 0.7);
	glTranslatef(0, 8, 0);

	/* משטח השולחן */
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-11, 0, -14);
	glVertex3f(11, 0, -14);
	glVertex3f(11, 0, 14);
	glVertex3f(-11, 0, 14);
	glEnd();

	/* הרגליים של השולחן */
	glColor3f(0.5, 0.9, 0.2);
	glTranslatef(-10, 0, 13);
	create_Cube(-0.8, -8, 0.8);
	glTranslatef(0, 0, -26);
	create_Cube(-0.8, -8, 0.8);
	glTranslatef(20, 0, 0);
	create_Cube(-0.8, -8, 0.8);
	glTranslatef(0, 0, 26);
	create_Cube(-0.8, -8, 0.8);
	glTranslatef(-10, 0, -13);

	/* הגדר של השולחן */
	glColor3f(0.9, 0.1, 0.2);
	glTranslatef(0, 0, -13.5);
	create_Cube(-11, 0.8, 0.5);
	glTranslatef(0, 0, 27);
	create_Cube(-11, 0.8, 0.5);
	glTranslatef(10.5, 0, -13.5);
	create_Cube(-0.5, 0.8, 14);
	glTranslatef(-21, 0, 0);
	create_Cube(-0.5, 0.8, 14);
}

/* ציור החומות */
void draw_fence()
{
	glTranslatef(10.5, 0, 0);
	glTranslatef(2, 0, 9);
	create_Cube(-8, 0.5, 0.4);

	glTranslatef(-4, 0, -4.5);
	create_Cube(-6, 0.5, 0.4);

	glTranslatef(4, 0, -4);
	create_Cube(-7.8, 0.5, 0.4);

	glTranslatef(-5, 0, -4);
	create_Cube(-7, 0.5, 0.4);

	glTranslatef(6, 0, -4);
	create_Cube(-7, 0.5, 0.4);

	glTranslatef(-3, 0, 8);
}

/* בדיקה אם הכדור פגע באחת מן החומות */
int check_Fences()
{
	int i;

	for (i = 0; i < 5; i++)
	{
		if ((b.ball_point.z - BallRadius<fences[i].BotLeftPoint.z  && b.ball_point.z - BallRadius>fences[i].TopRightPoint.z))
			if ((b.ball_point.x + BallRadius > fences[i].BotLeftPoint.x  && b.ball_point.x + BallRadius< fences[i].TopRightPoint.x))
				return 1;

		if ((b.ball_point.z + BallRadius<fences[i].BotLeftPoint.z  && b.ball_point.z + BallRadius>fences[i].TopRightPoint.z))
			if ((b.ball_point.x + BallRadius > fences[i].BotLeftPoint.x  && b.ball_point.x + BallRadius< fences[i].TopRightPoint.x))
				return 1;

		if ((b.ball_point.z - BallRadius<fences[i].BotLeftPoint.z  && b.ball_point.z - BallRadius>fences[i].TopRightPoint.z))
			if ((b.ball_point.x - BallRadius > fences[i].BotLeftPoint.x  && b.ball_point.x - BallRadius < fences[i].TopRightPoint.x))
				return 1;

		if ((b.ball_point.z + BallRadius<fences[i].BotLeftPoint.z  && b.ball_point.z + BallRadius>fences[i].TopRightPoint.z))
			if ((b.ball_point.x - BallRadius > fences[i].BotLeftPoint.x  && b.ball_point.x - BallRadius < fences[i].TopRightPoint.x))
				return 1;

		if ((b.ball_point.z <= fences[i].BotLeftPoint.z  && b.ball_point.z >= fences[i].TopRightPoint.z))
			if ((b.ball_point.x - BallRadius >= fences[i].BotLeftPoint.x  && b.ball_point.x - BallRadius <= fences[i].TopRightPoint.x))
				return 2;


		if ((b.ball_point.z <= fences[i].BotLeftPoint.z  && b.ball_point.z >= fences[i].TopRightPoint.z))
			if ((b.ball_point.x + BallRadius >= fences[i].BotLeftPoint.x  && b.ball_point.x + BallRadius <= fences[i].TopRightPoint.x))
				return 2;
	}
	return 0;
}

/* ציור הכדור */
void draw_ball()
{
	glColor3f(1, 1, 1);
	glutSolidSphere(0.3, 32, 32);
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0, -20, -55);
	glRotatef(rotate, 0, 1, 0);
	glRotatef(rotate2, 1, 0, 0);
	glRotatef(rotate3, 0, 0, 1);

	/*  רצפה */
	glTranslatef(0, 5, -13);
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-30, 0, -30);
	glVertex3f(30, 0, -30);
	glVertex3f(30, 0, 30);
	glVertex3f(-30, 0, 30);
	glEnd();

	/* השולחן */
	draw_table();

	/* החומות  */
	draw_fence();

	/* פתח השולחן */
	glColor3f(0, 0, 0);
	glTranslatef(0, 0.1, -12.5);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 720; i++) {
		aC = 3.14 * i;
		xC = cos(aC / 360);
		zC = sin(aC / 360);
		glVertex3d(xC, 0, zC);
	}
	glEnd();

	/* קירות */
	glTranslatef(0, -0.1, 12.5);
	glColor3f(0.3, 0.5, 0.7);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-27, -8, -25);
	glVertex3f(27, -8, -25);
	glVertex3f(27, 20, -25);
	glVertex3f(-27, 20, -25);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-27, -8, -25);
	glVertex3f(-27, 20, -25);
	glVertex3f(-27, 20, 25);
	glVertex3f(-27, -8, 25);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(27, -8, -25);
	glVertex3f(27, 20, -25);
	glVertex3f(27, 20, 25);
	glVertex3f(27, -8, 25);
	glEnd();

	/* תוצאה */
//	sprintf(str, "Your SCORE = %d", s);
	str2 = str;
	glColor3f(0, 0, 0);
	glRasterPos3f(-4, 2, -18);
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str2);
	while (*(++str2));

	printf(str, "Hello");
	str2 = str;
	glColor3f(0, 0, 0);
	glRasterPos3f(-17, 2, -18);
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str2);
	while (*(++str2));

	// כדור //
	glTranslatef(0, BallRadius, 0);
	glTranslatef(b.ball_point.x, b.ball_point.y, b.ball_point.z);
	draw_ball();
	glTranslatef(-b.ball_point.x, -b.ball_point.y, -b.ball_point.z);
	glTranslatef(0, -BallRadius, 0);

	glutSwapBuffers();
}

/*  שינוי כיוון */
void swap(int* a, int* b)
{
	*a = 0;
	*b = 1;
}

/*  הזזת הכדור */
void Idle()
{
	/*  בדיקה אם הכדור פגע במטרה */
	if (sqrt(pow(b.ball_point.x - (0), 2) + pow(b.ball_point.z - -(11.5), 2)) <= 0.85) {
		fillStructs();
		s = s + 10;
	}

	if (b.right)
	{
		if (!check_Fences()) {

			b.ball_point.x += ball_speed;
			if (b.ball_point.x >= 9.5) {
				b.ball_point.x -= ball_speed;
				swap(&b.right, &b.left);
			}
		}
		else
		{
			b.ball_point.x -= ball_speed;
			if (!b.out && !b.in) {
				swap(&b.right, &b.left);
			}
			else if (check_Fences() == 2)
			{
				b.ball_point.x -= BallRadius;
				swap(&b.right, &b.left);
			}
		}

	}

	if (b.left)
	{
		if (!check_Fences())
		{
			b.ball_point.x -= ball_speed;
			if (b.ball_point.x <= -9.5) {
				b.ball_point.x += ball_speed;
				swap(&b.left, &b.right);
			}
		}
		else
		{
			b.ball_point.x += ball_speed;
			if (!b.out && !b.in) {
				swap(&b.left, &b.right);
			}
			else if (check_Fences() == 2)
			{
				b.ball_point.x += BallRadius;
				swap(&b.left, &b.right);
			}
		}
	}

	if (b.out)
	{
		if (!check_Fences())
		{
			b.ball_point.z -= ball_speed;
			if (b.ball_point.z <= -12.5) {
				b.ball_point.z += ball_speed;
				swap(&b.out, &b.in);
			}

		}
		else
		{
			b.ball_point.z += ball_speed;
			swap(&b.out, &b.in);
		}
	}
	if (b.in)
	{
		if (!check_Fences()) {
			b.ball_point.z += ball_speed;
			if (b.ball_point.z >= 12.5) {
				b.ball_point.z -= ball_speed;
				swap(&b.in, &b.out);
			}

		}
		else
		{
			b.ball_point.z -= ball_speed;
			swap(&b.in, &b.out);
		}
	}
	draw();
}

/* מצייר קובייה */
void create_Cube(double x, double y, double z)
{
	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1);
	glVertex3f(x, 0, z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glVertex3f(x, 0, z);

	glNormal3f(0, 0, 1);
	glVertex3f(x, 0, -z);
	glVertex3f(-x, 0, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);

	glNormal3f(-1, 0, 0);
	glVertex3f(x, 0, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);
	glVertex3f(x, 0, -z);

	glNormal3f(1, 0, 0);
	glVertex3f(-x, 0, z);
	glVertex3f(-x, 0, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);

	glNormal3f(1, 0, 0);
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);

	glEnd();
}



// Set OpenGL parameters
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	// Lighting parameters

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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // RGB display, double-buffered, with Z-Buffer
	glutInitWindowSize(600, 600); // 500 x 500 pixels
	glutCreateWindow("3D");
	init();
	fillStructs();
	glutDisplayFunc(draw); // Set the display function
	glutKeyboardFunc(keyboard); // Set the keyboard function
	glutIdleFunc(Idle);
	glutMainLoop(); // Start the main event loop
}