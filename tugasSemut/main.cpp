/**********************************************/
/* ants movement                              */
/* Copyleft (c) 2012. Ridlo W. Wibowo         */
/**********************************************/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <fstream>
#define MAX 17
using namespace std;

double grid [MAX][MAX];
double grid2[MAX][MAX];
bool f = false;
int tpm = 200;
double boredProb = 0.1;
double maxPher = 10.;

double unirand(){ return (double)rand()/(double)RAND_MAX;}

void copy(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            grid[i][j] = grid2[i][j];}}
}

void inisiasi(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            grid2[i][j] = 0.0;
        }
    }
    grid2[8][8] = 10.;
    copy();
}

void par(float x1, float x2, float y1, float y2, float val){
    glColor3f(val/maxPher, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y1, 0.0);
    glVertex3f(x2, y2, 0.0);
    glVertex3f(x1, y2, 0.0);
    glEnd;
}   

void jalan(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            if (grid[i][j] > 0.0){grid2[i][j] -= 0.1;}
        }
    }
    copy();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -22.0);

    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            par(-6.0 + 0.7*j + 0.1,
                -6.0 + 0.7*(j + 1),
                 6.0 - 0.7*i + 0.1,
                 6.0 - 0.7*(i - 1),
                 grid[i][j]);
        }
    }
    glutSwapBuffers();
}

void menu(int t){
    tpm = t;
    glutPostRedisplay();
}

void myIdleFunc(int a){
    jalan();
    glutPostRedisplay();
    if (f) glutTimerFunc(tpm, myIdleFunc, 0);
}

void keyboard(unsigned char key, int x, int y){
    if (key==27){ 
        exit(0);
    } else if ((char)key == 'a'){
        if (!f) glutTimerFunc(tpm, myIdleFunc, 0);
        f = true;
    } else if ((char)key == 's'){
        jalan();
        glutPostRedisplay();
    } else if ((char)key == 'd'){
        f = false;
    } else if ((char)key == 'f'){
        inisiasi();
        f = false;
        glutPostRedisplay();
    }
}

void init(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    GLfloat acolor[] = {1.4, 1.4, 1.4, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, acolor);
}

void Reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 0.1, 200.0);
}

int main(int argc, char** argv){
    inisiasi();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(500, 0);
    glutCreateWindow("Ants Movement");
    
    glutCreateMenu(menu);
    glutAddMenuEntry("20", 20);
    glutAddMenuEntry("40", 40);
    glutAddMenuEntry("60", 60);
    glutAddMenuEntry("100", 100);
    glutAddMenuEntry("150", 150);
    glutAddMenuEntry("200", 200);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
