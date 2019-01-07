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
enum VAO_IDs { Cube, PiramideExTop, Piramide, NumVAOs };
enum Buffer_IDs { CubeBuffer, PiramideExTopBuffer, PiramideBuffer, NumBuffers };
enum EBO_IDs { CubeEBuffer, PiramideExTopEBuffer, PiramideEBuffer, NumEBuffers };
enum Attrib_IDs { vPosition, vColor, vTexcoord };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBuffers[NumEBuffers];
const GLuint NumVerticesBodyWoman = 60;
const GLuint NumVerticesCube = 36;
const GLuint NumFigure = 16;
GLuint program;

bool b_depth = true;
bool b_blend = true;
bool b_stencil = false;

GLfloat posx = 0.0f;
GLfloat posy = 0.0f;

GLfloat kposx = 0.0;
GLfloat kposy = 0.0;
GLint mposx, mposy;

GLuint Location;

using namespace glm;

GLfloat alpha = 0.2f, beta = 0.8f, dist = 5.0f, DELTA = 0.5f;

// cube
void generateCube(){
	static const GLfloat cube_positions[] = {
		-1.0, -1.0, -1.0, 1.0,     // 0
		-1.0, -1.0, 1.0, 1.0,     // 1
		-1.0, 1.0, -1.0, 1.0,    // 2
		-1.0, 1.0, 1.0, 1.0,    // 3
		1.0, -1.0, -1.0, 1.0,  // 4
		1.0, -1.0, 1.0, 1.0,  // 5
		1.0, 1.0, -1.0, 1.0, // 6
		1.0, 1.0, 1.0, 1.0  // 7
	};
	static const GLfloat cube_colors[] = {
		0.0, 1.0, 1.0, 0.5, 0.0, 0.0, 0.0, 0.5, 0.0, 1.0, 1.0, 0.5,
		0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.5,
		0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.5 };
	static const GLushort cube_indices[] = {
		0, 1, 2, 3, 6, 7, 4, 5, 0xFFFF, 2, 6, 0, 4, 1, 5, 3, 7 };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[CubeEBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices,
		GL_STATIC_DRAW);

	glBindVertexArray(VAOs[Cube]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[CubeBuffer]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
		NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors),
		cube_colors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void drawCube() {
	glBindVertexArray(VAOs[CubeBuffer]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[CubeEBuffer]);
#if USE_PRIMITIVE_RESTART
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);
	glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
#else
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT,
		(const GLvoid*)(9 * sizeof(GLushort)));
#endif
}

// Piramide without top
void generatePiramideExTop(){
	static const GLfloat cube_positions[] = {
		-2.0, -1.0, -2.0, 1.0,     // 0
		-2.0, -1.0, 2.0, 1.0,     // 1
		-1.0, 1.0, -1.0, 1.0,    // 2
		-1.0, 1.0, 1.0, 1.0,    // 3
		2.0, -1.0, -2.0, 1.0,  // 4
		2.0, -1.0, 2.0, 1.0,  // 5
		1.0, 1.0, -1.0, 1.0, // 6
		1.0, 1.0, 1.0, 1.0  // 7
	};
	static const GLfloat cube_colors[] = {
		0.0, 1.0, 1.0, 0.5, 0.0, 0.0, 0.0, 0.5, 0.0, 1.0, 1.0, 0.5,
		0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.5,
		0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.5 };
	static const GLushort cube_indices[] = {
		0, 1, 2, 3, 6, 7, 4, 5, 0xFFFF, 2, 6, 0, 4, 1, 5, 3, 7 };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[PiramideExTopEBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices,
		GL_STATIC_DRAW);

	glBindVertexArray(VAOs[PiramideExTop]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PiramideExTopBuffer]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
		NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors),
		cube_colors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void drawPiramideExTop() {
	glBindVertexArray(VAOs[PiramideExTopBuffer]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[PiramideExTopEBuffer]);
#if USE_PRIMITIVE_RESTART
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);
	glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
#else
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT,
		(const GLvoid*)(9 * sizeof(GLushort)));
#endif
}

