/*
  Dreiecke
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>
#define M_PI           3.14159265358979323846  /* pi */
GLuint loadShaders(const char* vertexFilePath,
 const char* fragmentFilePath,
 const char* geometryFilePath,
 const char* tesscontrolFilePath,
 const char* tessevaluationFilePath,
 const char* computeFilePath);
GLint height=100,width=100;
enum VAO_IDs {Circle,NumVAOs};
enum Buffer_IDs {ArrayBuffer,NumBuffers};
enum Attrib_IDs {vPosition,vColor};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVerticesCircle = 60;
const GLuint NumFigure = 16;
GLuint program;

GLfloat posx = 0.0f;
GLfloat posy = 0.0f;

// prakt4 
GLuint Location;

using namespace glm;

GLfloat nIDLE = 0.0;
GLfloat nIDLETR = 0.0;
GLfloat nSPEED = 1.0;

void generateCircle(GLfloat r);

void generateCircle(GLfloat r) {
	GLfloat verticesR[NumVerticesCircle][2];
	///*
	for (int i = 0; i < NumVerticesCircle; i++) {
	if (i % 3 == 0) {
		verticesR[i][0] = 0;
		verticesR[i][1] = 0;
	}
	else {
	GLfloat wert = 2* M_PI * i / (NumVerticesCircle/3);
		verticesR[i][0] = (GLfloat)r*cos(wert);
		verticesR[i][1] = (GLfloat)r*sin(wert);
	}
	std::cout << "Punkt " << i << std::endl;
	std::cout << verticesR[i][0] << std::endl;
	std::cout << verticesR[i][1] << std::endl;
	}
	//*/
	/*
	int i = 0;
	for (int counter = 0; counter < NumVerticesCircle; counter += 3) {
		verticesR[i][0] = 0;
		verticesR[i][1] = 0;
		i++;

		GLfloat wert = 6 * M_PI * counter / NumVerticesCircle;
		verticesR[i][0] = (GLfloat)r*cos(wert);
		verticesR[i][1] = (GLfloat)r*sin(wert);
		i++;

		GLfloat wert1 = 6 * M_PI * (counter + 1) / NumVerticesCircle;
		verticesR[i][0] = (GLfloat)r*cos(wert1);
		verticesR[i][1] = (GLfloat)r*sin(wert1);
		i++;
	}
	*/
	glBindVertexArray(VAOs[Circle]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void drawCircle(void) {
	for (int i = 0; i < NumVerticesCircle; i += 3) {
		if (i % 2 == 0)
			glVertexAttrib3f(vColor, 1, 0.8, 0);
		else
			glVertexAttrib3f(vColor, 1, 0, 0);
		glDrawArrays(GL_TRIANGLES, i, 3);
	}
}

void init(void)
{
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("Programme/prakt5.vs", "Programme/prakt5.fs", "", "", "", "");
	glUseProgram(program);
	glGenBuffers(NumBuffers, Buffers);
	glGenVertexArrays(NumVAOs, VAOs);
	generateCircle(0.85);
}

void display(void)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Circle]);

	glViewport(0, 0, 500, 500);
	Location = glGetUniformLocation(program, "ModelViewProjection");
	mat4 Projection = mat4(1.0);
	mat4 Model = mat4(1.0);
	mat4 View = mat4(1.0);
	mat4 ModelViewProjection;

	//Projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 20.0f);

	Model = translate(Model, vec3(nIDLETR*0.01f, 0.0, 0.0));
	Model = rotate(Model, nIDLE*0.02f, vec3(0.0, 0.0, 1.0));

	ModelViewProjection = Projection*View*Model;

	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);

	drawCircle();

	glFlush();
}

void reshape(int w, int h) {
	width = w;
	height = h;
}

int translateEnabled = 0;

void idle(void) {
	if (nIDLE > M_PI * 100) {
		nIDLE = 0.0;
		//translateEnabled = 1;
	}
	if (translateEnabled)
		nIDLETR++;
	nIDLE++;
	display();
	Sleep(15*nSPEED);
}


GLfloat kposx = 0.0;
GLfloat kposy = 0.0;
GLint mposx, mposy;

void keyboard(unsigned char theKey, int mouseX, int mouseY) {
	GLint x = mouseX;
	GLint y = height - mouseY;
	GLfloat px, py;
	switch (theKey)	{
	case 'p':
		for (;;){
			printf("Punkt: ");
			scanf("%f,%f", &px, &py);
			if (px == 99) break;
			kposx = px; kposy = py;
			display();
		} break;
	case 'e': exit(-1);
	}
}

void mouse(int theButton, int State, int mouseX, int mouseY) {
	if ((theButton == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) {
		if (nSPEED > 0.5)
			nSPEED -= 0.5;
	}
	if ((theButton == GLUT_RIGHT_BUTTON) && (State == GLUT_DOWN)) {
		if (nSPEED < 10.0)
			nSPEED += 1;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 5);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	glewExperimental = GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
}