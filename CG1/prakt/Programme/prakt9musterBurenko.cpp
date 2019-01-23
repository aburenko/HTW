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
enum VAO_IDs { Box24, Box, Triangles, Circle, Piramide, NumVAOs };
enum Buffer_IDs { Box24Buffer, BoxBuffer, TrianglesBuffer, CircleBuffer, PiramideBuffer, NumBuffers };
enum EBO_IDs {BoxEBuffer, PiramideEBuffer, NumEBuffers };
enum Attrib_IDs { vPosition, vColor };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBuffers[NumEBuffers];
const GLuint NumVerticesCircle = 60;
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

// prakt4 
GLuint Location;

using namespace glm;

GLfloat alpha = 0.2f, beta = 0.8f, dist = 5.0f, DELTA = 0.5f;
// BOX
void genarateBox() {
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
		0.0, 1.0, 1.0,
		0.1, 0.0, 0.0,
		0.0, 0.1, 0.0,
		1.0, 1.0, 0.1,
		0.0, 1.0, 1.0,
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		1.0, 1.0, 0.1 };
	static const GLushort cube_indices[] = {
		0, 1, 2, 3, 6, 7, 4, 5, 0xFFFF, 2, 6, 0, 4, 1, 5, 3, 7 };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[BoxEBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices,
		GL_STATIC_DRAW);

	glBindVertexArray(VAOs[Box]); 
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[BoxBuffer]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
		NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors),
		cube_colors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void drawBox() {
	glBindVertexArray(VAOs[BoxBuffer]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[BoxEBuffer]);
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
// BOX24
void genarateBox24() {
	static const GLfloat cube_positions[] = {
		//peredniaya
		1.0, 1.0, 1.0, 1.0,     // 1
		-1.0, 1.0, 1.0, 1.0,     // 0
		1.0, 1.0, -1.0, 1.0,    // 2
		-1.0, 1.0, -1.0, 1.0,    // 3
		//zadnia
		1.0, -1.0, 1.0, 1.0,     // 1
		-1.0, -1.0, 1.0, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//levo
		-1.0, 1.0, 1.0, 1.0,     // 1
		-1.0, -1.0, 1.0, 1.0,     // 0
		-1.0, 1.0, -1.0, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//pravo
		1.0, -1.0, 1.0, 1.0,     // 1
		1.0, 1.0, 1.0, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		1.0, 1.0, -1.0, 1.0,    // 3
		//niz
		1.0, 1.0, -1.0, 1.0,     // 1
		-1.0, 1.0, -1.0, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//verh
		1.0, 1.0, 1.0, 1.0,     // 1
		-1.0, 1.0, 1.0, 1.0,     // 0
		1.0, -1.0, 1.0, 1.0,    // 2
		-1.0, -1.0, 1.0, 1.0  // 3
	};

	static const GLfloat cube_colors[] = {
		//peredniaya
		0.5, 0.5, 0.5,     // 0
		0.5, 0.5, 0.5,     // 1
		0.5, 0.5, 0.5,     // 2
		0.5, 0.5, 0.5,     // 3
		//zadnia
		0.5, 0.5, 0.5,     // 0
		0.5, 0.5, 0.5,     // 1
		0.5, 0.5, 0.5,     // 2
		0.5, 0.5, 0.5,     // 3
		//levo
		0.5, 0.5, 0.5,     // 0
		0.5, 0.5, 0.5,     // 1
		0.5, 0.5, 0.5,     // 2
		0.5, 0.5, 0.5,     // 3
		//pravo
		0.5, 0.5, 0.5,     // 0
		0.5, 0.5, 0.5,     // 1
		0.5, 0.5, 0.5,     // 2
		0.5, 0.5, 0.5,     // 3
		//niz
		0.5, 0.5, 0.5,     // 0
		0.5, 0.5, 0.5,     // 1
		0.5, 0.5, 0.5,     // 2
		0.5, 0.5, 0.5,     // 3
		//verh
		0.5, 0.5, 0.5,     // 0
		0.5, 0.5, 0.5,     // 1
		0.5, 0.5, 0.5,     // 2
		0.5, 0.5, 0.5      // 3
	};
	static const GLfloat cube_norm[] = {
		//peredniaya
		0, 1, 0,     // 0
		0, 1, 0,     // 1
		0, 1, 0,     // 2
		0, 1, 0,     // 3
		//zadnia
		0, -1, 0,     // 0
		0, -1, 0,     // 1
		0, -1, 0,     // 2
		0, -1, 0,     // 3
		//levo
		-1, 0, 0,     // 0
		-1, 0, 0,     // 1
		-1, 0, 0,     // 2
		-1, 0, 0,     // 3
		//pravo
		1, 0, 0,     // 0
		1, 0, 0,     // 1
		1, 0, 0,     // 2
		1, 0, 0,     // 3
		//niz
		0, 0, -1,     // 0
		0, 0, -1,     // 1
		0, 0, -1,     // 2
		0, 0, -1,     // 3
		//verh
		0, 0, 1,     // 0
		0, 0, 1,     // 1
		0, 0, 1,     // 2
		0, 0, 1     // 3
	};


	glBindVertexArray(VAOs[Box24]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Box24Buffer]);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm),
		cube_positions,
		GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, 
		sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm),
		cube_positions, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions),
		sizeof(cube_colors), cube_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
		sizeof(cube_norm), cube_norm);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(sizeof(cube_positions) + sizeof(cube_colors)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void drawBox24() {
	glBindVertexArray(VAOs[Box24Buffer]);
	for (int i = 0; i < 6; i++) {
		glDrawArrays(GL_TRIANGLES,
			(4 * i), 3);
		glDrawArrays(GL_TRIANGLES,
			(4 * i + 1), 3);
	}
}
// Rectangle
void generateRectangle(GLfloat x, GLfloat y) {
	GLfloat verticesR[4][2] = {
		{ 0, 0 }, { 0, 1 },
		{ 1, 0 }, { 1, 1 }
	};
	static const GLfloat normal_data[] = {
		0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 
	};
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[TrianglesBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);


	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR) + sizeof(normal_data),
		NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticesR), verticesR);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(verticesR), sizeof(normal_data),
		normal_data);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(verticesR));
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(2);
}

