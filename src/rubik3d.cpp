#include <rubik3d.hpp>

const int FRAMES_PER_SECOND = 60;
const double SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

void 		main_loop(GLuint shaderProgram, sdl_t	&sdl_var, std::list<t_move> *shuffle, std::list<t_move> *solution)
{
	SDL_Event		windowEvent;
	auto 				t_start = std::chrono::high_resolution_clock::now();
	auto 				currentTime = std::chrono::high_resolution_clock::now();
	auto				lastTime = currentTime;
	bool				keyrot_start = true;
	bool				launch_shuffle = false;
	float				rad = 0.0f;
	t_move			move = NONE;
  bool        quit = false;

	double			sleep_time = 0;
	double			next_game_tick = 0;
	int					nbFrames = 0;

	glUseProgram(shaderProgram);

	while (quit == false)
	{
		currentTime = std::chrono::high_resolution_clock::now();

		/// FRAMERATE CONTROL
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - t_start).count();
		if (sleep_time >= 0)
		{
			usleep(sleep_time * 1000);
		}
		else
			printf("WTF !!!\n");

		// FRAME TIME MESURE
		double difftime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime).count();
		nbFrames++;
		if (difftime >= 1.0 ){ // If last prinf() was more than 1 sec ago
		    // printf and reset timer
		    printf("%f ms/frame\n", 1000.0/double(nbFrames));
		    nbFrames = 0;
		    lastTime += std::chrono::seconds(1);
		}

		// KEY EVENT
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

		// GET MOVE ID FROM PREDEFINED SHUFFLE MOVE SEQUENCE
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

		// UPDATE BUFFERS
			if (move != NONE)
			{
				if (keyrot_start)
				{
					rad = 0.0f;
					keyrot_start = false;
				}
				if (apply_move(move, rad) == false)
				{
					float speed = 90.0f / (float)(FRAMES_PER_SECOND);
					rad += speed * 2;
				}
				else
				{
					move = NONE;
					keyrot_start = true;
				}
			}
		// CLEAR SCREEN
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		// computeMatricesFromInputs();
		// glm::mat4 ProjectionMatrix = getProjectionMatrix();
		// glm::mat4 ViewMatrix = getViewMatrix();
		// glm::mat4 ModelMatrix = glm::mat4(1.0);
		// glm::mat4 MVP = ProjectionMatrix * ViewMatrix * Model;

		// RENDER
		draw_cube(shaderProgram);
		SDL_GL_SwapWindow(sdl_var.window);
	}
}

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

	// INIT BUFFERS
  GLuint vertexArrayId;
	init_vao(&vertexArrayId);
	GLuint	vertexBuffer = init_vertex_buffer();
	GLuint	colorBuffer = init_color_buffer();
	init_position_buffer();
	init_post_rotation_buffer();

	// INIT SHADERS
	GLuint	shaderProgram = loadShaders();

	// INIT VIEW AND PROJECTIONS
	init_camera();

	// INIT 3D ARRAY
	init_rubik();

	main_loop(shaderProgram, sdl_var, shuffle, solution);

	glDisableVertexAttribArray(0); //vertices
	glDisableVertexAttribArray(1); //color
	for( int c = 0; c < 4; c++ )
	{
		glDisableVertexAttribArray(2 + c); //position
		glDisableVertexAttribArray(8 + c); //rotation
	}
	glDeleteProgram(shaderProgram); // del shader program
	glDeleteBuffers(1, &vertexBuffer); //del vertex buffer
	glDeleteBuffers(1, &colorBuffer); //del vertex buffer
	glDeleteBuffers(1, &position_vbo); //del vertex buffer
  glDeleteBuffers(1, &post_rotation_vbo); //del vertex buffer
  glDeleteVertexArrays(1, &vertexArrayId); //del vao
	clean_sdl(&sdl_var);
  return 0;
}
