#include <rubik3d.hpp>

void 		main_loop(GLuint shaderProgram, sdl_t	&sdl_var, std::list<t_move> *shuffle, std::list<t_move> *solution)
{
	SDL_Event		windowEvent;
	auto				t_start = std::chrono::high_resolution_clock::now();
	bool				keyrot_start = true;
	// bool				click = false;
	bool				launch_shuffle = false;
	float				rad = 0.0f;
	t_move			move = NONE;
  bool        quit = false;

	glUseProgram(shaderProgram);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); //doesn't change a thing
	glDepthFunc(GL_LESS); // doesnt't change a thing
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	while (quit == false)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
			if (windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
			if (shuffle)
			{
				if (windowEvent.type == SDL_KEYUP &&
          windowEvent.key.keysym.sym == SDLK_RETURN)
					launch_shuffle = true;
			}
	    else if (solution == NULL)
      {
			     if (windowEvent.type == SDL_KEYUP && move == NONE)
						   move = get_key_move(&windowEvent);
      }
      else
      {
        if (windowEvent.type == SDL_KEYUP &&
          windowEvent.key.keysym.sym == SDLK_RETURN &&
          move == NONE)
          {
            if (solution->size() != 0)
            {
              move = solution->front();
              solution->pop_front();
            }
            else
						{
							printf("quit\n");
              quit = true;
						}
          }
      }
		// 	if (windowEvent.type == SDL_MOUSEBUTTONDOWN &&
		// 			windowEvent.button.button == SDL_BUTTON_LEFT)
		// 	{
		// 		printf("LEFT CLICK DOWN\n");
		// 	}
		// 	if (windowEvent.type == SDL_MOUSEBUTTONUP &&
		// 	windowEvent.button.button == SDL_BUTTON_LEFT)
		// 	{
		// 		printf("LEFT CLICK UP\n");
		//
		// 	}
		}
		if (launch_shuffle)
		{
			if (move == NONE)
			{
				if (shuffle->size() != 0)
				{
					move = shuffle->front();
					shuffle->pop_front();
				}
				else
				{
					shuffle = NULL;
					launch_shuffle = false;
				}
			}
		}

		glm::mat4 Rot;
			if (move != NONE)
			{
				if (keyrot_start)
				{
					rad = 1.0f;
					keyrot_start = false;
				}
				if (rad <= 90.0f)
				{
					usleep(5000);
					apply_move(move, rad);
					rad++;
				}
				else
				{
					move = NONE;
					keyrot_start = true;
				}
			}
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //clear the screen

		// auto t_now = std::chrono::high_resolution_clock::now();
		// float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

		// computeMatricesFromInputs();
		// glm::mat4 ProjectionMatrix = getProjectionMatrix();
		// glm::mat4 ViewMatrix = getViewMatrix();
		// glm::mat4 ModelMatrix = glm::mat4(1.0);
		// glm::mat4 MVP = ProjectionMatrix * ViewMatrix * Model;

		draw_cube(shaderProgram);
		SDL_GL_SwapWindow(sdl_var.window);
	}
}

int			rubik3d(std::list<t_move> *shuffle, std::list<t_move> *solution)
{
	sdl_t	sdl_var;
	init_sdl(&sdl_var);
	init_glew();

  GLuint vertexArrayId;
	init_vao(&vertexArrayId);
	GLuint	shaderProgram = loadShaders();
	GLuint	vertexBuffer = init_vertex_buffer();
	GLuint	colorBuffer = init_color_buffer();
	init_rubik();
	init_camera();

	main_loop(shaderProgram, sdl_var, shuffle, solution);

	glDisableVertexAttribArray(0); //vertices
	glDisableVertexAttribArray(1); //color
	glDeleteProgram(shaderProgram); // del shader program
	glDeleteBuffers(1, &vertexBuffer); //del vertex buffer
  glDeleteBuffers(1, &colorBuffer); //del vertex buffer
  glDeleteVertexArrays(1, &vertexArrayId); //del vao
	clean_sdl(&sdl_var);
  return 0;
}
