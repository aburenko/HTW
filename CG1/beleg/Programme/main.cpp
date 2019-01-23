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
enum VAO_IDs { Box24, PiramideExTop, Piramide, Triangles, Circle, NumVAOs };
enum Buffer_IDs { Box24Buffer, PiramideExTopBuffer, PiramideBuffer, TrianglesBuffer, CircleBuffer, NumBuffers };
enum Tex_IDs { floorID, wallId, roofId, sunid, texNum };
enum Attrib_IDs { vPosition, vColor, vNormal, vTexcoord };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint tex[texNum];
GLuint renderbuffer;
GLuint program;
const GLuint NumVerticesCircle = 120;

GLsizei TexWidth, TexHeight; 
GLuint framebuffer, texture;

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

GLfloat alpha = 0.6f, beta = 1.2f, dist = 25.0f, DELTA = 0.5f;

//licht raum
GLuint locMV;
GLuint locNM;
GLuint locM;
GLuint locHigth;

GLuint locRichtungBool;
GLuint locSpotBool;

mat3 NormalMatrix = mat3(1.0);
mat4 Projection = mat4(1.0);
mat4 Model = mat4(1.0);
mat4 View = mat4(1.0);
mat4 ModelView = View*Model;
mat4 ModelViewProjection;

// animation
GLfloat hightLimit = 5;
GLfloat currHight = -5;
bool downwards = false;

// BOX24
void generateBox24() {
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
		1, 1, 1,     // 0
		1, 1, 1,     // 1
		1, 1, 1,     // 2
		1, 1, 1,     // 3
		//zadnia
		1, 1, 1,     // 0
		1, 1, 1,     // 1
		1, 1, 1,     // 2
		1, 1, 1,     // 3
		//levo
		1, 1, 1,     // 0
		1, 1, 1,     // 1
		1, 1, 1,     // 2
		1, 1, 1,     // 3
		//pravo
		1, 1, 1,     // 0
		1, 1, 1,     // 1
		1, 1, 1,     // 2
		1, 1, 1,     // 3
		//niz
		1, 1, 1,     // 0
		1, 1, 1,     // 1
		1, 1, 1,     // 2
		1, 1, 1,     // 3
		//verh
		1, 1, 1,     // 0
		1, 1, 1,     // 1
		1, 1, 1,     // 2
		1, 1, 1      // 3
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

	static const GLfloat cube_tex[] = {
		//verh
		0, 0, 0, 1,
		1, 0, 1, 1,
		//niz
		0, 0, 0, 1,
		1, 0, 1, 1,
		//levo
		1, 1, 1, 0,
		0, 1, 0, 0,
		//pravo
		0, 0, 0, 1,
		1, 0, 1, 1,
		//zad
		1, 1, 0, 1,
		1, 0, 0, 0,
		//pered
		1, 1, 0, 1,
		1, 0, 0, 0
	};


	glBindVertexArray(VAOs[Box24]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Box24Buffer]);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(cube_positions),
		cube_positions,
		GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm) + sizeof(cube_tex),
		cube_positions, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions),
		sizeof(cube_colors), cube_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
		sizeof(cube_norm), cube_norm);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm),
		sizeof(cube_tex), cube_tex);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(sizeof(cube_positions) + sizeof(cube_colors)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 
		(const GLvoid*)(sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm)));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
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

