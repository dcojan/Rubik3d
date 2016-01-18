#ifndef RUBIK_HPP
# define RUBIK_HPP
#include <rubik3d.hpp>

typedef struct s_rubik
{
  int       id;
  glm::mat4 trans;
  glm::mat4 rot_x;
  glm::mat4 rot_y;
  glm::mat4 rot_z;
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
void      move_front(float rad);

#endif
