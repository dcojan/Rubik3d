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
		M_FRONT,
		M_RIGHT,
		M_BACK,
		M_LEFT,
		M_UP,
		M_DOWN,
		M_REV_FRONT,
		M_REV_RIGHT,
		M_REV_BACK,
		M_REV_LEFT,
		M_REV_UP,
		M_REV_DOWN,
		M_DOUBLE_FRONT,
		M_DOUBLE_RIGHT,
		M_DOUBLE_BACK,
		M_DOUBLE_LEFT,
		M_DOUBLE_UP,
		M_DOUBLE_DOWN,
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
extern const glm::vec3 transtab[27];
extern GLuint position_vbo;
extern GLuint post_rotation_vbo;
extern glm::mat4 positions[27];
extern glm::mat4 post_rotation[27];

int			rubik3d(std::list<t_move> *shuffle, std::list<t_move> *solution);
void		init_sdl(sdl_t *sdl_var);
void		init_glew();
void    init_vao(GLuint *vertexArrayId);
GLuint  init_vertex_buffer();
GLuint  init_color_buffer();
void    init_position_buffer();
void    init_post_rotation_buffer();

std::list<t_move>	*parse(std::string entry);

void		clean_sdl(sdl_t *sdl_var);
GLuint loadShaders();

#endif
