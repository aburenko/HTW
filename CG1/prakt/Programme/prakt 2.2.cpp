/*
  Dreiecke
*/
#include <iostream>
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
enum VAO_IDs {Circle,NumVAOs};
enum Buffer_IDs {ArrayBuffer,NumBuffers};
enum Attrib_IDs {vPosition,vColor};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVerticesCircle = 60;
GLuint program; 


void generateCircle(GLfloat r) {
	GLfloat verticesR[NumVerticesCircle][2];
/*	
	for (int i = 0; i < NumVerticesCircle; i++) {
		if (i % 3 == 0) {
			verticesR[i][0] = 0;
			verticesR[i][1] = 0;
		}
		else {
			GLfloat wert = 2* 3.14 * i / (NumVerticesCircle/3);
			verticesR[i][0] = (GLfloat)r*cos(wert);
			verticesR[i][1] = (GLfloat)r*sin(wert);
		}
		std::cout << "Punkt " << i << std::endl;
		std::cout << verticesR[i][0] << std::endl;
		std::cout << verticesR[i][1] << std::endl;
	}
*/
///*
	int i = 0;
	for (int counter = 0; counter < NumVerticesCircle; counter += 3) {
		verticesR[i][0] = 0;
		verticesR[i][1] = 0;
		i++;

		GLfloat wert = 6 * 3.14 * counter / NumVerticesCircle;
		verticesR[i][0] = (GLfloat)r*cos(wert);
		verticesR[i][1] = (GLfloat)r*sin(wert);
		i++;

		GLfloat wert1 = 6 * 3.14 * (counter + 1) / NumVerticesCircle;
		verticesR[i][0] = (GLfloat)r*cos(wert1);
		verticesR[i][1] = (GLfloat)r*sin(wert1);
		i++;
	}
//*/
	glBindVertexArray(VAOs[Circle]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void drawCircle(void) {
	for (int i = 0; i < NumVerticesCircle; i += 3) {
		if(i % 2 == 0) 
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
	program = loadShaders("Programme/Dreiecke.vs", "Programme/Dreiecke.fs", "", "", "", "");
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

	drawCircle();

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