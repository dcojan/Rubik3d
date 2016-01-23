#include <rubik3d.hpp>

void		init_sdl(sdl_t *sdl_var)
{
    SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	sdl_var->window = SDL_CreateWindow("OpenGL", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	sdl_var->context = SDL_GL_CreateContext(sdl_var->window);
}

void		init_glew()
{
	glewExperimental = GL_TRUE;
	glewInit();
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
}

void    init_vao(GLuint *vertexArrayId)
{
  glGenVertexArrays(1, vertexArrayId);
  glBindVertexArray(*vertexArrayId);
}

void    init_post_rotation_buffer()
{
  glGenBuffers( 1, &post_rotation_vbo ); //gen vbo
	glBindBuffer( GL_ARRAY_BUFFER, post_rotation_vbo ); //bind vbo
	char *pointer = 0;
	for( int c = 0; c < 4; c++ )
	{
		glEnableVertexAttribArray( 8 + c); //tell the location
		glVertexAttribPointer( 8 + c, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), pointer + c * sizeof(glm::vec4)); //tell other data
		glVertexAttribDivisor( 8 + c, 1); //is it instanced?
	}
	glBindBuffer( GL_ARRAY_BUFFER, post_rotation_vbo ); //bind vbo
	glBufferData( GL_ARRAY_BUFFER, sizeof( glm::mat4 ) * 27, &positions[0][0], GL_DYNAMIC_DRAW );
}

void    init_position_buffer()
{
    glGenBuffers( 1, &position_vbo ); //gen vbo
    glBindBuffer( GL_ARRAY_BUFFER, position_vbo ); //bind vbo

  	GLuint location = 2;
  	GLint components = 4; // 4 vertex attribute
  	GLenum type = GL_FLOAT;
  	GLboolean normalized = GL_FALSE;
  	GLsizei datasize = sizeof( glm::mat4 );
  	char* pointer = 0; //no other components
  	GLuint divisor = 1; //instanced
  	for( int c = 0; c < 4; c++ )
  	{
  		glEnableVertexAttribArray( location + c); //tell the location
  		glVertexAttribPointer( location + c, components, type, normalized, datasize, pointer + c * sizeof(glm::vec4)); //tell other data
  		glVertexAttribDivisor( location + c, divisor ); //is it instanced?
  	}
}

GLuint  init_vertex_buffer()
{
  	GLuint vertexBuffer;
  	glGenBuffers(1, &vertexBuffer);
  	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  	glEnableVertexAttribArray(0);
    return vertexBuffer;
}

GLuint  init_texture_buffer()
{
  	GLuint vertexBuffer;
  	glGenBuffers(1, &vertexBuffer);
  	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
  	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  	glEnableVertexAttribArray(1);
    return vertexBuffer;
}


GLuint  init_color_buffer()
{
  GLuint colorbuffer;
 glGenBuffers(1, &colorbuffer);
 glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
 glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_color_buffer_data), g_cube_color_buffer_data, GL_STATIC_DRAW);
 glEnableVertexAttribArray(1);
 glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
 glVertexAttribPointer(
      1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
      3,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0                          // array buffer offset
  );
  return colorbuffer;
}