void drawRectangle(void) {
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttrib3f(vColor, 1.0, 0.8f, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glVertexAttrib3f(vColor, 1.0, 0.8f, 0);
	glDrawArrays(GL_TRIANGLES, 1, 3);
}
// Circle
void generateCircle(GLfloat r) {
	GLfloat verticesR[NumVerticesCircle*2][3];

	for (int i = 0; i < NumVerticesCircle; i++) {
		if (i % 3 == 0) {
			verticesR[i][0] = 0;
			verticesR[i][1] = 0;
			verticesR[i][2] = 0;
			verticesR[NumVerticesCircle + i][0] = 0;
			verticesR[NumVerticesCircle + i][1] = 0;
			verticesR[NumVerticesCircle + i][2] = -2.0;
		}
		else {
			GLfloat wert = 2 * M_PI * i / (NumVerticesCircle / 3.0);
			verticesR[i][0] = (GLfloat)r*cos(wert);
			verticesR[i][1] = (GLfloat)r*sin(wert);
			verticesR[i][2] = 0;
			verticesR[NumVerticesCircle + i][0] = (GLfloat)r*sin(wert);
			verticesR[NumVerticesCircle + i][1] = (GLfloat)r*cos(wert);
			verticesR[NumVerticesCircle + i][2] = 0;
		}

	}

	glBindVertexArray(VAOs[Circle]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[CircleBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void drawCircle(void) {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(VAOs[Circle]);
	for (int i = 0; i < NumVerticesCircle*2; i += 3) {
		if (i < NumVerticesCircle)
			glVertexAttrib3f(vColor, 0.0f, 0.0f, 1.0f);
		else
			glVertexAttrib3f(vColor, 1, 0, 0);
		glDrawArrays(GL_TRIANGLES, i, 3);
	}
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

// Cone
void generateCone() {
	static const GLfloat cone_positions[] = {
		-1.0, 0.0, -1.0, 1.0,     // 0
		1.0, 0.0, -1.0, 1.0,     // 1
		-1.0, 0.0, 1.0, 1.0,    // 2
		1.0, 0.0, 1.0, 1.0,    // 3
		0.0, 2.0, 0.0, 1.0,   // 4
	};
	static const GLfloat cone_colors[] = {
		1.0, 1.0, 1.0, 1.0,		// 0
		1.0, 1.0, 0.0, 1.0,	   // 1
		1.0, 0.0, 1.0, 1.0,   // 2
		1.0, 0.0, 0.0, 1.0,  // 3
		0.0, 1.0, 1.0, 1.0  // 4
	};
	static const GLushort cone_indices[] = {
		0, 1, 2, 3, 0xFFFF, 1, 3, 4, 2, 0, 4, 1
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffers[PiramideEBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cone_indices), cone_indices,
		GL_STATIC_DRAW);

	glBindVertexArray(VAOs[Piramide]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PiramideBuffer]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cone_positions) + sizeof(cone_colors),
		NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cone_positions), cone_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cone_positions), sizeof(cone_colors),
		cone_colors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cone_colors));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void drawCone(void) {
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
	program = loadShaders("Programme/prakt9musterBurenko.vs", "Programme/prakt9musterBurenko.fs", "", "", "", "");
	glUseProgram(program);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_STENCIL_TEST);

	glGenBuffers(NumEBuffers, EBuffers);
	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumBuffers, Buffers);

	genarateBox24();
	generateRectangle(2.0, 2.0);
	generateCircle(1);
	generatePiramide();
}

