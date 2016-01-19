#include <rubik3d.hpp>

const GLchar*		vertexSource =
	"#version 330 core\n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;"
	"layout(location = 1) in vec3 vertexColor;"
	"uniform mat4 MVP;"
//	"in vec3 position;"
	//"in vec3 color;"
	"out vec3 fragmentColor;"
	"void main() {"
	"	fragmentColor = vertexColor;"
	"gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);"
	"}";

const GLchar*		fragmentSource = // without uniform
	"#version 330 core\n"
	"in vec3 fragmentColor;"
	"out vec3 outColor;"
	"void main() {"
	"	outColor = fragmentColor;" // R G B Alpha
	"}";
