// Copyleft (c) Ridlo W. Wibowo
// Simut muuut muut
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <fstream>
#include <time.h>
#define MAX 17
#define maxSemut 20
using namespace std;

int grid [MAX][MAX];
int grid2[MAX][MAX];
int strong[MAX][MAX];
bool f = false;
int tpm = 100;
double boredProb = 0.1;
int maxPher = 200;
/* N  = 0, NE = 1, E  = 2, SE = 3, S  = 4, SW = 5, W  = 6, NW = 7 */

double unirand(){ return (double)rand()/(double)RAND_MAX;}

int getStrong(int x, int y, int direc){ 
    int m = x+MAX; int n = y+MAX; int kuat=0; int arahbaru = direc;
    if (direc == 0){ 
            if (grid[m%MAX][(n+1)%MAX] > kuat){kuat = grid[m%MAX][(n+1)%MAX]; arahbaru=0;}
            if (grid[(m-1)%MAX][n%MAX] > kuat){ kuat = grid[(m-1)%MAX][n%MAX] ; arahbaru = 6;}
            if (grid[(m-1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n+1)%MAX] ; arahbaru = 7;}
            if (grid[(m+1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n+1)%MAX] ; arahbaru = 1;}
            if (grid[(m+1)%MAX][n%MAX] > kuat){ kuat = grid[(m+1)%MAX][n%MAX] ; arahbaru = 2;}
    }
    if (direc == 1){
            if (grid[m%MAX][(n+1)%MAX] > kuat){kuat = grid[m%MAX][(n+1)%MAX]; arahbaru = 0;}
            if (grid[(m+1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n+1)%MAX] ; arahbaru = 1;}
            if (grid[(m-1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n+1)%MAX] ; arahbaru = 7;}
            if (grid[(m+1)%MAX][n%MAX] > kuat){ kuat = grid[(m+1)%MAX][n%MAX] ; arahbaru = 2;}
            if (grid[(m+1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n-1)%MAX] ; arahbaru = 3;}
    }
    if (direc == 2){
            if (grid[m%MAX][(n+1)%MAX] > kuat){kuat = grid[m%MAX][(n+1)%MAX]; arahbaru = 0;}
            if (grid[(m+1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n+1)%MAX] ; arahbaru = 1;}
            if (grid[(m+1)%MAX][n%MAX] > kuat){ kuat = grid[(m+1)%MAX][n%MAX] ; arahbaru = 2;}
            if (grid[(m+1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n-1)%MAX] ; arahbaru = 3;}
            if (grid[m%MAX][(n-1)%MAX] > kuat){ kuat = grid[m%MAX][(n-1)%MAX] ; arahbaru = 4;}
    }
    if (direc == 3){
            if (grid[(m+1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n+1)%MAX] ; arahbaru = 1;}
            if (grid[(m+1)%MAX][n%MAX] > kuat){ kuat = grid[(m+1)%MAX][n%MAX] ; arahbaru = 2;}
            if (grid[(m+1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n-1)%MAX] ; arahbaru = 3;}
            if (grid[m%MAX][(n-1)%MAX] > kuat){ kuat = grid[m%MAX][(n-1)%MAX] ; arahbaru = 4;}
            if (grid[(m-1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n-1)%MAX] ; arahbaru = 5;}
    }
    if (direc == 4){
            if (grid[(m+1)%MAX][n%MAX] > kuat){ kuat = grid[(m+1)%MAX][n%MAX] ; arahbaru = 2;}
            if (grid[(m+1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n-1)%MAX] ; arahbaru = 3;}
            if (grid[m%MAX][(n-1)%MAX] > kuat){ kuat = grid[m%MAX][(n-1)%MAX] ; arahbaru = 4;}
            if (grid[(m-1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n-1)%MAX] ; arahbaru = 5;}
            if (grid[(m-1)%MAX][n%MAX] > kuat){ kuat = grid[(m-1)%MAX][n%MAX] ; arahbaru = 6;}
    }
    if (direc == 5){
            if (grid[(m+1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n-1)%MAX] ; arahbaru = 3;}
            if (grid[m%MAX][(n-1)%MAX] > kuat){ kuat = grid[m%MAX][(n-1)%MAX] ; arahbaru = 4;}
            if (grid[(m-1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n-1)%MAX] ; arahbaru = 5;}
            if (grid[(m-1)%MAX][n%MAX] > kuat){ kuat = grid[(m-1)%MAX][n%MAX] ; arahbaru = 6;}
            if (grid[(m-1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n+1)%MAX] ; arahbaru = 7;}
    }
    if (direc == 6){
            if (grid[m%MAX][(n-1)%MAX] > kuat){ kuat = grid[m%MAX][(n-1)%MAX] ; arahbaru = 4;}
            if (grid[(m-1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n-1)%MAX] ; arahbaru = 5;}
            if (grid[(m-1)%MAX][n%MAX] > kuat){ kuat = grid[(m-1)%MAX][n%MAX] ; arahbaru = 6;}
            if (grid[(m-1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n+1)%MAX] ; arahbaru = 7;}
            if (grid[m%MAX][(n+1)%MAX] > kuat){kuat = grid[m%MAX][(n+1)%MAX]; arahbaru = 0;}
    }
    if (direc == 7){
            if (grid[(m-1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n-1)%MAX] ; arahbaru = 5;}
            if (grid[(m-1)%MAX][n%MAX] > kuat){ kuat = grid[(m-1)%MAX][n%MAX] ; arahbaru = 6;}
            if (grid[(m-1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n+1)%MAX] ; arahbaru = 7;}
            if (grid[m%MAX][(n+1)%MAX] > kuat){kuat = grid[m%MAX][(n+1)%MAX]; arahbaru = 0;}
            if (grid[(m+1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n+1)%MAX] ; arahbaru = 1;}
    }
    
    return arahbaru;
    /*
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            int m = i + MAX; int n = j + MAX; int kuat=0; //strong[i][j] = 0;
            if (grid[m%MAX][(n+1)%MAX] > kuat){kuat = grid[m%MAX][(n+1)%MAX]; strong[i][j] = 0;}
            if (grid[(m+1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n+1)%MAX] ; strong[i][j] = 1;}
            if (grid[(m+1)%MAX][n%MAX] > kuat){ kuat = grid[(m+1)%MAX][n%MAX] ; strong[i][j] = 2;}
            if (grid[(m+1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m+1)%MAX][(n-1)%MAX] ; strong[i][j] = 3;}
            if (grid[m%MAX][(n-1)%MAX] > kuat){ kuat = grid[m%MAX][(n-1)%MAX] ; strong[i][j] = 4;}
            if (grid[(m-1)%MAX][(n-1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n-1)%MAX] ; strong[i][j] = 5;}
            if (grid[(m-1)%MAX][n%MAX] > kuat){ kuat = grid[(m-1)%MAX][n%MAX] ; strong[i][j] = 6;}
            if (grid[(m-1)%MAX][(n+1)%MAX] > kuat){ kuat = grid[(m-1)%MAX][(n+1)%MAX] ; strong[i][j] = 7;}
        }
    }
    */
    
}

