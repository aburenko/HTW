/*
  Dreiecke
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>

GLuint loadShaders(const char* vertexFilePath,
 const char* fragmentFilePath,
 const char* geometryFilePath,
 const char* tesscontrolFilePath,
 const char* tessevaluationFilePath,
 const char* computeFilePath);
GLint height=100,width=100;
enum VAO_IDs {Triangles,NumVAOs};
enum Buffer_IDs {ArrayBuffer,NumBuffers};
enum Attrib_IDs {vPosition,vColor};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVerticesRectangle = 4;
GLuint program; 


void generateRectangle(GLfloat x, GLfloat y) {
	GLfloat verticesR[NumVerticesRectangle][2] = {
		{ 0, 0 }, { 0, y },
		{ x, 0 }, { x, y }
	};
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void drawRectangle(void) {
	glVertexAttrib3f(vColor, 1, 0.8, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glVertexAttrib3f(vColor, 1, 0.8, 0);
	glDrawArrays(GL_TRIANGLES, 1, 3);
}

void init(void)
{
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("Programme/Dreiecke.vs", "Programme/Dreiecke.fs", "", "", "", "");
	glUseProgram(program);
	glGenBuffers(NumBuffers, Buffers);
	glGenVertexArrays(NumVAOs, VAOs);
	generateRectangle(0.5,0.5);
}

void display(void)
{ 
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);

	drawRectangle();

	glFlush(); 
}

void reshape(int w, int h) {
	width=w;
	height=h; 
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512,512);
	glutInitContextVersion(4,5);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	glewExperimental=GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop(); 
}