// Piramide without top
void generatePiramideExTop(){
	static const GLfloat cube_positions[] = {
		//verh
		0.5, 0.5, 0.5, 1.0,     // 1
		-0.5, 0.5, 0.5, 1.0,     // 0
		0.5, 0.5, -0.5, 1.0,    // 2
		-0.5, 0.5, -0.5, 1.0,    // 3
		//niz
		1.0, -1.0, 1.0, 1.0,     // 1
		-1.0, -1.0, 1.0, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//levo
		-0.5, 0.5, 0.5, 1.0,     // 1
		-1.0, -1.0, 1.0, 1.0,     // 0
		-0.5, 0.5, -0.5, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//pravo
		1.0, -1.0, 1.0, 1.0,     // 1
		0.5, 0.5, 0.5, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		0.5, 0.5, -0.5, 1.0,    // 3
		//zad
		0.5, 0.5, -0.5, 1.0,     // 1
		-0.5, 0.5, -0.5, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//pered
		0.5, 0.5, 0.5, 1.0,     // 1
		-0.5, 0.5, 0.5, 1.0,     // 0
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
		-1, 1, 0,     // 0
		-1, 1, 0,     // 1
		-1, 1, 0,     // 2
		-1, 1, 0,     // 3
		//pravo
		1, 1, 0,     // 0
		1, 1, 0,     // 1
		1, 1, 0,     // 2
		1, 1, 0,     // 3
		//niz
		0, 1, -1,     // 0
		0, 1, -1,     // 1
		0, 1, -1,     // 2
		0, 1, -1,     // 3
		//verh
		0, 1, 1,     // 0
		0, 1, 1,     // 1
		0, 1, 1,     // 2
		0, 1, 1     // 3
	};

	static const GLfloat cube_tex[] = {
		//verh
		0, 0, 0, 1,
		1, 0, 1, 1,
		//niz
		0, 0, 0, 1,
		1, 0, 1, 1,
		//levo
		1, 1, 1, 0,
		0, 1, 0, 0,
		//pravo
		0, 0, 0, 1,
		1, 0, 1, 1,
		//zad
		1, 1, 0, 1,
		1, 0, 0, 0,
		//pered
		1, 1, 0, 1,
		1, 0, 0, 0
	};

	glBindVertexArray(VAOs[PiramideExTop]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PiramideExTopBuffer]);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm) + sizeof(cube_tex),
		NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions),
		sizeof(cube_colors), cube_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
		sizeof(cube_norm), cube_norm);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm),
		sizeof(cube_tex), cube_tex);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(sizeof(cube_positions) + sizeof(cube_colors)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0,
		(const GLvoid*)(sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}

void drawPiramideExTop() {
	glBindVertexArray(VAOs[PiramideExTopBuffer]);
	for (int i = 0; i < 6; i++) {
		glDrawArrays(GL_TRIANGLES,
			(4 * i), 3);
		glDrawArrays(GL_TRIANGLES,
			(4 * i + 1), 3);
	}
}

// Piramide
void generatePiramide() {
	static const GLfloat cube_positions[] = {
		//verh
		0, 1, 0, 1.0,     // 1
		0, 1, 0, 1.0,     // 0
		0, 1, -0, 1.0,    // 2
		-0, 1, -0, 1.0,    // 3
		//niz
		1.0, -1.0, 1.0, 1.0,     // 1
		-1.0, -1.0, 1.0, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//levo
		0, 1, 0, 1.0,     // 1
		-1.0, -1.0, 1.0, 1.0,     // 0
		0, 1, 0, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//pravo
		1.0, -1.0, 1.0, 1.0,     // 1
		0, 1, 0, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		0, 1, 0, 1.0,   // 3
		//zad
		0, 1, 0, 1.0,     // 1
		0, 1, 0, 1.0,     // 0
		1.0, -1.0, -1.0, 1.0,    // 2
		-1.0, -1.0, -1.0, 1.0,    // 3
		//pered
		0, 1, 0, 1.0,     // 1
		0, 1, 0, 1.0,     // 0
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
		-1, 2, 0,     // 0
		-1, 2, 0,     // 1
		-1, 2, 0,     // 2
		-1, 2, 0,     // 3
		//pravo
		1, 2, 0,     // 0
		1, 2, 0,     // 1
		1, 2, 0,     // 2
		1, 2, 0,     // 3
		//niz
		0, 2, -1,     // 0
		0, 2, -1,     // 1
		0, 2, -1,     // 2
		0, 2, -1,     // 3
		//verh
		0, 2, 1,     // 0
		0, 2, 1,     // 1
		0, 2, 1,     // 2
		0, 2, 1     // 3
	};

	static const GLfloat cube_tex[] = {
		//verh
		0, 0, 0, 1,
		1, 0, 1, 1,
		//niz
		0, 0, 0, 1,
		1, 0, 1, 1,
		//levo
		1, 1, 1, 0,
		0, 1, 0, 0,
		//pravo
		0, 0, 0, 1,
		1, 0, 1, 1,
		//zad
		1, 1, 0, 1,
		1, 0, 0, 0,
		//pered
		1, 1, 0, 1,
		1, 0, 0, 0
	};


	glBindVertexArray(VAOs[Piramide]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PiramideBuffer]);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm) + sizeof(cube_tex),
		NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions),
		sizeof(cube_colors), cube_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
		sizeof(cube_norm), cube_norm);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm),
		sizeof(cube_tex), cube_tex);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(sizeof(cube_positions) + sizeof(cube_colors)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0,
		(const GLvoid*)(sizeof(cube_positions) + sizeof(cube_colors) + sizeof(cube_norm)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}

void drawPiramide(void) {
	glBindVertexArray(VAOs[PiramideBuffer]);
	for (int i = 0; i < 6; i++) {
		glDrawArrays(GL_TRIANGLES,
			(4 * i), 3);
		glDrawArrays(GL_TRIANGLES,
			(4 * i + 1), 3);
	}
}

// Circle
void generateCircle(GLfloat r) {
	GLfloat verticesR[NumVerticesCircle][2];
	int i = 0;
	float cc = 0.0;
	for (int counter = 0; counter < NumVerticesCircle / 3; counter++) {
		verticesR[i][0] = 0;
		verticesR[i][1] = 0;
		i++;

		GLfloat wert = 2 * M_PI * cc / (NumVerticesCircle / 3);
		verticesR[i][0] = (GLfloat)r*cos(wert);
		verticesR[i][1] = (GLfloat)r*sin(wert);
		i++;
		cc++;

		GLfloat wert1 = 2 * M_PI * cc / (NumVerticesCircle / 3);
		verticesR[i][0] = (GLfloat)r*cos(wert1);
		verticesR[i][1] = (GLfloat)r*sin(wert1);
		i++;
	}

	GLfloat col[NumVerticesCircle][3];
	for (int counter = 0; counter < NumVerticesCircle; counter++) {
		verticesR[counter][0] = 1;
		verticesR[counter][1] = 0;
		verticesR[counter][2] = 0;
	}


	glBindVertexArray(VAOs[Circle]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[CircleBuffer]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR) + sizeof(col), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(verticesR), verticesR);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(verticesR),
		sizeof(col), col);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(verticesR) + sizeof(col),
		sizeof(verticesR), verticesR);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(verticesR));
	glVertexAttribPointer(vTexcoord, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(verticesR) + sizeof(col)));

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vColor);
	glEnableVertexAttribArray(vTexcoord);
}

