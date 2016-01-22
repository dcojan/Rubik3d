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
  if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1)
    printf("relative mouse mode not supported\n");

	while (quit == false)
	{
		currentTime = std::chrono::high_resolution_clock::now();

		/// FRAMERATE CONTROL
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - t_start).count();
		if (sleep_time >= 0)
		{
			usleep(sleep_time * 1000);
      //flush all recorded moves during sleep time
      SDL_FlushEvent(SDL_MOUSEMOTION);
		}
    // else
		// 	printf("WTF !!!\n");

		// FRAME TIME MESURE
		double difftime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime).count();
		nbFrames++;
		if (difftime >= 1.0 ){ // If last prinf() was more than 1 sec ago
		    // printf and reset timer
		  //  printf("%f ms/frame\n", 1000.0/double(nbFrames));
		    nbFrames = 0;
		    lastTime += std::chrono::seconds(1);
		}

		// KEY EVENT
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
			if (windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE)
        {
          // printf("esc_key\n");
          break;
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN &&
            windowEvent.button.button == SDL_BUTTON_LEFT)
        {
          // printf("LEFT CLICK DOWN\n");
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONUP &&
        windowEvent.button.button == SDL_BUTTON_LEFT)
        {
          // printf("LEFT CLICK UP\n");
        }
        else if (windowEvent.type == SDL_MOUSEMOTION)
        {
          int x;
          int y;
          SDL_GetRelativeMouseState(&x, &y);
          // printf("mouse relative position : %d %d\n",x, y);
          move_camera(x, y);
        }

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
