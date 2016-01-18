
#include <rubik3d.hpp>

int			main(int argc, char *argv[])
{
	sdl_t	sdl_var;
	init_sdl(&sdl_var);
	init_glew();

  GLuint vertexArrayId; // Vertex Array Object
  glGenVertexArrays(1, &vertexArrayId);
  glBindVertexArray(vertexArrayId); // set as the current one

	GLuint	shaderProgram = loadShaders();

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //make active buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0); //first attribute buffer : vertices

	// GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	// glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(posAttrib);

	GLuint colorbuffer;
	 glGenBuffers(1, &colorbuffer);
	 glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
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

//++++++++++++++++++++++++++++++++++++++++++++++++++ CAMERA
// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
 glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float)HEIGHT, 0.1f, 100.0f);
 // Camera matrix
 glm::mat4 View = glm::lookAt(
                glm::vec3(4,3,5), // Camera is at (4,3,3), in World Space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                );
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // Model matrix : an identity matrix (model will be at the origin)
 glm::mat4 Model = glm::mat4(1.0f);
 // Our ModelViewProjection : multiplication of our 3 matrices
 glm::mat4 Scale = glm::scale(glm::vec3(0.5f, 0.5f ,0.5f));

 glm::mat4 Trans1 = glm::translate(glm::vec3({1.0f, 0.0f, 0.0f}));

 glm::mat4 Trans2 = glm::translate(glm::vec3({0.0f, 0.0f, 0.0f}));

 // Get a handle for our "MVP" uniform
  // Only during the initialisation
  GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
  // Send our transformation to the currently bound shader, in the "MVP" uniform
  //+++++++++++++++++++++++++++++++++++++++++++++++++++
	glUseProgram(shaderProgram); //use our shaders
	glEnable(GL_DEPTH_TEST); //doesn't change a thing
	glDepthFunc(GL_LESS); // doesnt't change a thing
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	SDL_Event windowEvent;
	auto t_start = std::chrono::high_resolution_clock::now();
	bool keyrot = false;
	bool keyrot_start = true;
	float rad = 0.0f;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			// correspond to clicking the X button
			if (windowEvent.type == SDL_QUIT) break;
			// correspond to escape key - preferable with fullscreen
			if (windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
			if (windowEvent.type == SDL_KEYUP &&
					windowEvent.key.keysym.sym == SDLK_UP &&
				keyrot == false)
					{
						printf("KEY UP\n");
						keyrot = true;
					}
		}
			glm::mat4 Rot;
			if (keyrot == true)
			{
				printf("KEY ROT - rad = %f\n", rad);

				if (keyrot_start)
				{
					rad = 1.0f;
					keyrot_start = false;
				}
				if (rad <= 90.0f)
				{
					usleep(5000);
					printf("KEY ROT\n");

					Rot = glm::rotate(Rot, glm::radians(rad),glm::vec3(0.0f, 0.0f, 1.0f));
					glm::mat4 mvp1 = Projection * View * Rot * Trans1 * Scale * Model; // Remember, matrix multiplication is the other way around
					rad++;
				}
				else
				{
					printf("END KEY ROT\n");
					keyrot = false;
					keyrot_start = true;
				}
			}
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //clear the screen

		// auto t_now = std::chrono::high_resolution_clock::now();
		// float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		// APPLY CAMERA
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glm::mat4 mvp1 = Projection * View * Rot * Trans1 * Scale * Model; // Remember, matrix multiplication is the other way around

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp1[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glm::mat4 mvp2 = Projection * View * Trans2 * Rot * Scale * Model; // Remember, matrix multiplication is the other way around

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp2[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		SDL_GL_SwapWindow(sdl_var.window);
	}
	glDisableVertexAttribArray(0);

	  glDeleteProgram(shaderProgram); // del shader program
    glDeleteBuffers(1, &vertexBuffer); //del vertex buffer
    glDeleteVertexArrays(1, &vertexArrayId); //del vao

	  clean_sdl(&sdl_var);
    return 0;
}
