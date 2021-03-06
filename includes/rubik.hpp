#ifndef RUBIK_HPP
# define RUBIK_HPP
#include <rubik3d.hpp>

typedef struct s_rubik
{
  int       id;
  glm::mat4 trans;
  glm::mat4 post_rot;
  glm::mat4 rot;
  glm::quat quat;
}              t_rubik;

typedef struct  s_trans_tab
{
  float   x;
  float   y;
  float   z;
}               t_trans_tab;

void      init_rubik(void);
glm::mat4 get_rubik_translation(int id);
void      draw_cube(GLuint shaderProgram);
bool      apply_move(t_move move, float rad);

bool      move_front(float rad);
bool      move_right(float rad);
bool      move_back(float rad);
bool      move_left(float rad);
bool      move_up(float rad);
bool      move_down(float rad);
bool      move_rev_front(float rad);
bool      move_rev_right(float rad);
bool      move_rev_back(float rad);
bool      move_rev_left(float rad);
bool      move_rev_up(float rad);
bool      move_rev_down(float rad);

#endif