void drawCircle(void) {
	glBindVertexArray(VAOs[Circle]);
	for (int i = 0; i < NumVerticesCircle; i += 3) {
		glDrawArrays(GL_TRIANGLES, i, 3);
	}
}

// Rectangle
void generateRectangle() {
	GLfloat verticesarr[] = {
		0, 0, 0, 1,
		1, 0, 1, 1,

		0, 0, 0, 1,
		1, 0, 1, 1
	};
	// vertex attribute array
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[TrianglesBuffer]);
	// data
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesarr), verticesarr, GL_STATIC_DRAW);
	//PunktePointer: 0 Punkt, 2 Dimensionen, (GLvoid*)0 von wo wir im Array anfangen zu lesen
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//Texturpointer: 1 , 2 Dimensionen, ab 16. Punkt kommen Textur Koordinaten.
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(8 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(3);
}

void drawRectangle(void) {
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttrib3f(vColor, 1.0, 0.8f, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glVertexAttrib3f(vColor, 1.0, 0.8f, 0);
	glDrawArrays(GL_TRIANGLES, 1, 3);
}

void init(void)
{
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("Programme/main.vs", "Programme/main.fs", "", "", "", "");

	glGenTextures(texNum, tex);

	// texturen
	FreeImage_Initialise(true);
	FIBITMAP *bitmap_data;
	int bitmapWidth, bitmapHeight;
	BYTE *bitmapBits;
	FREE_IMAGE_FORMAT bitmapFormat;
	// grass texture
	bitmapFormat = FreeImage_GetFileType("Programme/grass.bmp");
	bitmap_data = FreeImage_Load(bitmapFormat, "Programme/grass.bmp");
	glBindTexture(GL_TEXTURE_2D, tex[floorID]);
	bitmapWidth = FreeImage_GetWidth(bitmap_data);
	bitmapHeight = FreeImage_GetHeight(bitmap_data);
	bitmapBits = FreeImage_GetBits(bitmap_data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapWidth, bitmapHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bitmapBits);
	FreeImage_Unload(bitmap_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_WRAP_BORDER, GL_REPEAT);
	// roof texture
	bitmapFormat = FreeImage_GetFileType("Programme/roof.jpg");
	bitmap_data = FreeImage_Load(bitmapFormat, "Programme/roof.jpg");
	glBindTexture(GL_TEXTURE_2D, tex[roofId]);
	bitmapWidth = FreeImage_GetWidth(bitmap_data);
	bitmapHeight = FreeImage_GetHeight(bitmap_data);
	bitmapBits = FreeImage_GetBits(bitmap_data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapWidth, bitmapHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bitmapBits);
	FreeImage_Unload(bitmap_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_WRAP_BORDER, GL_REPEAT);
	// wall bzw. block texture
	bitmapFormat = FreeImage_GetFileType("Programme/japwall.jpg");
	bitmap_data = FreeImage_Load(bitmapFormat, "Programme/japwall.jpg");
	glBindTexture(GL_TEXTURE_2D, tex[wallId]);
	bitmapWidth = FreeImage_GetWidth(bitmap_data);
	bitmapHeight = FreeImage_GetHeight(bitmap_data);
	bitmapBits = FreeImage_GetBits(bitmap_data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapWidth, bitmapHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bitmapBits);
	FreeImage_Unload(bitmap_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_WRAP_BORDER, GL_REPEAT);
	// white texture from 1 pixel
	bitmapFormat = FreeImage_GetFileType("Programme/sun.png");
	bitmap_data = FreeImage_Load(bitmapFormat, "Programme/sun.png");
	glBindTexture(GL_TEXTURE_2D, tex[sunid]);
	bitmapWidth = FreeImage_GetWidth(bitmap_data);
	bitmapHeight = FreeImage_GetHeight(bitmap_data);
	bitmapBits = FreeImage_GetBits(bitmap_data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapWidth, bitmapHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bitmapBits);
	FreeImage_Unload(bitmap_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_WRAP_BORDER, GL_REPEAT);

	glUseProgram(program);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_STENCIL_TEST);

	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumBuffers, Buffers);

	generateBox24();
	generatePiramideExTop();
	generatePiramide();
	generateRectangle();
	generateCircle(1);

	locMV = glGetUniformLocation(program, "MVMatrix");
	locNM = glGetUniformLocation(program, "NormalMatrix");
	locM = glGetUniformLocation(program, "ModelMatrix"); 
	locHigth = glGetUniformLocation(program, "sunHight");
	locRichtungBool = glGetUniformLocation(program, "richBool");
	locSpotBool = glGetUniformLocation(program, "spotBool");
}

