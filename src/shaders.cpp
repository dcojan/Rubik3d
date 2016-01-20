#include <rubik3d.hpp>


void compile_shader(const GLchar* text, const GLuint& program, const GLenum& type)
{
	GLuint	id = glCreateShader(type);
	glShaderSource(id, 1, &text, NULL);
	glCompileShader(id);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	 }
	 glAttachShader(program, id);
	 glLinkProgram(program);

	 glDeleteShader(id);

	 glGetShaderiv(program, GL_COMPILE_STATUS, &Result);
 		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
 		if ( InfoLogLength > 0 ){
 		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
 		glGetShaderInfoLog(id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
 		printf("%s\n", &VertexShaderErrorMessage[0]);
 	 }
}


GLuint loadShaders()
{
		GLuint	program = glCreateProgram();

		compile_shader(vertexSource, program, GL_VERTEX_SHADER);
		compile_shader(fragmentSource, program, GL_FRAGMENT_SHADER);
		return program;
}
