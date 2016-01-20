#include <rubik3d.hpp>

void 		main_loop(GLuint shaderProgram, sdl_t	&sdl_var, std::list<t_move> *shuffle, std::list<t_move> *solution)
{
	SDL_Event		windowEvent;
	auto				lastTime = std::chrono::high_resolution_clock::now();
	bool				keyrot_start = true;
	// bool				click = false;
	bool				launch_shuffle = false;
	float				rad = 0.0f;
	t_move			move = NONE;
  bool        quit = false;

	int nbFrames = 0;
	glUseProgram(shaderProgram);
	while (quit == false)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		double difftime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime).count();
		nbFrames++;
		if (difftime >= 1.0 ){ // If last prinf() was more than 1 sec ago
		    // printf and reset timer
		    printf("%f ms/frame\n", 1000.0/double(nbFrames));
		    nbFrames = 0;
		    lastTime += std::chrono::seconds(1);
		}

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
					rad = 0.0f;
					keyrot_start = false;
				}
				if (rad <= 90.0f)
				{
					// usleep(5000);
					apply_move(move, rad);
					rad += 2.0f;
				}
				else
				{
					move = NONE;
					keyrot_start = true;
				}
			}
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //clear the screen


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
	glFrontFace( GL_CCW );
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); //doesn't change a thing
	glDepthFunc(GL_LESS); // doesnt't change a thing
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);


  GLuint vertexArrayId;
	init_vao(&vertexArrayId);
	GLuint	vertexBuffer = init_vertex_buffer();
	GLuint	colorBuffer = init_color_buffer();

	glBindVertexArray( vertexArrayId );


	//////////

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

	// for (int i = 0 ; i < 27 ; i++)
	// {
	// 	positions[i] = glm::translate(transtab[i]);
	// }
	// glBindBuffer( GL_ARRAY_BUFFER, position_vbo ); //bind vbo
	// //you need to upload sizeof( vec4 ) * number_of_cubes bytes, DYNAMIC_DRAW because it is updated per frame
	// glBufferData( GL_ARRAY_BUFFER, sizeof( glm::mat4 ) * 27, &positions[0][0], GL_STATIC_DRAW );

	printf("init position done\n");
	///////////

	//////////

	glGenBuffers( 1, &post_rotation_vbo ); //gen vbo
	glBindBuffer( GL_ARRAY_BUFFER, post_rotation_vbo ); //bind vbo
	//
	for( int c = 0; c < 4; c++ )
	{
		glEnableVertexAttribArray( 8 + c); //tell the location
		glVertexAttribPointer( 8 + c, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), pointer + c * sizeof(glm::vec4)); //tell other data
		glVertexAttribDivisor( 8 + c, 1); //is it instanced?
	}
	glBindBuffer( GL_ARRAY_BUFFER, post_rotation_vbo ); //bind vbo
	glBufferData( GL_ARRAY_BUFFER, sizeof( glm::mat4 ) * 27, &positions[0][0], GL_DYNAMIC_DRAW );

	///////////



///////
	GLuint	shaderProgram = loadShaders();


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