void display(void)
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat viewpoint[3];
	viewpoint[0] = dist*sin(beta)*sin(alpha);
	viewpoint[1] = dist*cos(beta);
	viewpoint[2] = dist*sin(beta)*cos(alpha);

	glViewport(0, 0, 512, 512);
	Location = glGetUniformLocation(program, "ModelViewProjection");
	GLuint locMV = glGetUniformLocation(program, "MVMatrix");
	GLuint locNM = glGetUniformLocation(program, "NormalMatrix");

	GLuint locAmbient = glGetUniformLocation(program, "Ambient");
	GLuint locColor = glGetUniformLocation(program, "LightColor");
	GLuint locLight = glGetUniformLocation(program, "LightPosition");

	GLuint locEye = glGetUniformLocation(program, "EyeDirection");
	GLuint locSchini= glGetUniformLocation(program, "Shininess");

	vec3 Ambient = vec3(1, 0.0, 0.0);
	vec3 LightColor = vec3(1, 0, 0);
	vec3 LightPosition = vec3(4, 4, 4);

	vec3 EyeDirection = vec3(10, 0, 0);
	float Shininess = 200.0;

	glUniform3fv(locAmbient, 1, &Ambient[0]);
	glUniform3fv(locColor, 1, &LightColor[0]);
	glUniform3fv(locLight, 1, &LightPosition[0]);

	glUniform3fv(locEye, 1, &EyeDirection[0]);
	glUniform1f(locSchini, Shininess);

	mat3 NormalMatrix;
	mat4 Projection = mat4(1.0);
	mat4 Model = mat4(1.0);
	mat4 View = mat4(1.0);
	mat4 ModelView = View*Model;
	mat4 ModelViewProjection;

	Projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.f);
	View = glm::lookAt(
		glm::vec3(viewpoint[0], viewpoint[1], viewpoint[2]),
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(0.0, cos(beta - 3.141593*0.5), 0.0)
	);

	ModelViewProjection = Projection*View*Model;
	ModelView = View*Model;
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
		{
			NormalMatrix[i][j] = ModelView[i][j];
			//printf("%d - %d: %f\n", i, j, NormalMatrix[i][j]);
		}
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	glUniformMatrix4fv(locMV, 1, GL_FALSE, &ModelView[0][0]);
	glUniformMatrix3fv(locNM, 1, GL_FALSE, &NormalMatrix[0][0]);
	//drawRectangle();

	//ModelView = View*Model;
	//for (int i = 0; i<3; i++)
	//	for (int j = 0; j<3; j++)
	//		NormalMatrix[i][j] = ModelView[i][j];
	//glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	//glUniformMatrix4fv(locMV, 1, GL_FALSE, &ModelView[0][0]);
	//glUniformMatrix3fv(locNM, 1, GL_FALSE, &NormalMatrix[0][0]);
	drawBox24();

	Model = mat4(1.0);
	Model = translate(Model, vec3(5.0, 5.0, 5.0));
	Model = scale(Model, vec3(0.1, 0.1, 0.1));
	ModelView = View*Model;
	ModelViewProjection = Projection*View*Model;
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
		{
			NormalMatrix[i][j] = ModelView[i][j];
			//printf("%d - %d: %f\n", i, j, NormalMatrix[i][j]);
		}
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	glUniformMatrix4fv(locMV, 1, GL_FALSE, &ModelView[0][0]);
	glUniformMatrix3fv(locNM, 1, GL_FALSE, &NormalMatrix[0][0]);
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
	glutInitContextVersion(4, 2);  // (4,2) (3,3);
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