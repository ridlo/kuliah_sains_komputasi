/**************************************************/
/* pollen.cpp                                     */
/* copyleft (c) 2012. Ridlo W. Wibowo             */
/**************************************************/
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int n=100;
double x[100], y[100], z[100];
double dx, dy, dz;
double l, theta, phi;
double unirand(){ return (double)rand()/(double)RAND_MAX;}

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void move(){
    for (int i=0;i<n;i++){
        phi = 2.*M_PI*unirand();
        theta = acos(1. - 2.*unirand());
        l = 0.05*unirand();
        dx = l*sin(theta)*cos(phi);
        dy = l*sin(theta)*sin(phi);
        dz = l*cos(theta);
        
        x[i] = fmod((x[i] + dx + 5.),5.);
        y[i] = fmod((y[i] + dy + 5.),5.);
        z[i] = fmod((z[i] + dz + 5.),5.);
    }
}

void myIdleFunc(int a) {
    move();
    glutPostRedisplay();
    glutTimerFunc(100, myIdleFunc, 0);
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    
    glutWireCube(5.0);
    for (int i=0;i<n;i++){
        glPushMatrix();
        glTranslatef(-2.5 + x[i], -2.5 + y[i], -2.5 + z[i]);
        glutSolidSphere(0.05, 10, 8);
        glPopMatrix();
    }
    glutSwapBuffers();
}

void inisiasi(){
    for (int i=0;i<n;i++){
        x[i] = 5.*unirand();
        y[i] = 5.*unirand();
        z[i] = 5.*unirand();
    }
}


void reshape(int w, int h){
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, (GLfloat) w/ (GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.0, 1.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (700, 700);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("pollen brownian motion");
    init ();
    srand(time(NULL));
    inisiasi();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(100, myIdleFunc, 0);

    glutMainLoop();
    return 0;
}
