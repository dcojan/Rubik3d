#ifndef RUBIK3D_HPP
# define RUBIK3D_HPP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //functions to ease the calculation of the view and projection matrices
#include <glm/gtc/type_ptr.hpp> //adds functionality for converting a matrix object into a float array for usage in OpenGL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <list>

typedef enum 			e_move
{
		MOVE_FRONT,
		MOVE_RIGHT,
		MOVE_BACK,
		MOVE_LEFT,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_REV_FRONT,
		MOVE_REV_RIGHT,
		MOVE_REV_BACK,
		MOVE_REV_LEFT,
		MOVE_REV_UP,
		MOVE_REV_DOWN,
		MOVE_DOUBLE_FRONT,
		MOVE_DOUBLE_RIGHT,
		MOVE_DOUBLE_BACK,
		MOVE_DOUBLE_LEFT,
		MOVE_DOUBLE_UP,
		MOVE_DOUBLE_DOWN,
		NONE,
}									t_move;

#include <rubik.hpp>
#define WIDTH 		800
#define HEIGHT 		600
#include <controls.hpp>

typedef struct		sdl_s
{
	SDL_Window* window;
	SDL_GLContext context;
}					sdl_t;

extern const GLfloat g_vertex_buffer_data[108];
extern const GLfloat g_color_buffer_data[108];
extern const GLfloat g_cube_color_buffer_data[108];
extern const GLchar*		vertexSource;
extern const GLchar*		fragmentSource;

int			rubik3d(std::list<t_move> *shuffle, std::list<t_move> *solution);
void		init_sdl(sdl_t *sdl_var);
void		init_glew();
void    init_vao(GLuint *vertexArrayId);
GLuint  init_vertex_buffer();
GLuint  init_color_buffer();
std::list<t_move>	*parse(std::string entry);

void		clean_sdl(sdl_t *sdl_var);
GLuint loadShaders();

#endif
