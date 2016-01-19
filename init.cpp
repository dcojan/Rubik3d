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
	printf("%u\n", vertexBuffer);
}

void    init_vao(GLuint *vertexArrayId)
{
  glGenVertexArrays(1, vertexArrayId);
  glBindVertexArray(*vertexArrayId);
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
