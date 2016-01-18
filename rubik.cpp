#include <rubik.hpp>


t_rubik   *rubiksCube[3][3][3];
const glm::vec3 transtab[27] = {
      {-1.0f, 1.0f, 1.0f}, // LINE FRONT UP
      { 0.0f, 1.0f, 1.0f}, //
      { 1.0f, 1.0f, 1.0f}, //

      {-1.0f, 0.0f, 1.0f}, // LINE FRONT MID
      {0.0f, 0.0f, 1.0f},
      {1.0f, 0.0f, 1.0f},

      {-1.0f, -1.0f, 1.0f}, // LINE FRONT BOT
      {0.0f, -1.0f, 1.0f},
      {1.0f, -1.0f, 1.0f},

      {-1.0f, 1.0f, 0.0f}, // LINE MID UP
      {0.0f, 1.0f, 0.0f}, //
      {1.0f, 1.0f, 0.0f}, //

      {-1.0f, 0.0f, 0.0f}, // LINE MID MID
      {0.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},

      {-1.0f, -1.0f, 0.0f}, // LINE MID BOT
      {0.0f, -1.0f, 0.0f},
      {1.0f, -1.0f, 0.0f},

      {-1.0f, 1.0f, -1.0f}, // LINE MID UP
      {0.0f, 1.0f, -1.0f}, //
      {1.0f, 1.0f, -1.0f}, //

      {-1.0f, 0.0f, -1.0f}, // LINE MID MID
      {0.0f, 0.0f, -1.0f},
      {1.0f, 0.0f, -1.0f},

      {-1.0f, -1.0f, -1.0f}, // LINE MID BOT
      {0.0f, -1.0f, -1.0f},
      {1.0f, -1.0f, -1.0f},

};

glm::mat4   get_rubik_translation(int id)
{
  return  glm::translate(transtab[id]);
}
void init_rubik()
{

  int id = 0;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 3; k++)
      {
        rubiksCube[i][j][k] = new t_rubik;
        rubiksCube[i][j][k]->id = id;
        rubiksCube[i][j][k]->trans = glm::translate(transtab[id]);
        rubiksCube[i][j][k]->rot_x = glm::mat4(1.0f);
        rubiksCube[i][j][k]->rot_y = glm::mat4(1.0f);
        rubiksCube[i][j][k]->rot_z = glm::mat4(1.0f);

        id++;
      }
    }

  }
}

void move_front(float rad)
{
  int id = 0;
  glm::mat4 Rot;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        printf("move front id %d\n", rubiksCube[i][j][0]->id);
        rubiksCube[i][j][0]->rot_z = glm::rotate(Rot, glm::radians(rad),glm::vec3(0.0f, 0.0f, 1.0f));
        id++;
    }
  }
}

void draw_cube(GLuint shaderProgram)
{
  GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
  glm::mat4 Model = glm::mat4(1.0f);

  glm::mat4 ProjectionMatrix = getProjectionMatrix();
  glm::mat4 ViewMatrix = getViewMatrix();
  glm::mat4 ModelMatrix = glm::mat4(1.0);
  glm::mat4 Scale = glm::scale(glm::vec3(0.5f, 0.5f ,0.5f));

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 3; k++)
      {
    // glm::mat4 Trans = get_rubik_translation(i);
      glm::mat4 Trans = rubiksCube[i][j][k]->trans;
      glm::mat4 Rot = rubiksCube[i][j][k]->rot_z;
      glm::mat4 mvp = ProjectionMatrix * ViewMatrix * Rot * Trans * Scale * ModelMatrix; // Remember, matrix multiplication is the other way around
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    }
  }

}
