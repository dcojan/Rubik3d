#ifndef CONTROLS_HPP
#define CONTROLS_HPP

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void      init_camera();
void      move_camera(int x, int y);
t_move		get_key_move(SDL_Event *windowEvent);

#endif
