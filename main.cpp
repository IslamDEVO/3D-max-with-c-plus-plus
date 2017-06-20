/*
الاسم : اسلام محمد عبد العزيز
سكشن : 1
قسم : تكنولوجياالمعلومات
الفرقه : الثالثه
*/

/*
		3	|		|	4
	--------|-------|--------
		1	|		|	2
*/

#include <string>
#include <gl/glut.h>
#include <math.h>
#include <fstream>
#include <iostream>


using namespace std;

GLfloat w = 0;
GLfloat h = 0;

int fileSeek = 0;
GLfloat nRange = 75.0f;

int NumberOfVert;
int NumberOfFaces;

GLfloat **vdata;
GLint **tindices;


void SetVolum(){
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, 1, 1, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopMatrix();
}

void ChangeSize(int w, int h)	{
	/*GLfloat nRange = 75.0f;*/
	
	::w = w;
	::h = h;

	// Prevent a divide by zero
	if(h == 0)	h = 1;

	// Set Viewport to window dimensions
    //glViewport(0, 0, w, h);

	 //Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void SetupRC()	{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);

}

void ReadScene(){

	 ifstream f1("scene.ASE");
	 f1.seekg(fileSeek);
	 /*if(f1.is_open()){
		 cout<<"the file is open correct\n";
		 cout<<"the point of file is \t"<<f1.tellg()<<endl;
	 }*/
	string s1;
	char c1;
	
	s1=" ";
	f1>>s1;
	while (s1 != "*MESH_NUMVERTEX") f1>>s1;
	f1>>NumberOfVert;
	f1>>s1;
	f1>>NumberOfFaces;

	vdata = new float* [NumberOfVert];
	tindices = new int* [NumberOfFaces];
	
	
	s1=" ";
	f1>>s1;
	while (s1 != "*MESH_VERTEX_LIST") f1>>s1;
	f1>>s1;
	for (int i=0 ; i<NumberOfVert ; i++)
	{
		vdata[i] = new float[3];
		f1 >> s1;
		f1 >> s1;
		f1 >> vdata[i][0];
		f1 >> vdata[i][1];
		f1 >> vdata[i][2];
	}

	s1=" ";
	f1>>s1;
	while (s1 != "*MESH_FACE_LIST") f1>>s1;
	f1>>s1;
	for (int i=0 ; i<NumberOfFaces ; i++)
	{
		tindices[i] = new int[3];
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
		f1 >> tindices[i][0];
		f1 >> s1;
		f1 >> tindices[i][1];
		f1 >> s1;
		f1 >> tindices[i][2];
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
		f1 >> s1;
	}
	fileSeek = f1.tellg();
	f1.close();

}

void DrawScene() {
		// Save matrix state and do the rotation
	glPushMatrix();
		// Call only once for all remaining points
	for (int i = 0; i < NumberOfFaces; i++) {    
   /* color information here */ 
   glBegin(GL_TRIANGLES);    
      glVertex3fv(&vdata[tindices[i][0]][0]); 
      glVertex3fv(&vdata[tindices[i][1]][0]); 
      glVertex3fv(&vdata[tindices[i][2]][0]);    
   glEnd(); 
}

	// Restore transformations
	glPopMatrix();

}

void RenderScene(void)	{

	// Clear the window with current clearing color
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	#pragma region ViewPort 1	bottom left		(TOP)
	glColor3f(1.0, 1.0, 0.0);
	glViewport(0 , 0 , w / 2 , h / 2);

	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	fileSeek = 0;
	glFlush();
#pragma endregion

#pragma region ViewPort 2	bottom rigtht	(FRONT)
	glColor3f(1.0, 0.0, 1.0);
	glViewport(0 + ( w/2 ) , 0 , w / 2 , h / 2);
	/*glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	ReadScene();*/
	gluLookAt(20, 0, 0, 0, 0, 0, 0, 0, 1);
	DrawScene();
	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	fileSeek = 0;
	glPopMatrix();
	glFlush();
#pragma endregion
	
#pragma region ViewPort 3 top left		(LEFT)
	glColor3f(0.5, 0.0, 0.1);
	glViewport(0 , 0 + ( h/2 ) , w / 2 , h / 2);
	gluLookAt(0, 20, 0, 0, 0, 0, 0, 0, 1);

	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	fileSeek = 0;
	glFlush();
#pragma endregion

#pragma region ViewPort 4	top right		(PERSPECTIVE)
	glColor3f(0.0, 1., 0.1);
	SetVolum();
	glViewport(0 + (w / 2), 0 + (h / 2) , w / 2, h / 2);
	gluLookAt(20, -20, 70
		, 150, 150, 0
		, 1, 1, 0);

	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	ReadScene();
	DrawScene();
	fileSeek = 0;
	glFlush();
#pragma endregion

	glPopMatrix();
	glutSwapBuffers();
}


int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Points Example");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}
