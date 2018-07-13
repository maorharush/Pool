#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#pragma region defines section
#define CAMERA_UP 'i'
#define CAMERA_DOWN 'k'
#define CAMERA_LEFT 'j'
#define CAMERA_RIGHT 'l'
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_ROTATE 'q'
#define SPEED 0.05
#define FRICTION_MODIFIER 0.0005
#pragma endregion
int rot_x = 90, rot_z = 90, rot_y = 90, curBallIndex = -1, score = 0;
float xt = 0.0, yt = 0.0, zt = 0.0;
char printContainer[100], *printPointer;
double angle = 0.0, originX, originZ, radius = 0.5;
//const float DEG2RAD = 3.14159 / 180;
struct Ball
{
	double x, y, z, speed, red, green, blue;
	bool left, right, up, down, active, circularMotionIsActive, draw;
};
Ball ball[10];
Ball ballForRefrence; //we'll keep the focused ball details here before changing them

void drawBall(Ball ball, int i) {
	glColor3f(ball.red, ball.green, ball.blue);
	glTranslatef(ball.x, 0.1, ball.z);
	glutSolidSphere(0.3, 32, 32);
	sprintf_s(printContainer, "%d", (char)i);
	printPointer = printContainer;
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(ball.x*0.1, 1, ball.z*0.1);
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *printPointer); while (*(++printPointer));
	glTranslatef(-ball.x, -0.1, -ball.z);
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
	double a, x, y;
	glBegin(GL_POLYGON); /// glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 720; i++) {
		a = 3.14 * i;
		x = cos(a / 360);
		y = sin(a / 360);
		x /= 2;
		y /= 2;
		glVertex3d(x, 0, y);
	}
	glEnd();
}
void initBallParams() {
	ball[6].z = 2; ball[6].x = -8.2; ball[0].red = 0.58; ball[0].green = 0; ball[0].blue = 0.83;
	ball[7].z = 2.6; ball[7].x = -8.2; ball[1].red = 0.64; ball[1].green = 0.16; ball[1].blue = 0.16;
	ball[8].z = 3.2; ball[8].x = -8.2; ball[2].red = 0.16; ball[2].green = 0.36; ball[2].blue = 0.8;
	ball[9].z = 3.8; ball[9].x = -8.2; ball[3].red = 0.5; ball[3].green = 0.8; ball[3].blue = 0.9;
	ball[0].z = 4.4; ball[0].x = -8.2; ball[4].red = 0.31; ball[4].green = 0.58; ball[4].blue = 0.80;
	ball[1].z = 2; ball[1].x = -7.6; ball[5].red = 0.51; ball[5].green = 0.51; ball[5].blue = 0.51;
	ball[2].z = 2.6; ball[2].x = -7.6; ball[6].red = 0.51; ball[6].green = 0.51; ball[6].blue = 0.51;
	ball[3].z = 3.2; ball[3].x = -7.6; ball[7].red = 1; ball[7].green = 0.5; ball[7].blue = 0.0;
	ball[4].z = 3.8; ball[4].x = -7.6; ball[8].red = 0.64; ball[8].green = 0.16; ball[8].blue = 0.16;
	ball[5].z = 4.4; ball[5].x = -7.6; ball[9].red = 0.58; ball[9].green = 0; ball[9].blue = 0.83;
	for (int i = 0; i < 10; i++)
	{
		ball[i].draw = true;
		ball[i].speed = SPEED;
		ball[i].circularMotionIsActive = false;
	}
}
void changeBallState(Ball * ball)
{
	ball->draw = false;
	ball->x = -50;
	ball->z = -50;
}
void blackHole(Ball *ball) {
	if ((ball->x >= 0.13 && ball->x <= 0.26 && ball->z <= 0.35 && ball->z >= -0.11) || (ball->x >= -2.14 && ball->x <= -1.7 && ball->z >= 5.7 && ball->z <= 6.57)) {
		score += 15;
		changeBallState(ball);
	}
	else if (ball->x >= -4.3 && ball->x <= -3.4 && ball->z <= 2.3 && ball->z >= 2) {
		score -= 15;
		changeBallState(ball);
	}
	
}
void drawAllBalls() {
	int i;
	for (i = 0; i < 10; i++){
		blackHole(&ball[i]);
		if (ball[i].draw == true)
			drawBall(ball[i], i);

	}
}
void draw()
{
	//int i;
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -15);
	glRotatef(rot_x, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);
	/*********/
