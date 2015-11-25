#include "GLHelpers.h"


#include "GLEW\glew.h"
#include "GLFW\glfw3.h"

//#define STB_IMAGE_IMPLEMENTATION


#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace reng;

// ---- Local helpers ----


void APIENTRY openglCallbackFunction(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
{

	cout << "---------------------opengl-callback-start------------" << endl;
	cout << "message: " << message << endl;
	cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		cout << "OTHER";
		break;
	}
	cout << endl;

	cout << "id: " << id;
	cout << "severity: ";
	switch (severity){
	case GL_DEBUG_SEVERITY_LOW:
		cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		cout << "HIGH";
		break;
	}
	cout << endl;
	cout << "---------------------opengl-callback-end--------------" << endl;
}


string readFile(const char* fileName)
{
	ifstream ifs(fileName, ios::in | ios::binary | ios::ate);
	if (!ifs.is_open()) return "";

	ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, ios::beg);

	vector<char> bytes((unsigned int)fileSize);
	ifs.read(&bytes[0], fileSize);

	return string(&bytes[0], (unsigned int)fileSize);
}

void GLHelpers::TurnOnDebugLogging()
{

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	//glDebugMessageCallback(openglCallbackFunction, nullptr);
	GLuint unusedIds = 0;
	glDebugMessageControl(GL_DONT_CARE,
		GL_DONT_CARE,
		GL_DONT_CARE,
		0,
		&unusedIds,
		true);
}
