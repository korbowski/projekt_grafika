#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include <list>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"
#include "Texture.h"

GLuint programColor;
GLuint programTexture;
GLuint sunTexture;
GLuint sunColor;
GLuint GLOBAL_VARIABLE;
GLuint THE_SUN;
GLuint MERKURY;
GLuint WENUS;
GLuint ZIEMIA;
GLuint MARS;
GLuint JOWISZ;
GLuint SATURN;
GLuint URAN;
GLuint NEPTUN;
GLuint MOON;
GLuint SPACE;

std::list<std::tuple<glm::vec3, glm::vec3, float>> gunfire = {};

Core::Shader_Loader shaderLoader;

obj::Model sphereModel;
obj::Model square;

float lastX = 600.0f; // Pozycja pocz¹tkowa x myszki
float lastY = 400.0f; // Pozycja pocz¹tkowa y myszki
bool firstMouse = true;

Core::Camera camera(glm::vec3(-5, 0, 0), glm::vec3(0, 1, 0), -90.0f, 0.0f);

glm::mat4 perspectiveMatrix;

glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, -0.9f, -1.0f));

float angleSpeed = 0.1f;
float moveSpeed = 0.1f;

void drawObjectTextureSun(obj::Model* model, glm::mat4 modelMatrix, GLuint textureID)
{
	GLuint program = sunTexture;

	glUseProgram(program);
	Core::SetActiveTexture(textureID, "sampler2dtype", 1, 0);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * camera.createViewMatrix() * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}
void drawObjectTexture(obj::Model* model, glm::mat4 modelMatrix, GLuint textureID)
{
	GLuint program = programTexture;

	glUseProgram(program);
	Core::SetActiveTexture(textureID, "sampler2dtype", 1, 0);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * camera.createViewMatrix() * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}


void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glm::mat4 rotation;
	glm::mat4 translationMerkury;
	glm::mat4 translationWenus;
	glm::mat4 translationZiemia;
	glm::mat4 translationMars;
	glm::mat4 translationJowisz;
	glm::mat4 translationSaturn;
	glm::mat4 translationUran;
	glm::mat4 translationNeptun;
	glm::mat4 translationKsiezyc;

	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	rotation[0][0] = cos(time);
	rotation[2][0] = sin(time);
	rotation[0][2] = -sin(time);
	rotation[2][2] = cos(time);

	translationMerkury[3][0] = 10 * sin(0.9 * time);
	translationMerkury[3][2] = 10 * cos(0.9 * time);
	translationWenus[3][0] = 15 * sin(0.7 * time);
	translationWenus[3][2] = 15 * cos(0.7 * time);
	translationZiemia[3][0] = 20 * sin(0.5 * time);
	translationZiemia[3][2] = 20 * cos(0.5 * time);
	translationMars[3][0] = 25 * sin(0.3 * time);
	translationMars[3][2] = 25 * cos(0.3 * time);
	translationJowisz[3][0] = 30 * sin(0.1 * time);
	translationJowisz[3][2] = 30 * cos(0.1 * time);
	translationSaturn[3][0] = 35 * sin(0.05 * time);
	translationSaturn[3][2] = 35 * cos(0.05 * time);
	translationUran[3][0] = 40 * sin(0.02 * time);
	translationUran[3][2] = 40 * cos(0.02 * time);
	translationNeptun[3][0] = 45 * sin(0.005 * time);
	translationNeptun[3][2] = 45 * cos(0.005 * time);
	translationKsiezyc[3][0] = 4 * sin(0.1 * time);
	translationKsiezyc[3][2] = 4 * cos(0.1 * time);

	drawObjectTextureSun(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * glm::scale(glm::vec3(2.8f)), THE_SUN);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * translationMerkury * rotation * glm::scale(glm::vec3(0.5f)), MERKURY);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * translationWenus * rotation * glm::scale(glm::vec3(0.8f)), WENUS);
	glm::mat4 finalmatrixZiemia = glm::translate(glm::vec3(0, 0, 0)) * translationZiemia * rotation * glm::scale(glm::vec3(1.0f));
	drawObjectTexture(&sphereModel, finalmatrixZiemia, ZIEMIA);
	drawObjectTexture(&sphereModel, (finalmatrixZiemia * translationKsiezyc * glm::scale(glm::vec3(0.4f))), MOON);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * translationMars * rotation * glm::scale(glm::vec3(0.7f)), MARS);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * translationJowisz * rotation * glm::scale(glm::vec3(2.0f)), JOWISZ);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * translationSaturn * rotation * glm::scale(glm::vec3(1.8f)), SATURN);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * translationUran * rotation * glm::scale(glm::vec3(1.6f)), URAN);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * translationNeptun * rotation * glm::scale(glm::vec3(1.4f)), NEPTUN);
	drawObjectTextureSun(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * glm::scale(glm::vec3(70.0f)), SPACE);
	glutSwapBuffers();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram("shaders/shader_color.vert", "shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");
	sunTexture = shaderLoader.CreateProgram("shaders/shader_tex_sun.vert", "shaders/shader_tex_sun.frag");
	sphereModel = obj::loadModelFromFile("models/sphere.obj");
	square = obj::loadModelFromFile("models/cube.obj");
	GLOBAL_VARIABLE = Core::LoadTexture("textures/earth.png");
	THE_SUN = Core::LoadTexture("textures/sun.png");
	MERKURY = Core::LoadTexture("textures/merkury.png");
	WENUS = Core::LoadTexture("textures/wenus.png");
	ZIEMIA = Core::LoadTexture("textures/earth.png");
	MARS = Core::LoadTexture("textures/mars.png");
	JOWISZ = Core::LoadTexture("textures/jowisz.png");
	SATURN = Core::LoadTexture("textures/saturn.png");
	URAN = Core::LoadTexture("textures/uran.png");
	NEPTUN = Core::LoadTexture("textures/neptun.png");
	MOON = Core::LoadTexture("textures/deathstar.png");
	SPACE = Core::LoadTexture("textures/SPACE.PNG");

	perspectiveMatrix = camera.createPerspectiveMatrix(0.1f, 100.0f);
}


void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
	shaderLoader.DeleteProgram(sunTexture);
}

void idle()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': camera.ProcessKeyboardMovement(0, moveSpeed); break;
	case 's': camera.ProcessKeyboardMovement(1, moveSpeed); break;
	case 'a': camera.ProcessKeyboardMovement(2, moveSpeed); break;
	case 'd': camera.ProcessKeyboardMovement(3, moveSpeed); break;

	case 'p': moveSpeed = 0.5f; angleSpeed = 0.5f; break;
	case 'y': moveSpeed = 0.1f; angleSpeed = 0.1f; break;
	}
}

void mouseCallback(int x, int y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y;

	lastX = x;
	lastY = y;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Cymiñski Ciryt D¹browski");
	glewInit();
	init();
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseCallback);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	glutMainLoop();
	shutdown();
	return 0;
}
