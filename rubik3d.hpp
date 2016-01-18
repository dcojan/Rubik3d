#ifndef RUBIK3D_HPP
# define RUBIK3D_HPP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //functions to ease the calculation of the view and projection matrices
#include <glm/gtc/type_ptr.hpp> //adds functionality for converting a matrix object into a float array for usage in OpenGL
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <rubik.hpp>
#define WIDTH 		800
#define HEIGHT 		600
#include <controls.hpp>
typedef struct		sdl_s
{
	SDL_Window* window;
	SDL_GLContext context;
}					sdl_t;

typedef struct		cube_s
{

}									cube_t;

extern const GLfloat g_vertex_buffer_data[108];
extern const GLfloat g_color_buffer_data[108];
extern const GLfloat g_cube_color_buffer_data[108];
extern const GLchar*		vertexSource;
extern const GLchar*		fragmentSource;

void		init_sdl(sdl_t *sdl_var);
void		init_glew();
void		clean_sdl(sdl_t *sdl_var);
GLuint loadShaders();

#endif
