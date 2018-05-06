#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <fstream>

#define MAX 60

using namespace std;

char grid [MAX][MAX];
char grid2[MAX][MAX];
bool f = false;
int tpm = 200;

void copy_file();

void menu(int t){
	tpm = t;
	glutPostRedisplay();
}
int num(int i, int j){
	int n = 0;
	i += MAX;
	j += MAX;
	if(grid[(i - 1)%MAX][(j - 1)%MAX] == '1') n++; 
	if(grid[(i - 1)%MAX][(j    )%MAX] == '1') n++; 
	if(grid[(i - 1)%MAX][(j + 1)%MAX] == '1') n++; 
	
	if(grid[(i    )%MAX][(j - 1)%MAX] == '1') n++; 
	if(grid[(i    )%MAX][(j + 1)%MAX] == '1') n++; 
	
	if(grid[(i + 1)%MAX][(j - 1)%MAX] == '1') n++; 
	if(grid[(i + 1)%MAX][(j    )%MAX] == '1') n++; 
	if(grid[(i + 1)%MAX][(j + 1)%MAX] == '1') n++;
	
	return n;
}
void copy(){
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			grid[i][j] = grid2[i][j];
		}
	}
}
void move(){
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			int n = num(i, j);
			if(grid[i][j] == '1'){
				if( n < 2 || n > 3) grid2[i][j] = '0';
			}else{
				if( n == 3) grid2[i][j] = '1';
			}
		}
	}
	copy();
}

void par(float x1, float x2, float y1, float y2){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);

	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	glTranslatef(0.0, 0.0, -22.0);
	
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			if(grid[i][j] == '1')
				par(-8.0 + 0.3 * j + 0.1,
					-8.0 + 0.3 * (j + 1),
					8.0 - 0.3 * i + 0.1,
					8.0 - 0.3 * (i - 1));
		}
	}
	
	glutSwapBuffers();
}
void myIdleFunc(int a) {
	move();
	glutPostRedisplay();
	if(f) glutTimerFunc(tpm, myIdleFunc, 0);
}
void copy_file(){
	int i = 0;
	int j = 0;
	
	ifstream myReadFile;
	myReadFile.open("grid");
	char c;
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> c;
			if(j == 59){
				i++;
				j = 0;
			}else{
				if(c == '0') grid2[i][j] = '0';	
				else grid2[i][j] = '1';	
				j++;
			}
		}
	}
	myReadFile.close();
	copy();
}
void keyboard(unsigned char key, int x, int y){
	if(key == 27) {		
		exit(0);	
	}else if((char)key == 'a'){
		if(!f) glutTimerFunc(tpm, myIdleFunc, 0);
		f = true;
	}else if((char)key == 's'){
		move();
		glutPostRedisplay();
	}else if((char)key == 'd'){
		f = false;
	}else if((char)key == 'f'){
		copy_file();
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
	glLoadIdentity ();
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

	copy_file();
	
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(500,0);
	glutCreateWindow("game_of_life");
	glutCreateMenu(menu);

	glutAddMenuEntry( "20",  20);
	glutAddMenuEntry( "40",  40);
	glutAddMenuEntry( "60",  60);
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