void lichtBerechnung() {
	ModelViewProjection = Projection*View*Model;
	ModelView = View*Model;
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
		{
			NormalMatrix[i][j] = ModelView[i][j];
		}
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
	glUniformMatrix4fv(locMV, 1, GL_FALSE, &ModelView[0][0]);
	glUniformMatrix3fv(locNM, 1, GL_FALSE, &NormalMatrix[0][0]);
	glUniformMatrix4fv(locM, 1, GL_FALSE, &Model[0][0]);
}

void drawFigures(void) {
	//// building
	//// roof s
	//// TEXTURE_ROOF
	glBindTexture(GL_TEXTURE_2D, tex[roofId]);

	Model = mat4(1.0);
	Model = translate(Model, vec3(-0, 2.0, -0));
	Model = scale(Model, vec3(5, 2.0, 5));
	lichtBerechnung();
	drawPiramideExTop();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-0, 6.0, -0));
	Model = scale(Model, vec3(4, 1, 4));
	lichtBerechnung();
	drawPiramideExTop();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-0, 9, -0));
	Model = scale(Model, vec3(3, 1, 3));
	lichtBerechnung();
	drawPiramide();

	// wall s
	// TEXTURE_WALL
	glBindTexture(GL_TEXTURE_2D, tex[wallId]);

	Model = mat4(1.0);
	Model = translate(Model, vec3(-0, -2.0, -0));
	Model = scale(Model, vec3(4, 2.0, 4));
	lichtBerechnung();
	drawBox24();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-0, 4.0, -0));
	Model = scale(Model, vec3(2.5, 1.0, 2.5));
	lichtBerechnung();
	drawBox24();

	Model = mat4(1.0);
	Model = translate(Model, vec3(-0, 7.0, -0));
	Model = scale(Model, vec3(2.0, 1.0, 2.0));
	lichtBerechnung();
	drawBox24();

	// floor s
	// TEXTURE_FLOOR
	glBindTexture(GL_TEXTURE_2D, tex[floorID]);

	Model = mat4(1.0);
	Model = translate(Model, vec3(0, -4.0, 0.0));
	Model = scale(Model, vec3(8.0, 0.1, 8.0));
	lichtBerechnung();
	drawBox24();

	// sun
	glBindTexture(GL_TEXTURE_2D, tex[sunid]);
	Model = mat4(1.0);
	Model = scale(Model, vec3(2, 2.0, 2));
	Model = translate(Model, vec3(0, currHight, -20.0));
	lichtBerechnung();
	drawBox24();
}

