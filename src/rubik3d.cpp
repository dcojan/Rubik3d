#include <rubik3d.hpp>

int			rubik3d(std::list<t_move> *shuffle, std::list<t_move> *solution)
{
	sdl_t	sdl_var;
	init_sdl(&sdl_var);
	init_glew();

	// OPENGL CONFIGURATION
	glFrontFace( GL_CCW );
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); //doesn't change a thing
	glDepthFunc(GL_LESS); // doesnt't change a thing
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	// INIT TEXTURES
	std::string cpath = std::string(__FILE__);
	cpath = cpath.substr(0, cpath.find_last_of("/\\"));
	cpath = cpath.substr(0, cpath.find_last_of("/\\"));
	cpath += "/texture/uvtemplate.tga";
	GLuint    Texture = loadTGA(cpath.c_str());
	// INIT BUFFERS
  GLuint vertexArrayId;
	init_vao(&vertexArrayId);
	GLuint	vertexBuffer = init_vertex_buffer();
	// GLuint	colorBuffer = init_color_buffer();
	GLuint  textureBuffer = init_texture_buffer();

	init_position_buffer();
	init_post_rotation_buffer();

	// INIT SHADERS
	GLuint	shaderProgram = loadShaders();

	// INIT VIEW AND PROJECTIONS
	init_camera();

	// INIT 3D ARRAY
	init_rubik();

	// MAIN STUFF
	main_loop(shaderProgram, sdl_var, shuffle, solution);

	// CLEANING
	glDisableVertexAttribArray(0); //vertices
	glDisableVertexAttribArray(1); //color
	for( int c = 0; c < 4; c++ )
	{
		glDisableVertexAttribArray(2 + c); //position
		glDisableVertexAttribArray(8 + c); //rotation
	}
	glDeleteProgram(shaderProgram); // del shader program
	glDeleteBuffers(1, &vertexBuffer); //del vertex buffer
	glDeleteBuffers(1, &textureBuffer); //del vertex buffer
	glDeleteTextures(1, &Texture);
	// glDeleteBuffers(1, &colorBuffer); //del vertex buffer
	glDeleteBuffers(1, &position_vbo); //del vertex buffer
  glDeleteBuffers(1, &post_rotation_vbo); //del vertex buffer
  glDeleteVertexArrays(1, &vertexArrayId); //del vao
	clean_sdl(&sdl_var);
  return 0;
}
