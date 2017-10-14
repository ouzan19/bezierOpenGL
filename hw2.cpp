#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;
class point{
	public :
	float x;
	float  y;
	float z;
	point() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		}
	point operator*(float d){
		point temp;
		temp.x = d*this->x;
		temp.y = d*this->y;
		temp.z = d*this->z;
		return temp;
		
		}

	point operator+(point d){
		point temp;
		temp.x = this->x + d.x;
		temp.y = this->y + d.y;
		temp.z = this->z + d.z;
		return temp;
		
		}
};

class color{
	public :
	int r;
	int g;
	int b;

};
int main_window;
int sampleR =0,sampleC =0,M=0,N=0,K=0,RotAngle=0,tx=0,ty=0,tz=0,mode=1,selectedX=0,selectedY=0,oldX=0,oldY=0,valid=0,lookX=0,lookY=0;
bool changed=false;
float udiff,vdiff;
vector< vector<point> > points;
vector< vector<point> > samples;
vector<color> palette;
void readFile(string filename){
	
	fstream f;
	f.open(filename.c_str());
	f >> sampleR;
	f >> sampleC;
	f >> M;
	f >> N;
	
	for(int i=0;i<M;i++){
		vector<point> row;
		for(int j=0;j<N;j++){
			point p;
			f >> p.x;
			f >> p.y;
			f >> p.z;
			row.push_back(p);
		}
		points.push_back(row);
	}
	
	f >> K;
	for(int i=0;i<K;i++){
		color c;
		f >> c.r;
		f >> c.g;
		f >> c.b;
		palette.push_back(c);
	}
	f.close();
	
}

int fac(int n){
	if(n<=1) return 1;
	int result =1;
	for(int i=2;i<n+1;i++){
		result *= i;
		}
	return result; 
	
	}

int C(int n,int i){
	
	int result = 1;
	for(int k=n;k>n-i;k--){
		result *= k;
		}
	return result/fac(i);
	}

float B(int i, int n, float u){
	
	return C(n,i) * pow(u,i) * pow(1-u,n-i);
	
	}

point P(float u, float v){
	//cout << u << " "<<v<<"      ";
	point result;
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++){
			point temp = points[i][j]*(B(i,M-1,u)* B(j,N-1,v));
			//cout <<points[i][j].x<<" "<< points[i][j].y<<" "<< points[i][j].z<<" "<<endl;
			//cout <<temp.x<<" "<< temp.y<<" "<< temp.z<<" "<<endl;
			result = result + temp;
	}
	//cout <<result.x<<" "<< result.y<<" "<< result.z<<" "<<endl;
	return result ;
	}

void createSamples(){
		vdiff = 1.0/ (sampleC);
		udiff = 1.0/ (sampleR);
		samples.clear();
		for(int i=0;i<sampleR+1;i++){
			vector <point> row;
			for(int j=0;j<sampleC+1;j++){
				point temp = P(i*udiff,j*vdiff);
				//cout <<i<<" "<<j<<" "<<temp.x<<" "<< temp.y<<" "<< temp.z<<" "<<endl;
				row.push_back(temp);
				}
				samples.push_back(row);
		}
	}

point findAvarage(){
	point avarage;
	
	for(int i= 0;i<sampleR;i++){
		for(int j=0;j<sampleC;j++){
			avarage.x += samples[i][j].x;
			avarage.y += samples[i][j].y;
			avarage.z += samples[i][j].z;
		}
	} 
	int total = sampleC*sampleR;
	avarage.x /= total;
	avarage.y /= total;
	avarage.z /= total;
	
	return avarage;
	
	}
	
