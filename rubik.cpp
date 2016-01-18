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
        rubiksCube[i][j][k]->post_rot = glm::mat4(1.0f);
        rubiksCube[i][j][k]->rot = glm::mat4(1.0f);
        id++;
      }
    }

  }
}

void apply_move(t_move move, float rad) {
  switch (move) {
    		case (MOVE_FRONT) : move_front(rad); break;
    		case (MOVE_RIGHT) : break;
    		case (MOVE_BACK): break;
    		case (MOVE_LEFT): break;
    		case (MOVE_UP): move_up(rad);break;
    		case (MOVE_DOWN): break;
    		case (MOVE_REV_FRONT): break;
    		case (MOVE_REV_RIGHT): break;
    		case (MOVE_REV_BACK): break;
    		case (MOVE_REV_LEFT): break;
    		case (MOVE_REV_UP): break;
    		case (MOVE_REV_DOWN): break;
    		case (MOVE_DOUBLE_FRONT): break;
    		case (MOVE_DOUBLE_RIGHT): break;
    		case (MOVE_DOUBLE_BACK): break;
    		case (MOVE_DOUBLE_LEFT): break;
    		case (MOVE_DOUBLE_UP): break;
    		case (MOVE_DOUBLE_DOWN): break;
  }
}

void move_front(float rad)
{
  int id = 0;
  // glm::mat4 Rot;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        // printf("move front id %d\n", rubiksCube[i][j][0]->id);
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, rad)));
        rubiksCube[0][j][i]->post_rot = glm::toMat4(MyQuat * rubiksCube[0][j][i]->quat);
        // rubiksCube[0][j][i]->post_rot = glm::rotate(Rot, glm::radians(rad),glm::vec3(0.0f, 0.0f, 1.0f));
        if (rad == 90.0f)
        {
            // rubiksCube[0][j][i]->rot = glm::rotate(Rot, glm::radians(rad),glm::vec3(0.0f, 0.0f, 1.0f)) * rubiksCube[0][j][i]->rot;
//            rubiksCube[0][j][i]->post_rot = glm::mat4(1.0f);
            rubiksCube[0][j][i]->quat = MyQuat * rubiksCube[0][j][i]->quat;
        }
        id++;
    }
  }
}

void move_up(float rad)
{
  int id = 0;
  // glm::mat4 Rot = glm::mat4(1.0f);
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        printf("move up id %d\n", rubiksCube[i][2][j]->id);
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, rad, 0.0f)));
        rubiksCube[i][0][j]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][0][j]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][0][j]->quat = MyQuat * rubiksCube[i][0][j]->quat;
        }
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
  glm::mat4 Rot = glm::mat4(1.0);
  glm::mat4 Scale = glm::scale(glm::vec3(0.5f, 0.5f ,0.5f));

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 3; k++)
      {
      glm::mat4 Trans = rubiksCube[i][j][k]->trans;
      glm::mat4 postRot = rubiksCube[i][j][k]->post_rot;
      Rot = rubiksCube[i][j][k]->rot;
      glm::mat4 mvp = ProjectionMatrix * ViewMatrix * postRot * Trans * Rot * Scale * ModelMatrix; // Remember, matrix multiplication is the other way around
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    }
  }

}
