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
		case (SDLK_f): return M_FRONT;
		case (SDLK_r): return M_RIGHT;
		case (SDLK_b): return M_BACK;
		case (SDLK_l): return M_LEFT;
		case (SDLK_u): return M_UP;
		case (SDLK_d): return M_DOWN;
		case (SDLK_g): return M_REV_FRONT;
		case (SDLK_s): return M_REV_RIGHT;
		case (SDLK_c): return M_REV_BACK;
		case (SDLK_m): return M_REV_LEFT;
		case (SDLK_v): return M_REV_UP;
		case (SDLK_e): return M_REV_DOWN;
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

void move_camera(int x, int y)
{
	float speed = 3.0f;
	static glm::vec3 position = glm::vec3(4.f,3.f, 5.f);
	float yawAngle = 1.0f * speed;
 	float pitchAngle = 1.0f * speed;

	glm::vec3 target = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 camera_up_vector = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 target_to_camera_vector = position - target;
	glm::vec3 camera_right_vector = glm::normalize(glm::cross(target_to_camera_vector, camera_up_vector));

	pitchAngle *= y / 20.0f;
	glm::quat pitch = glm::angleAxis(glm::radians(pitchAngle), camera_right_vector);
	position = glm::vec3(pitch * glm::vec4(position, 1.0f));

	yawAngle *= -x / 20.0f;
	glm::quat yaw = glm::quat(glm::radians(glm::vec3(0.0f, yawAngle, 0.0f)));
	position = glm::vec3(yaw * glm::vec4(position, 1.0f));
//	printf("x %f   y %f   w %f \n", position.x, position.y, position.z);

	ViewMatrix = glm::lookAt(
 								position, // Camera is at (4,3,3), in World Space
 								target, // and looks at the origin
 								camera_up_vector  // Head is up (set to 0,-1,0 to look upside-down)
 								);
}
