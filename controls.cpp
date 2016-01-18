#include <rubik3d.hpp>

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
// FoV : lvl of Zoom.
// 80 degree : very wide angle, huge deformation
// 60 - 45 degree : standard
// 20 degree : big zoom
float speed = 3.0f;
float mouseSpeed = 0.005f;

t_move		get_key_move(SDL_Event *windowEvent)
{
	switch (windowEvent->key.keysym.sym)
	{
		case (SDLK_f): return MOVE_FRONT;
		case (SDLK_r): return MOVE_RIGHT;
		case (SDLK_b): return MOVE_BACK;
		case (SDLK_l): return MOVE_LEFT;
		case (SDLK_u): return MOVE_UP;
		case (SDLK_d): return MOVE_DOWN;
		case (SDLK_g): return MOVE_REV_FRONT;
		case (SDLK_s): return MOVE_REV_RIGHT;
		case (SDLK_c): return MOVE_REV_BACK;
		case (SDLK_m): return MOVE_REV_LEFT;
		case (SDLK_v): return MOVE_REV_UP;
		case (SDLK_e): return MOVE_REV_DOWN;
	}
	return NONE;
}

void init_camera() {
	//++++++++++++++++++++++++++++++++++++++++++++++++++ CAMERA
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	 ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	 // Camera matrix
	 ViewMatrix = glm::lookAt(
	                glm::vec3(4,3,5), // Camera is at (4,3,3), in World Space
	                glm::vec3(0,0,0), // and looks at the origin
	                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	                );
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

}

void computeMatricesFromInputs()
{
  static auto t_start = std::chrono::high_resolution_clock::now();
  auto        t_now = std::chrono::high_resolution_clock::now();
  float       deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
  glm::vec3   position = glm::vec3(0,0,5);
  int xpos, ypos;
  SDL_GetMouseState(&xpos, &ypos);

  horizontalAngle += mouseSpeed * deltaTime * float(WIDTH/2 - (xpos));
  verticalAngle   += mouseSpeed * deltaTime * float(HEIGHT/2 - (ypos));
  glm::vec3 direction(
       cos(verticalAngle) * sin(horizontalAngle),
       sin(verticalAngle),
       cos(verticalAngle) * cos(horizontalAngle)
  );
  glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
  // Up vector
	glm::vec3 up = glm::cross( right, direction );

	// // Move forward
	// if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
	// 	position += direction * deltaTime * speed;
	// }
	// // Move backward
	// if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
	// 	position -= direction * deltaTime * speed;
	// }
	// // Strafe right
	// if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
	// 	position += right * deltaTime * speed;
	// }
	// // Strafe left
	// if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
	// 	position -= right * deltaTime * speed;
	// }
  float FoV = initialFoV;
  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	t_start = t_now;
}