// Piramide
void generatePiramide() {
	static const GLfloat piramide_positions[] = {
		-1.0, 0.0, -1.0, 1.0,     // 0
		1.0, 0.0, -1.0, 1.0,     // 1
		-1.0, 0.0, 1.0, 1.0,    // 2
		1.0, 0.0, 1.0, 1.0,    // 3
		0.0, 2.0, 0.0, 1.0,   // 4
	};
	static const GLfloat piramide_colors[] = {
		1.0, 1.0, 1.0, 1.0,		// 0
		1.0, 1.0, 0.0, 1.0,	   // 1
		1.0, 0.0, 1.0, 1.0,   // 2
		1.0, 0.0, 0.0, 1.0,  // 3
		0.0, 1.0, 1.0, 1.0  // 4
	};
	static const GLushort piramide_indices[] = {
		0, 1, 2, 3, 0xFFFF, 1, 3, 4, 2, 0, 4, 1
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[PiramideEBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(piramide_indices), piramide_indices,
		GL_STATIC_DRAW);

	glBindVertexArray(VAOs[Piramide]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PiramideBuffer]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(piramide_positions) + sizeof(piramide_colors),
		NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(piramide_positions), piramide_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(piramide_positions), sizeof(piramide_colors),
		piramide_colors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(piramide_colors));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void drawPiramide(void) {
	glBindVertexArray(VAOs[PiramideBuffer]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[PiramideEBuffer]);

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_TRIANGLE_STRIP, 7, GL_UNSIGNED_SHORT, (const GLvoid*)(5 * sizeof(GLushort)));
}

void init(void)
{
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("Programme/prakt6.vs", "Programme/prakt6.fs", "", "", "", "");
	glUseProgram(program);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_STENCIL_TEST);

	glGenBuffers(NumEBuffers, EBuffers);
	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumBuffers, Buffers);

	generateCube();
	generatePiramideExTop();
	generatePiramide();
}

void display(void)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	
	glStencilFunc(GL_ALWAYS, 0x01, 0x1);

	// pol
	Model = mat4(1.0);
	Model = translate(Model, vec3(0, -2.0, 0.0));
	Model = scale(Model, vec3(20.0, 0.1, 20.0));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCube();

	// kvadratnaya bashnia
	Model = mat4(1.0);
	Model = translate(Model, vec3(10.0, 0.0, -15.0));
	Model = scale(Model, vec3(4.0, 2.0, 4.0));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCube();

	Model = mat4(1.0);
	Model = translate(Model, vec3(10.0, 4.0, -15.0));
	Model = scale(Model, vec3(3.5, 2.0, 3.5));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCube();

	Model = mat4(1.0);
	Model = translate(Model, vec3(10.0, 8, -15.0));
	Model = scale(Model, vec3(3.0, 2, 3.0));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCube();

	Model = mat4(1.0);
	Model = translate(Model, vec3(10.0, 11.0, -15.0));
	Model = scale(Model, vec3(2.5, 1.0, 2.5));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCube();

	Model = mat4(1.0);
	Model = translate(Model, vec3(10.0, 12.0, -15.0));
	Model = scale(Model, vec3(2.5, 1.5, 2.5));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawPiramide();

	// shipastaya bashnia
	Model = mat4(1.0);
	Model = translate(Model, vec3(-10.0, 0.0, -15.0));
	Model = scale(Model, vec3(3, 1.0, 3));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCube();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-10.0, 2.0, -15.0));
	Model = scale(Model, vec3(2.5, 1.0, 2.5));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawPiramideExTop();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-10.0, 4.0, -15.0));
	Model = scale(Model, vec3(2.5, 1.0, 2.5));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCube();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-10.0, 6.0, -15.0));
	Model = scale(Model, vec3(2.0, 1.0, 2.0));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawPiramideExTop();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-10.0, 8.0, -15.0));
	Model = scale(Model, vec3(2.0, 1.0, 2.0));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawCube();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-10.0, 10.0, -15.0));
	Model = scale(Model, vec3(1.5, 1.0, 1.5));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawPiramideExTop();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-10.0, 11.0, -15.0));
	Model = scale(Model, vec3(1.5, 1.5, 1.5));
	ModelViewProjection = Projection*View*Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	drawPiramide();

	glFlush();
}

void reshape(int w, int h) {
	glViewport(0,0,w,h);
	width = w;
	height = h;
}

void idle(void) {
	display();
	Sleep(15);
}

void keyboard(unsigned char theKey, int mouseX, int mouseY) {
	GLint x = mouseX;
	GLint y = height - mouseY;
	switch (theKey)	{
		case 'v': dist -= DELTA; display(); break;
		case 'z': dist += DELTA; display(); break;
		case 'd': 
			if (b_depth) glDisable(GL_DEPTH_TEST);
			else glEnable(GL_DEPTH_TEST);
			b_depth = !b_depth; 
			display();
			break;
		case 's':
			if (b_stencil) glDisable(GL_STENCIL);
			else glEnable(GL_STENCIL);
			b_stencil = !b_stencil;
			display();
			break;
		case 'b':
			if (b_blend) glDisable(GL_BLEND);
			else glEnable(GL_BLEND);
			b_blend = !b_blend;
			display();
			break;
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
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