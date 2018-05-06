/******************************************************************************/
/* koch snowflake                                                             */
/* Copyleft (c) 2012. Ridlo W. Wibowo                                         */
/* Written in C++ with OpenGL                                                 */
/* Absolutely no warranty implied or expressed                                */
/******************************************************************************/

#include<GL/glut.h>
#include<cmath>
#define PI 3.1415926535897932384626433832795

void DrawLine(float x1, float y1, float x2, float y2) {
	glColor3f(0.1, 0.5, 1.0);
	glBegin(GL_LINES);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
	glEnd();
}

void RecurDraw(float xa, float ya, float xb, float yb, float theta, int orde){
    float dy = fabs(yb - ya);
    float dx = fabs(xb - xa);
    float newLength = sqrt(dx*dx + dy*dy)/3.;
    float dtheta = PI/3.;
    float x1, y1, x2, y2, x3, y3;
    float mtheta = theta + dtheta;
    float ntheta = theta - dtheta;
    x1 = xa + newLength*cos(theta); y1 = ya + newLength*sin(theta);
    x2 = x1 + newLength*cos(mtheta); y2 = y1 + newLength*sin(mtheta);
    x3 = x2 + newLength*cos(ntheta); y3 = y2 + newLength*sin(ntheta);
    if (orde == 0){
        DrawLine(xa, ya, x1, y1); 
        DrawLine(x1, y1, x2, y2); 
        DrawLine(x2, y2, x3, y3); 
        DrawLine(x3, y3, xb, yb);}
    else{
        RecurDraw(xa, ya, x1, y1, theta, orde-1);
        RecurDraw(x1, y1, x2, y2, mtheta, orde-1);
        RecurDraw(x2, y2, x3, y3, ntheta, orde-1);
        RecurDraw(x3, y3, xb, yb, theta, orde-1);}
}
    
void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    RecurDraw(0.2, 0.6, 0.8, 0.6, 0., 3);
    RecurDraw(0.8, 0.6, 0.5, 0.08038475772933673, 4.*PI/3., 4); 
    RecurDraw(0.5, 0.08038475772933673, 0.2, 0.6, 2.*PI/3., 4);
    glFlush();
}

void Initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
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