#pragma region decorateEnvoierment
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

	glNormal3f(0, 1, 0);
	glTranslatef(-4, 0.1, 2.2);
	glColor3f(0.64, 0.16, 0.16);
	drawCircle();

	glTranslatef(4, -0.1, -2.2);//0000000

#pragma endregion
	//print the selected ball
	sprintf_s(printContainer, "Selected ball : %d", (char)curBallIndex);
	printPointer = printContainer;
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(0, 5, 3);
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *printPointer); while (*(++printPointer));
	sprintf_s(printContainer, "your score is : %d", (char)score);
	printPointer = printContainer;
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(2, 4, 2);
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *printPointer); while (*(++printPointer));
	drawAllBalls();
	if (score >= 50) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
		glLoadIdentity();
		glTranslatef(-7, 0, -15);
		glRotatef(rot_x, 0, 1, 0);
		glRotatef(rot_z, 0, 0, 1);
		sprintf_s(printContainer, "GAME OVER", (char)score);
		printPointer = printContainer;
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos3f(2, 4, 2);
		do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *printPointer); while (*(++printPointer));

		sprintf_s(printContainer, "your score is : %d", (char)score);
		printPointer = printContainer;
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos3f(2, 0, 2);
	
		do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *printPointer); while (*(++printPointer));
		sprintf_s(printContainer, "press ESC to exit", (char)score);
		printPointer = printContainer;
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos3f(1, 0, 1);
		do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *printPointer); while (*(++printPointer));
		rot_z -= 5;
		rot_z %= 360;
	}
	glutSwapBuffers();			// display the output
}
void changeBallControl(int ballNum) {
	if (curBallIndex >= 0) {
		ball[curBallIndex].blue = ballForRefrence.blue;
		ball[curBallIndex].blue = ballForRefrence.blue;
		ball[curBallIndex].green = ballForRefrence.green;
		ball[curBallIndex].red = ballForRefrence.red;
		ball[curBallIndex].active = false;
	}
	ballForRefrence = ball[ballNum];
	curBallIndex = ballNum;
	ball[ballNum].red = 1;
	ball[ballNum].blue = 1;
	ball[ballNum].green = 1;
	ball[ballNum].active = true;
	//glutPostRedisplay();
}
double calcVelocity(Ball *ball) {
	if (ball->speed >= 0.0) {
		ball->speed -= FRICTION_MODIFIER;
	}
	printf("\nball.speed: %lf", ball->speed);

	return ball->speed;
}
int checkCollision(int i)
{
	int j;
	for (j = 0; j < 10; j++)
	{
		if (j != i) {
			if (ball[i].x >= ball[j].x - 0.58 && ball[i].x <= ball[j].x + 0.58 && ball[i].z >= ball[j].z - 0.58 && ball[i].z <= ball[j].z + 0.58)
				return 0;
		}

	}
	return 1;
}

