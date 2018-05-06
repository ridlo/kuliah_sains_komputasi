/******************************************************************************/
/* myFirstFractal -> Phythagoras Fractal                                      */
/* Copyleft (c) 2012. Ridlo W. Wibowo                                         */
/* Written in C++ with OpenGL                                                 */
/* Absolutely no warranty implied or expressed                                */
/******************************************************************************/

#include<GL/glut.h>
#include<cmath>
#define PI 3.1415926535897932384626433832795

void DrawLine(float x1, float y1, float x2, float y2) {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
	glEnd();
}

void DrawLineFlower(float x1, float y1, float x2, float y2){
    DrawLine(x1, y1, x2, y2);
    float Radius = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    glBegin(GL_POLYGON);
        glVertex3f(x2-0.1*Radius, y2, 0.0);
        glVertex3f(x2, y2+0.1*Radius, 0.0);
        glVertex3f(x2+0.1*Radius, y2, 0.0);
        glVertex3f(x2, y2-0.1*Radius, 0.0);
    glEnd();       
}

void DrawTree(float x, float y, float length, float theta, float dTheta, int orde){
    float x0 = x;
    float y0 = y;
    float x1, y1, x2, y2;
    float mTheta = theta+dTheta;
    float nTheta = theta-dTheta;
    x1 = x0 + length*cos(mTheta);
    y1 = y0 + length*sin(mTheta);
    x2 = x0 + length*cos(nTheta);
    y2 = y0 + length*sin(nTheta);
    if (orde == 0){
        DrawLineFlower(x0, y0, x1, y1);
        DrawLineFlower(x0, y0, x2, y2);}
    else{
        DrawLine(x0, y0, x1, y1);
        DrawLine(x0, y0, x2, y2);
        length = length/sqrt(2.);
        DrawTree(x1, y1, length, mTheta, dTheta, orde-1);
        DrawTree(x2, y2, length, nTheta, dTheta, orde-1);}
}

void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    DrawLine(0.5, 0.01, 0.5, 0.21);
    DrawTree(0.5, 0.21, 0.15, PI/2, PI/4, 10);
    glFlush();
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Fractal Phythagoras");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}