void display(void)
{
	glClearColor(0.8, 0.8, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//texturen
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	GLfloat viewpoint[3];
	viewpoint[0] = dist*sin(beta)*sin(alpha);
	viewpoint[1] = dist*cos(beta);
	viewpoint[2] = dist*sin(beta)*cos(alpha);

	// locations
	Location = glGetUniformLocation(program, "ModelViewProjection");
	locMV = glGetUniformLocation(program, "MVMatrix");
	locNM = glGetUniformLocation(program, "NormalMatrix");

	NormalMatrix = mat3(1.0);
	Projection = mat4(1.0);
	Model = mat4(1.0);
	View = mat4(1.0);
	ModelView = View*Model;
	ModelViewProjection;

	Projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.f);
	View = glm::lookAt(
		glm::vec3(viewpoint[0], viewpoint[1], viewpoint[2]),
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(0.0, cos(beta - 3.141593*0.5), 0.0)
	);
	
	glStencilFunc(GL_ALWAYS, 0x01, 0x1);

	glViewport(512, 0, 512, 512);
	drawFigures();

	View = glm::lookAt(
		glm::vec3(0, currHight+1, -20.0),
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(0.0, 1.0, 0.0)
	);

	glViewport(0, 0, 512, 512);
	drawFigures();


	glFlush();
}

void reshape(int w, int h) {
	glViewport(0,0,w,h);
	width = w;
	height = h;
}

vec3 sunColor = vec3(0.7, 0, 0);
bool richtungsBool = true;
bool spotBool = true;

void idle(void) {
	if (currHight < -hightLimit) {
		downwards = !downwards;
		currHight = -hightLimit;
	}
	else if (currHight > hightLimit) {
		downwards = !downwards;
		currHight = hightLimit;
	}
	if (downwards) {
		currHight -= 0.02f;
		sunColor += vec3(0.004, 0, 0);
	}
	else {
		currHight += 0.02f;
		sunColor -= vec3(0.004, 0, 0);
	}
	//uniform sun color
	GLuint locSunColor = glGetUniformLocation(program, "sunColor");
	glUniform3f(locSunColor, sunColor.x, sunColor.y, sunColor.z);
	glUniform1f(locHigth, currHight);
	glUniform1f(locRichtungBool, richtungsBool);
	glUniform1f(locSpotBool, spotBool);

	std::cout << currHight << " ? " << hightLimit << std::endl;
	display();
	Sleep(10);
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
		case '1':
			richtungsBool = !richtungsBool;
			display();
			break;
		case '2':
			spotBool = !spotBool;
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
	GLint mposx = mouseX; GLint mposy = height - mouseY;
	printf("%d,%d\n", mouseX, mouseY);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(512*2, 512);
	glutInitContextVersion(4, 2);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow("beleg Burenko s76905");
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