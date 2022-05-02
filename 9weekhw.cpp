#include <windows.h>
#include <iostream>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

using namespace std;

#define		Window_Width	800
#define		Window_Height	800

int			point[100][2];
int			num = 0;
int			sum = 1;
float		p = 100.0;
float fat(int n)
{
	if (n <= 1)
		return sum;
	sum *= n;
	fat(n - 1);
}

float combi(int num, int i)
{
	float value = 0.0;
	float v1 = abs(fat(num));
	sum = 1;
	float v2 = abs(fat(num - i));
	sum = 1;
	float v3 = abs(fat(i));
	sum = 1;

	value = v1 / (v2 * v3);

	return value;
}

float BB(int num, int i, float time)
{
	float value = 0.0;
	value = combi(num - 1, i) * pow(1 - time, num - i - 1) * pow(time, i);
	//combi(num, i) *
	return value;
}
/*
int main(void)
{
	int x1[3] = { 0,100,100 };
	int y1[3] = { 0,100,0 };
	float t[3] = { 0,0.5,1.0 };
	float com, p1, p2, val;
	float sum1 = 0;
	float sum2 = 0;
	float sum3 = 0;
	cout << pow(0.1, 1) << '\n';

	for (int i = 0; i <= 2; i++)
	{
		sum1 = combi(2, i);
		sum2 = pow(1 - t[2], 2 - i);
		sum3 = pow(t[2], i);
		cout << i + 1 << "번 째 값 : " << '\n';
		cout << "조합 값 : " << sum1 << '\n';
		cout << "제곱 값1 : " << sum2 << '\n';
		cout << "제곱 값2 : " << sum3 << '\n' << '\n';
		cout << "BB 값 : " << sum1 * sum2 * sum3 << '\n' << '\n' << '\n';
	}


	return 0;
}
*/

void Draw_Bezier_Curve(void) {

	float time;
	float dtime;
	float cx, cy;
	float sumx, sumy;
	dtime = 1.0 / p;

	glBegin(GL_LINE_STRIP);

	for (time = 0.0; time <= 1.0; time += dtime)
	{
		sumx = 0;
		sumy = 0;

		for (int i = 0; i < num; i++)
		{
			sumx += BB(num, i, time) * point[i][0] ; // BB = B
			sumy += BB(num, i, time) * point[i][1] ; // BB = B

		}
		//sumx, sumy = C(t)
		cout << sumx << "	" << sumy << '\n';
		glVertex2f(sumx, sumy);
	}
	
	glEnd();

}
void Draw_Control_Points(void) {

	glPointSize(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int k = 0; k < num; k++) {
		glVertex2f(point[k][0], point[k][1]);
	}
	glEnd();

}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);

	if (num >= 1)
		Draw_Control_Points();
	if (num >= 2)
		Draw_Bezier_Curve();

	glFlush();
	glutSwapBuffers();
}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glLoadIdentity();
	gluOrtho2D(0, Window_Width, 0, Window_Height);
	//point[0][0] = 100;
	//point[0][1] = 100;
	//point[1][0] = 200;
	//point[1][1] = 200;
	//point[2][0] = 200;
	//point[2][1] = 100;
	//num = 3;
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		point[num][0] = x;
		point[num][1] = Window_Height - y;
		num++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		num = 0;
	}
	glutPostRedisplay();
	RenderScene();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Bezier Curve");
	init();
	glutDisplayFunc(RenderScene);
	glutMouseFunc(mouse);
	glutMainLoop();

}

