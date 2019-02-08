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
const GLuint NumVerticesCircle = 30;
const GLuint NumFigure = 16;
GLuint program;

GLfloat posx = 0.0f;
GLfloat posy = 0.0f;

void generateCircle(GLfloat r);

void init(void)
{
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("Programme/prakt3.vs", "Programme/prakt3.fs", "", "", "", "");
	glUseProgram(program);
	glGenBuffers(NumBuffers, Buffers);
	glGenVertexArrays(NumVAOs, VAOs);
	glUniform1f(glGetUniformLocation(program, "posx"), posx);
	glUniform1f(glGetUniformLocation(program, "posy"), posy);
	generateCircle(0.2f);
}

void generateCircle(GLfloat r) {
	GLfloat verticesR[NumVerticesCircle * NumFigure][2];
	GLfloat centerX = -0.75, centerY = -0.75;
	///*
	int i = 0;
	for (int k = 0; k < NumFigure / 4; k++)
	{
		for (int j = 0; j < NumFigure / 4; j++)
		{
			std::cout << "draw with center (" << centerX << ", " << centerY << ")" << std::endl;
			for (int counter = 0; counter < NumVerticesCircle; counter += 3) {
				verticesR[i][0] = centerX;
				verticesR[i][1] = centerY;
				i++;

				GLfloat wert = (GLfloat)(6 * 3.14 * counter / NumVerticesCircle);
				verticesR[i][0] = (GLfloat)r*cos(wert) + centerX;
				verticesR[i][1] = (GLfloat)r*sin(wert) + centerY;
				i++;

				GLfloat wert1 = (GLfloat)(6 * 3.14 * (counter + 1) / NumVerticesCircle);
				verticesR[i][0] = (GLfloat)r*cos(wert1) + centerX;
				verticesR[i][1] = (GLfloat)r*sin(wert1) + centerY;
				i++;
			}
			centerX += 0.5;
		}
		centerX = -0.75;
		centerY += 0.5;
	}

	for (i = 0; i < NumVerticesCircle*NumFigure; i++)
	{
		verticesR[i][0] *= 0.35f;
		verticesR[i][1] *= 0.35f;
	}
	//*/
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
	glBindVertexArray(VAOs[Circle]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void drawCircle(void) {
	for (int i = 0; i < NumVerticesCircle*NumFigure; i += 3) {
		//if (i % 2 == 0)
		//	glVertexAttrib3f(vColor, 0.0f, 0.0f, 0.0f);
		//else
		//	glVertexAttrib3f(vColor, 1.0f, 0.039f, 0.039f);
		glVertexAttrib3f(vColor, 1.0f, 0.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, i, 3);
	}
	
	//glBindVertexArray(VAOs[Circle]);
	//glVertexAttrib3f(vColor, 1, 0, 0);
	//glDrawArrays(GL_TRIANGLES, 0, NumVerticesCircle*NumFigure);
	
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

void OnMouseClick(int theButton, int State, int mouseX, int mouseY) {
	if ((theButton == GLUT_LEFT_BUTTON) && (State==GLUT_DOWN)) {
		GLint mposx = mouseX;  
		GLint mposy = height - mouseY;
		posx = mouseX / 250.0f - 1;
		posy = 1 - mouseY / 250.0f;
		printf("Mouse: %f, %f \n", posx, posy);
		glUniform1f(glGetUniformLocation(program, "posx"), posx);
		glUniform1f(glGetUniformLocation(program, "posy"), posy);
		display();
	}
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3,1);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	glewExperimental=GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutMouseFunc(OnMouseClick);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
