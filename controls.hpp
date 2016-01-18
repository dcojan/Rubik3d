#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void      computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void      init_camera();
t_move		get_key_move(SDL_Event *windowEvent);

#endif
