#include <rubik3d.hpp>

const GLchar*		vertexSource =
	"#version 330 core\n"
	"layout(location = 0) in vec3 in_vertex;"
	// "layout(location = 1) in vec3 vertexColor;"
	"layout(location = 1) in vec2 vertexUV;"
	"layout(location = 2) in mat4 pos;" //instance data
	"layout(location = 8) in mat4 post_rotation;" //instance data

	"uniform mat4 MVP;"

	// "out vec3 fragmentColor;"
	"out vec2 UV;"

	"void main() {"
	// "	fragmentColor = vertexColor;"
	"UV = vertexUV;"
	" float scale = 0.5;"
	" gl_Position = MVP * post_rotation * pos * vec4(scale * in_vertex, 1.0);"
	// " gl_Position = MVP * vec4(in_vertex, 1.0);"
	"}";

const GLchar*		fragmentSource =
	"#version 330 core\n"
	"in vec2 UV;"
	// "in vec3 fragmentColor;"
	"out vec3 outColor;"
	"uniform sampler2D myTextureSampler;"
	"void main() {"
	" outColor = texture( myTextureSampler, UV).rgb;"
	// "	outColor = fragmentColor;" // R G B Alpha
	"}";
