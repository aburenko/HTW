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
enum VAO_IDs { Box, Triangles, Circle, NumVAOs };
enum Buffer_IDs { BoxBuffer, TrianglesBuffer, CircleBuffer, NumBuffers };
enum EBO_IDs { BoxEBuffer, NumEBuffers };
enum Attrib_IDs { vPosition, vColor };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBuffers[NumEBuffers];
const GLuint NumVerticesCircle = 60;
const GLuint NumFigure = 16;
GLuint program;

GLfloat posx = 0.0f;
GLfloat posy = 0.0f;

// prakt4 
GLuint Location;

using namespace glm;

GLfloat alpha = 0.2f, beta = 0.8f, dist = 5.0f, DELTA = 0.5f;

void genarateBox() {
	static const GLfloat cube_positions[] = {
		-1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0, 1.0,
		-1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0,
		1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	static const GLfloat cube_colors[] = {
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0, 0.5, 0.5, 0.5, 1.0 };
	static const GLushort cube_indices[] = {
		0, 1, 2, 3, 6, 7, 4, 5, 0xFFFF, 2, 6, 0, 4, 1, 5, 3, 7 };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices,
		GL_STATIC_DRAW);
	glBindVertexArray(VAOs[0]); 
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors),
		cube_colors);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
		(const GLvoid*)sizeof(cube_positions));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void drawBox() {
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[0]);
#if USE_PRIMITIVE_RESTART
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);
	glDrawElements(GL_TRIANGLE_STRIP,17,GL_UNSIGNED_SHORT,NULL);
#else
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT,
		(const GLvoid*)(9 * sizeof(GLushort)));
#endif
}

void generateRectangle(GLfloat x, GLfloat y) {
	GLfloat verticesR[4][2] = {
		{ 0, 0 }, { 0, y },
		{ x, 0 }, { x, y }
	};
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[TrianglesBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void drawRectangle(void) {
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttrib3f(vColor, 1.0, 0.8f, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glVertexAttrib3f(vColor, 1.0, 0.8f, 0);
	glDrawArrays(GL_TRIANGLES, 1, 3);
}

void generateCircle(GLfloat r) {
	GLfloat verticesR[NumVerticesCircle][2];

	for (int i = 0; i < NumVerticesCircle; i++) {
		if (i % 3 == 0) {
			verticesR[i][0] = 0;
			verticesR[i][1] = 0;
		}
		else {
			GLfloat wert = 2 * M_PI * i / (NumVerticesCircle / 3.0);
			verticesR[i][0] = (GLfloat)r*cos(wert);
			verticesR[i][1] = (GLfloat)r*sin(wert);
		}

	}

	glBindVertexArray(VAOs[Circle]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[CircleBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void drawCircle(void) {
	glBindVertexArray(VAOs[Circle]);
	for (int i = 0; i < NumVerticesCircle; i += 3) {
		if (i % 2 == 0)
			glVertexAttrib3f(vColor, 0.9f, 0.9f, 0.9f);
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
	program = loadShaders("Programme/prakt6.vs", "Programme/prakt6.fs", "", "", "", "");
	glUseProgram(program);

	glGenBuffers(NumEBuffers, EBuffers);
	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumBuffers, Buffers);

	genarateBox();
	generateRectangle(2.0, 2.0);
	generateCircle(1);
}

void display(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat viewpoint[3];
	viewpoint[0] = dist*sin(beta)*sin(alpha);
	viewpoint[1] = dist*cos(beta);
	viewpoint[2] = dist*sin(beta)*cos(alpha);

	glViewport(0, 0, 512, 512);
	Location = glGetUniformLocation(program, "ModelViewProjection");
	mat4 Projection = mat4(1.0);
	mat4 Model = mat4(1.0);
	mat4 View = mat4(1.0);
	mat4 ModelViewProjection;

	Projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.f);
	View = glm::lookAt(
		glm::vec3(viewpoint[0], viewpoint[1], viewpoint[2]),
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(0.0, cos(beta - 3.141593*0.5), 0.0)
	);

	Model = translate(Model, vec3(-2.0, 0.0, 0.0));
	ModelViewProjection = Projection*View*Model;

	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawBox();

	Model = mat4(1.0);
	Model = rotate(Model, 0.5f, vec3(1.0, 1.0, 1.0));
	Model = translate(Model, vec3(2.0, 0.0, 0.0));
	ModelViewProjection = Projection*View*Model;

	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawRectangle();

	Model = mat4(1.0);
	Model = translate(Model, vec3(5.0, 0.0, 0.0));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCircle();


	glFlush();
}

void reshape(int w, int h) {
	width = w;
	height = h;
}

void idle(void) {
	display();
	Sleep(15);
}


GLfloat kposx = 0.0;
GLfloat kposy = 0.0;
GLint mposx, mposy;

void keyboard(unsigned char theKey, int mouseX, int mouseY) {
	GLint x = mouseX;
	GLint y = height - mouseY;
	switch (theKey)	{
	case 'v': dist -= DELTA; display(); break;
	case 'z': dist += DELTA; display(); break;
	case 'e': exit(-1);
	}
}

void special(int specKey, int mouseX, int mouseY) {
	GLint x = mouseX;
	GLint y = height - mouseY;
	switch (specKey) {
	case GLUT_KEY_LEFT: alpha -= DELTA; display(); break;
	case GLUT_KEY_RIGHT: alpha += DELTA; display(); break;
	case GLUT_KEY_UP: beta -= DELTA; display(); break;
	case GLUT_KEY_DOWN: display(); beta += DELTA; break;
	}
}

void motion(int mouseX, int mouseY) {
	if (mouseX<(width / 2)) { alpha -= (mouseX - (GLfloat)(width / 2)) / 10000.0f; }
	else { alpha -= (mouseX - (width / 2)) / 10000.0f; }
	if (mouseY<(height / 2)) { beta -= (mouseY - (GLfloat)(height / 2)) / 10000.0f; }
	else { beta -= (mouseY - (GLfloat)(height / 2)) / 10000.0f; }
	display();
}

void mouse(int theButton, int State, int mouseX, int mouseY) {
	if ((theButton == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) {

	}
	if ((theButton == GLUT_RIGHT_BUTTON) && (State == GLUT_DOWN)) {

	}
	GLint mposx = mouseX; GLint mposy = height - mouseY;
	printf("%d,%d\n", mouseX, mouseY);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3, 1);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	glewExperimental = GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
}