#include <rubik3d.hpp>

GLuint loadShaders()
{
		GLuint	vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		GLint Result = GL_FALSE;
		int InfoLogLength;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
	 	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	 	if ( InfoLogLength > 0 ){
		 	std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		 	glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		 	printf("%s\n", &VertexShaderErrorMessage[0]);
		 }

		GLuint	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
	 	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	 	if ( InfoLogLength > 0 ){
	 		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
	 		glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	 		printf("%s\n", &FragmentShaderErrorMessage[0]);
	 	}
		GLuint	shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		//glBindFragDataLocation(shaderProgram, 0, "outColor");
		glLinkProgram(shaderProgram);
		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		return shaderProgram;
}