void myGlutDisplay( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear color buffer with glClearColor() RGB values
	glLoadIdentity();

	gluLookAt(60, 50, 60, lookX, lookY, 0, 0, 1, 0); // Set camera position and direction
	
	
	
	
	
	point avarage = findAvarage();
	glTranslatef(tx,ty,tz);
	glTranslatef(avarage.x,avarage.y,avarage.z);
	glRotatef(RotAngle,0,1,0);
	glTranslatef(-avarage.x,-avarage.y,-avarage.z);
	
	
	
	
	if(mode == 2){
		createSamples();
	glBegin(GL_POINTS);	
	glColor3f(0.0f, 1.0f, 0.0f); 
	glVertex3f( points[selectedX][selectedY].x, points[selectedX][selectedY].y, points[selectedX][selectedY].z);
	
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			glColor3f(1.0f, 0.0f, 0.0f); 
			glVertex3f( points[i][j].x, points[i][j].y, points[i][j].z);
		}
	}
		
	glEnd();
	}
	
	
	float besty = -9999;
	float worsty=9999;
	for(int i=0;i<sampleR;i++){
		for(int j=0;j<sampleC;j++){

			float curY = (samples[i][j].y + samples[i+1][j].y + samples[i][j+1].y)/3.0f;
			if(besty < curY) besty = curY;
			if(worsty>curY) worsty = curY;
			curY = (samples[i+1][j].y + samples[i+1][j+1].y + samples[i][j+1].y)/3.0f;
			if(besty < curY) besty = curY;
			if(worsty>curY) worsty = curY;
		}
	}
	
	
	
	
	
	glBegin(GL_TRIANGLES);	
	for(int i=0;i<sampleR;i++){
		for(int j=0;j<sampleC;j++){
			
			float curY = (samples[i][j].y + samples[i+1][j].y + samples[i][j+1].y)/3.0;
			int colorIndex = (K-1)* (curY-worsty) / (besty - worsty);
			glColor3f(palette[colorIndex].r/255.0, palette[colorIndex].g/255.0, palette[colorIndex].b/255.0); 
			glVertex3f( samples[i][j].x, samples[i][j].y, samples[i][j].z);
			glVertex3f( samples[i+1][j].x, samples[i+1][j].y, samples[i+1][j].z);
			glVertex3f( samples[i][j+1].x, samples[i][j+1].y, samples[i][j+1].z);

			curY = (samples[i+1][j].y + samples[i+1][j+1].y + samples[i][j+1].y)/3.0;
			colorIndex = (K-1)* (curY-worsty) / (besty - worsty);
			glColor3f(palette[colorIndex].r/255.0, palette[colorIndex].g/255.0, palette[colorIndex].b/255.0); 
			glVertex3f( samples[i+1][j].x, samples[i+1][j].y, samples[i+1][j].z);
			glVertex3f( samples[i+1][j+1].x, samples[i+1][j+1].y, samples[i+1][j+1].z);
			glVertex3f( samples[i][j+1].x, samples[i][j+1].y, samples[i][j+1].z);
		}
	}
	glEnd();

	glutSwapBuffers();	// Swap buffers in float buffered scene
}


void myGlutKey (unsigned char key, int x, int y)
{
	
	if(key=='1') mode = 1;
	if(key=='2') mode = 2;
	
	if(mode == 1){
		if (key=='r')
			RotAngle++;
		else if (key=='t')
			RotAngle--;
		else if (key=='q')
			tx--;
		else if (key=='w')
			tx++;
		else if (key=='a')
			ty--;
		else if (key=='s')
			ty++;
		else if (key=='z')
			tz--;
		else if (key=='x')
			tz++;
	}else {
		changed = true;
		if (key=='q')
			points[selectedX][selectedY].x--;
		else if (key=='w')
			points[selectedX][selectedY].x++;
		else if (key=='a')
			points[selectedX][selectedY].y--;
		else if (key=='s')
			points[selectedX][selectedY].y++;
		else if (key=='z')
			points[selectedX][selectedY].z--;
		else if (key=='x')
			points[selectedX][selectedY].z++;
		else if(key=='i')
			sampleR /= 2 ;
		else if(key=='o')
			sampleR *= 2 ;
		else if(key=='k')
			sampleC /= 2 ;
		else if(key=='l')
			sampleC *= 2 ;	
		else changed = false;	
	}
    glutPostRedisplay();
}

void specialKeyInput(int key, int x, int y)
{
	if(mode ==2){
		if (key == GLUT_KEY_UP) 
			if (selectedX >0) 
				selectedX--;
		if (key == GLUT_KEY_DOWN)
			if (selectedX < M-1)
				selectedX++;
		if (key == GLUT_KEY_LEFT)
			if (selectedY >0) 
				selectedY--;
		if (key == GLUT_KEY_RIGHT)
			if (selectedY < N-1) 
				selectedY++;
	}
	glutPostRedisplay();
}


void MouseFunc(int button, int state, int x, int y){
	
								
		oldX = x;
		oldY=y;								
		valid = state == GLUT_DOWN;						
										
}

void MotionFunc(int x, int y){
	
	if(valid){
		lookX += x - oldX;
		lookY += y - oldY;
		oldX = x;
		oldY = y;
	}
	glutPostRedisplay();
}

/**************************************** myInit() ******************/

void myInit(void)
{
	// Any initialization before the main loop of GLUT goes here

	glEnable(GL_DEPTH_TEST);	// Enable depth Buffering 
	glEnable(GL_COLOR_MATERIAL);	// Enable color tracking
	glEnable(GL_NORMALIZE);	// Enables vector normalization (optional)
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f ); 	// Set initial value of color buffer (Set background color also)

	// Lighting initialization
	glDisable(GL_LIGHTING);
	glPointSize(10);

	// Initialize camera
	glMatrixMode(GL_PROJECTION);	// Switch  to projection matrix
	glLoadIdentity();	// Clear current matrix to identity matrix
	gluPerspective(60,1,1,10000);	// Set projection of camera (You can modify the arguments if needed.)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
	//   Initialize GLUT and create window
	
	readFile(argv[1]);
	createSamples();

	glutInit(&argc,argv);	// Glut initialization function
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );	// Set display mode
	glutInitWindowPosition( 50, 50 );	// Set window position
	glutInitWindowSize( 600, 600 );	// Set window size

	main_window = glutCreateWindow( "hw2" );	// Create new window with 
	glutDisplayFunc( myGlutDisplay );	// Set display function
	glutKeyboardFunc( myGlutKey );
	glutSpecialFunc  (specialKeyInput);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MotionFunc);

	myInit();	// Call defined init function
	glutMainLoop();	// Start main loop after initialization
}