class varSemut{
    public:
        int x, y, arah;
        void set_value(int, int, int);
        void sensing();
        void buangpher();
} semut[maxSemut];

void varSemut::set_value(int a, int b, int c){x = (a+MAX)%MAX; y = (b+MAX)%MAX; arah = c;}

void varSemut::buangpher(){
    if (grid2[x][y] < 50){
        grid2[x][y] = grid2[x][y] + 2;
    }
}

void varSemut::sensing(){
    int arahnew = getStrong(x, y, arah);
    if (arahnew == 0){ 
        x = x; 
        y = (y+MAX+1)%MAX;
        arah = arahnew;
    }
    if (arahnew == 1){ 
        x = (x+MAX+1)%MAX; 
        y = (y+MAX+1)%MAX;
        arah = arahnew;
    }
    if (arahnew == 2){ 
        x = (x+MAX+1)%MAX; 
        y = y;
        arah = arahnew;
    }
    if (arahnew == 3){ 
        x = (x+MAX+1)%MAX; 
        y = (y+MAX-1)%MAX;
        arah = arahnew;
    }
    if (arahnew == 4){ 
        x = x; 
        y = (y+MAX-1)%MAX;
        arah = arahnew;
    }
    if (arahnew == 5){ 
        x = (x+MAX-1)%MAX; 
        y = (y+MAX-1)%MAX;
        arah = arahnew;
    }
    if (arahnew == 6){ 
        x = (x+MAX-1)%MAX; 
        y = y;
        arah = arahnew;
    }
    if (arahnew == 7){ 
        x = (x+MAX-1)%MAX; 
        y = (y+MAX+1)%MAX;
        arah = arahnew;
    }
}

