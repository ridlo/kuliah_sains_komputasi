// Copyleft (c) Ridlo W. Wibowo
// Simple Spreading Fire
// Ref: Tharindra Galahena Code, game_of_life cellular automata
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <fstream>

#define MAX 501

using namespace std;

int grid [MAX][MAX];
int grid2[MAX][MAX];
bool f = false;
int tpm = 200;
double burnProb = 0.25;

double unirand(){ return (double)rand()/(double)RAND_MAX;}

void inisiasi();

void menu(int t){
	tpm = t;
	glutPostRedisplay();
}

void printm(){
    int m=0;
    ofstream out("fire.txt");
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            if (grid[i][j] == 1){ m++;}
            out << grid[i][j] << " ";}
        out << "\n";}
    out.close();
    cout << "tree = " << m << endl;
    cout << "persentase = " << (double)m*100./((double)MAX*MAX) << endl;
}

int check(int i, int j){
    // with periodic boundary 
    int s = 0;
	i += MAX;
	j += MAX;
    if (grid[i%MAX][j%MAX] == 1){
	    if(grid[(i - 1)%MAX][(j - 1)%MAX] == 2 && unirand() < burnProb){ s++;}
	    if(grid[(i - 1)%MAX][(j    )%MAX] == 2 && unirand() < burnProb){ s++;} 
	    if(grid[(i - 1)%MAX][(j + 1)%MAX] == 2 && unirand() < burnProb){ s++;}
	
	    if(grid[(i    )%MAX][(j - 1)%MAX] == 2 && unirand() < burnProb){ s++;} 
	    if(grid[(i    )%MAX][(j + 1)%MAX] == 2 && unirand() < burnProb){ s++;}
	
	    if(grid[(i + 1)%MAX][(j - 1)%MAX] == 2 && unirand() < burnProb){ s++;} 
	    if(grid[(i + 1)%MAX][(j    )%MAX] == 2 && unirand() < burnProb){ s++;} 
	    if(grid[(i + 1)%MAX][(j + 1)%MAX] == 2 && unirand() < burnProb){ s++;}

        return s;
	}
    else if (grid[i%MAX][j%MAX] == 2){return 999;}
    else{ return 888;}	
}

void copy(){
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			grid[i][j] = grid2[i][j];
		}
	}
}

void spread(){ // update
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
            int s = check(i, j);
            if (s == 0){ grid2[i][j] = 1;} // ada pohon dan gak kebakar
            if (s > 0 && s < 9){ grid2[i][j] = 2;} // pohon terbakar
            if (s == 999){ grid2[i][j] = 0;} // udah kebakar jadi empty
            if (s == 888){ grid2[i][j] = 0;} // tetep empty
		}
	}
	copy();
}

void par(float x1, float x2, float y1, float y2, int val){
	if (val == 0){glColor3f(1.0, 1.0, 1.0);}
    else if(val == 1){ glColor3f(0.0, 1.0, 0.0);}
    else{glColor3f(1.0, 0.0, 0.0);}

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

	glTranslatef(0.0, 0.0, -67.0);
	
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
				par(-25.0 + 0.1 * j,
					-25.0 + 0.1 * (j + 1),
					25.0 - 0.1 * i,
					25.0 - 0.1 * (i - 1),
                    grid[i][j]);
		}
	}
	
	glutSwapBuffers();
}

void myIdleFunc(int a) {
	spread();
	glutPostRedisplay();
	if(f) glutTimerFunc(tpm, myIdleFunc, 0);
}

void inisiasi(){
	for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            grid2[i][j] = 1;
        }
    }
    grid2[250][250] =  2;

    copy();
}

void keyboard(unsigned char key, int x, int y){
	if(key == 27) {		
		exit(0);	
	}else if((char)key == 'a'){
		if(!f) glutTimerFunc(tpm, myIdleFunc, 0);
		f = true;
	}else if((char)key == 's'){
		spread();
		glutPostRedisplay();
	}else if((char)key == 'd'){
		f = false;
	}else if((char)key == 'f'){
		inisiasi();
        f = false;
		glutPostRedisplay();
	}else if((char)key == 'p'){
        f = false;
        printm();
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

	inisiasi();
	
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(500,0);
	glutCreateWindow("Spreading Fire");
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
