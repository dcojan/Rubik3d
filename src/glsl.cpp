#include <rubik3d.hpp>

const GLchar*		vertexSource =
	"#version 330 core\n"
	"layout(location = 0) in vec3 in_vertex;"
	"layout(location = 1) in vec3 vertexColor;"
	"layout(location = 2) in mat4 pos;" //instance data
	"layout(location = 8) in mat4 post_rotation;" //instance data

	"uniform mat4 MVP;"

	"out vec3 fragmentColor;"

	"void main() {"
	"	fragmentColor = vertexColor;"
	" float scale = 0.5;"
	" gl_Position = MVP * post_rotation * pos * vec4(scale * in_vertex, 1.0);"
	// " gl_Position = MVP * vec4(in_vertex, 1.0);"
	"}";

const GLchar*		fragmentSource = // without uniform
	"#version 330 core\n"
	"in vec3 fragmentColor;"
	"out vec3 outColor;"
	"void main() {"
	"	outColor = fragmentColor;" // R G B Alpha
	"}";