void inisiasi();

void menu(int t){
	tpm = t;
	glutPostRedisplay();
}

void copy(){
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			grid[i][j] = grid2[i][j];}}
}

void mlaku(){
    for (int k=0;k<maxSemut;k++){
        if (unirand() > boredProb){
            semut[k].buangpher();
            semut[k].sensing();
        }
        else {
            semut[k].buangpher();
            semut[k].set_value(semut[k].x + (-1 + (rand()%3)), semut[k].y + (-1 + (rand()%3)), rand()%8); //semutnya bosen
        }
    }
}

void jalan(){
    for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            if (grid[i][j] > 0){ grid2[i][j] -= 1;}
        }
    }
    grid2[8][8] = 100;
    grid2[8][7] = 100;
    grid2[8][9] = 100;
    //grid2[7][8] = 100;
    //grid2[9][8] = 100;
    mlaku();
    copy();
}

void par(float x1, float x2, float y1, float y2, int val){
    glColor3f(1.0, 1.0, (float)val/(float)maxPher);
	glBegin(GL_QUADS);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glEnd();
}

void sem(float x1, float x2, float y1, float y2){
    glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glEnd();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -22.0);
    for (int k=0;k<maxSemut;k++){
        sem(-6.0 + 0.7 * semut[k].y + 0.15,
            -6.0 + 0.7 * (semut[k].y + 1) - 0.075,
             6.0 - 0.7 * semut[k].x + 0.15,
             6.0 - 0.7 * (semut[k].x - 1) - 0.075);
    }
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
				par(-6.0 + 0.7 * j + 0.1,
					-6.0 + 0.7 * (j + 1),
					6.0 - 0.7 * i + 0.1,
					6.0 - 0.7 * (i - 1),
                    grid[i][j]);
		}
	}
	glutSwapBuffers();
}

void myIdleFunc(int a) {
	jalan();
	glutPostRedisplay();
	if(f) glutTimerFunc(tpm, myIdleFunc, 0);
}

void inisiasi(){
	for (int i=0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            grid2[i][j] = 0;
        }
    }
    grid2[8][8] = 100;
    grid2[8][7] = 100;
    grid2[8][9] = 100;
    //grid2[7][8] = 100;
    //grid2[9][8] = 100;
    copy();
    for (int k=0;k<maxSemut;k++){
        semut[k].set_value(rand()%MAX, rand()%MAX, rand()%8);
    }
}

void keyboard(unsigned char key, int x, int y){
	if(key == 27) {		
		exit(0);	
	}else if((char)key == 'a'){
		if(!f) glutTimerFunc(tpm, myIdleFunc, 0);
		f = true;
	}else if((char)key == 's'){
		jalan();
		glutPostRedisplay();
	}else if((char)key == 'd'){
		f = false;
	}else if((char)key == 'f'){
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
	srand(time(NULL));
    inisiasi();
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(500,0);
	glutCreateWindow("Semut muutmuut");
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