void idle() {
	for (int i = 0; i < 10; i++) {
		if (ball[i].active == true) {
			if (ball[i].left == true && checkCollision(i) == 1 && ball[i].z >= -1.0 && ball[i].speed > 0.001) {

				ball[i].z -= calcVelocity(&ball[i]);
				printf("\nball[%d].x: %.2f, ball[%d].z: %.2f", i, ball[i].x, i, ball[i].z);
			}
			else {
				ball[i].left = false;
				ball[i].z += 0.02;
			}
			if (ball[i].right == true && checkCollision(i) == 1 && ball[i].z <= 7.5 && ball[i].speed > 0.001) {

				ball[i].z += calcVelocity(&ball[i]);
				printf("\nball[%d].x: %.2f, ball[%d].z: %.2f", i, ball[i].x, i, ball[i].z);
			}
			else {
				ball[i].right = false;
				ball[i].z -= 0.02;
			}
			if (ball[i].up == true && checkCollision(i) == 1 && ball[i].x <= 0.7 && ball[i].speed > 0.001) {

				ball[i].x += calcVelocity(&ball[i]);
				printf("\nball[%d].x: %.2f, ball[%d].z: %.2f", i, ball[i].x, i, ball[i].z);
			}
			else {
				ball[i].up = false;
				ball[i].x -= 0.02;
			}
			if (ball[i].down == true && checkCollision(i) == 1 && ball[i].x >= -8.2 && ball[i].speed > 0.001) {

				ball[i].x -= calcVelocity(&ball[i]);
				printf("\nball[%d].x: %.2f, ball[%d].z: %.2f", i, ball[i].x, i, ball[i].z);
			}
			else {
				ball[i].down = false;
				ball[i].x += 0.02;
			}
			if (ball[i].circularMotionIsActive == true) {
				if (angle < 2 * M_PI && checkCollision(i) == 1) {
					ball[i].x = originX + cos(angle)*radius;
					ball[i].z = originZ + sin(angle)*radius;
					printf("\noriginX: %.2lf originY: %.2lf -- ball[%d].x = %.2lf, ball[%d].z = %.2lf angle = %.2lf", originX, originZ, i, ball[i].x, i, ball[i].z, angle);
					angle += calcVelocity(&ball[i]) * 5;
				}
				if (angle >= 2 * M_PI) angle = 0.0;
			}

		}


	}
	
	glutPostRedisplay();
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
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
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

	if (key == 27) exit(1);
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
		for (int i = 0; i < 10; i++) {
			if (ball[i].active == true)
			{
				ball[i].speed = SPEED;
				ball[i].circularMotionIsActive = false;
				ball[i].left = false;
				ball[i].right = false;
				ball[i].up = true;
				ball[i].down = false;
			}
		}
	}
	if (key == KEY_DOWN) {
		for (int i = 0; i < 10; i++) {
			if (ball[i].active == true)
			{
				ball[i].speed = SPEED;
				ball[i].circularMotionIsActive = false;
				ball[i].left = false;
				ball[i].right = false;
				ball[i].up = false;
				ball[i].down = true;
			}
		}
	}
	if (key == KEY_LEFT) {
		for (int i = 0; i < 10; i++) {
			if (ball[i].active == true)
			{
				ball[i].speed = SPEED;
				ball[i].circularMotionIsActive = false;
				ball[i].left = true;
				ball[i].right = false;
				ball[i].up = false;
				ball[i].down = false;
			}
		}
	}
	if (key == KEY_RIGHT) {
		for (int i = 0; i < 10; i++) {
			if (ball[i].active == true)
			{
				ball[i].speed = SPEED;
				ball[i].circularMotionIsActive = false;
				ball[i].left = false;
				ball[i].right = true;
				ball[i].up = false;
				ball[i].down = false;
			}
		}
	}
	if (key == KEY_ROTATE)
	{
		for (int i = 0; i < 10; i++) {
			if (ball[i].active == true)
			{
				ball[i].speed = SPEED;
				originX = ball[i].x;
				originZ = ball[i].z;
				ball[i].circularMotionIsActive = true;
			}

		}

	}

	draw();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	// RGB display, double-buffered, with Z-Buffer
	glutInitWindowSize(500, 500);					// 500 x 500 pixels
	glutCreateWindow("3D");
	glutDisplayFunc(draw);// Set the display function
	glutKeyboardFunc(keyboard);// Set the keyboard function
	glutIdleFunc(idle);
	initBallParams();
	init();
	glutMainLoop();// Start the main event loop
}
