#include <rubik.hpp>


t_rubik   *rubiksCube[3][3][3];
const glm::vec3 transtab[27] = {
      // x     y     z
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

      {-1.0f, 1.0f, -1.0f}, // LINE BACK UP
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
    		case (M_FRONT) : move_front(rad); break;
    		case (M_RIGHT) : move_right(rad); break;
    		case (M_BACK): move_back(rad); break;
    		case (M_LEFT): move_left(rad); break;
    		case (M_UP): move_up(rad); break;
    		case (M_DOWN): move_down(rad); break;
    		case (M_REV_FRONT): move_rev_front(rad); break;
    		case (M_REV_RIGHT): move_rev_right(rad); break;
    		case (M_REV_BACK): move_rev_back(rad); break;
    		case (M_REV_LEFT): move_rev_left(rad); break;
    		case (M_REV_UP): move_rev_up(rad); break;
    		case (M_REV_DOWN): move_rev_down(rad); break;
    		case (M_DOUBLE_FRONT): break;
    		case (M_DOUBLE_RIGHT): break;
    		case (M_DOUBLE_BACK): break;
    		case (M_DOUBLE_LEFT): break;
    		case (M_DOUBLE_UP): break;
    		case (M_DOUBLE_DOWN): break;
			case (NONE):break;
  }
}

void draw_cube(GLuint shaderProgram)
{
  GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
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

void move_front(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, -rad)));
        rubiksCube[0][j][i]->post_rot = glm::toMat4(MyQuat * rubiksCube[0][j][i]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[0][j][i]->quat = MyQuat * rubiksCube[0][j][i]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][0][0];
    rubiksCube[0][0][0] = rubiksCube[0][2][0];
    rubiksCube[0][2][0] = rubiksCube[0][2][2];
    rubiksCube[0][2][2] = rubiksCube[0][0][2];
    rubiksCube[0][0][2] = tmp;
    tmp = rubiksCube[0][0][1];
    rubiksCube[0][0][1] = rubiksCube[0][1][0];
    rubiksCube[0][1][0] = rubiksCube[0][2][1];
    rubiksCube[0][2][1] = rubiksCube[0][1][2];
    rubiksCube[0][1][2] = tmp;
  }
}

void move_rev_front(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, rad)));
        rubiksCube[0][j][i]->post_rot = glm::toMat4(MyQuat * rubiksCube[0][j][i]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[0][j][i]->quat = MyQuat * rubiksCube[0][j][i]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][0][0];
    rubiksCube[0][0][0] = rubiksCube[0][0][2];
    rubiksCube[0][0][2] = rubiksCube[0][2][2];
    rubiksCube[0][2][2] = rubiksCube[0][2][0];
    rubiksCube[0][2][0] = tmp;
    tmp = rubiksCube[0][0][1];
    rubiksCube[0][0][1] = rubiksCube[0][1][2];
    rubiksCube[0][1][2] = rubiksCube[0][2][1];
    rubiksCube[0][2][1] = rubiksCube[0][1][0];
    rubiksCube[0][1][0] = tmp;
  }
}


void move_back(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, rad)));
        rubiksCube[2][j][i]->post_rot = glm::toMat4(MyQuat * rubiksCube[2][j][i]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[2][j][i]->quat = MyQuat * rubiksCube[2][j][i]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[2][0][0];
    rubiksCube[2][0][0] = rubiksCube[2][0][2];
    rubiksCube[2][0][2] = rubiksCube[2][2][2];
    rubiksCube[2][2][2] = rubiksCube[2][2][0];
    rubiksCube[2][2][0] = tmp;
    tmp = rubiksCube[2][0][1];
    rubiksCube[2][0][1] = rubiksCube[2][1][2];
    rubiksCube[2][1][2] = rubiksCube[2][2][1];
    rubiksCube[2][2][1] = rubiksCube[2][1][0];
    rubiksCube[2][1][0] = tmp;
  }
}

void move_rev_back(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, -rad)));
        rubiksCube[2][j][i]->post_rot = glm::toMat4(MyQuat * rubiksCube[2][j][i]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[2][j][i]->quat = MyQuat * rubiksCube[2][j][i]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[2][0][0];
    rubiksCube[2][0][0] = rubiksCube[2][2][0];
    rubiksCube[2][2][0] = rubiksCube[2][2][2];
    rubiksCube[2][2][2] = rubiksCube[2][0][2];
    rubiksCube[2][0][2] = tmp;
    tmp = rubiksCube[2][0][1];
    rubiksCube[2][0][1] = rubiksCube[2][1][0];
    rubiksCube[2][1][0] = rubiksCube[2][2][1];
    rubiksCube[2][2][1] = rubiksCube[2][1][2];
    rubiksCube[2][1][2] = tmp;
  }
}

void move_up(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, -rad, 0.0f)));
        rubiksCube[i][0][j]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][0][j]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][0][j]->quat = MyQuat * rubiksCube[i][0][j]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][0][0];
    rubiksCube[0][0][0] = rubiksCube[0][0][2];
    rubiksCube[0][0][2] = rubiksCube[2][0][2];
    rubiksCube[2][0][2] = rubiksCube[2][0][0];
    rubiksCube[2][0][0] = tmp;
    tmp = rubiksCube[0][0][1];
    rubiksCube[0][0][1] = rubiksCube[1][0][2];
    rubiksCube[1][0][2] = rubiksCube[2][0][1];
    rubiksCube[2][0][1] = rubiksCube[1][0][0];
    rubiksCube[1][0][0] = tmp;
  }
}

void move_rev_up(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, rad, 0.0f)));
        rubiksCube[i][0][j]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][0][j]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][0][j]->quat = MyQuat * rubiksCube[i][0][j]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][0][0];
    rubiksCube[0][0][0] = rubiksCube[2][0][0];
    rubiksCube[2][0][0] = rubiksCube[2][0][2];
    rubiksCube[2][0][2] = rubiksCube[0][0][2];
    rubiksCube[0][0][2] = tmp;
    tmp = rubiksCube[0][0][1];
    rubiksCube[0][0][1] = rubiksCube[1][0][0];
    rubiksCube[1][0][0] = rubiksCube[2][0][1];
    rubiksCube[2][0][1] = rubiksCube[1][0][2];
    rubiksCube[1][0][2] = tmp;
  }
}

void move_down(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, rad, 0.0f)));
        rubiksCube[i][2][j]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][2][j]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][2][j]->quat = MyQuat * rubiksCube[i][2][j]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][2][0];
    rubiksCube[0][2][0] = rubiksCube[2][2][0];
    rubiksCube[2][2][0] = rubiksCube[2][2][2];
    rubiksCube[2][2][2] = rubiksCube[0][2][2];
    rubiksCube[0][2][2] = tmp;
    tmp = rubiksCube[0][2][1];
    rubiksCube[0][2][1] = rubiksCube[1][2][0];
    rubiksCube[1][2][0] = rubiksCube[2][2][1];
    rubiksCube[2][2][1] = rubiksCube[1][2][2];
    rubiksCube[1][2][2] = tmp;
  }
}

void move_rev_down(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(0.0f, -rad, 0.0f)));
        rubiksCube[i][2][j]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][2][j]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][2][j]->quat = MyQuat * rubiksCube[i][2][j]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][2][0];
    rubiksCube[0][2][0] = rubiksCube[0][2][2];
    rubiksCube[0][2][2] = rubiksCube[2][2][2];
    rubiksCube[2][2][2] = rubiksCube[2][2][0];
    rubiksCube[2][2][0] = tmp;
    tmp = rubiksCube[0][2][1];
    rubiksCube[0][2][1] = rubiksCube[1][2][2];
    rubiksCube[1][2][2] = rubiksCube[2][2][1];
    rubiksCube[2][2][1] = rubiksCube[1][2][0];
    rubiksCube[1][2][0] = tmp;
  }
}

void move_right(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(-rad, 0.0f, 0.0f)));
        rubiksCube[i][j][2]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][j][2]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][j][2]->quat = MyQuat * rubiksCube[i][j][2]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][0][2];
    rubiksCube[0][0][2] = rubiksCube[0][2][2];
    rubiksCube[0][2][2] = rubiksCube[2][2][2];
    rubiksCube[2][2][2] = rubiksCube[2][0][2];
    rubiksCube[2][0][2] = tmp;
    tmp = rubiksCube[0][1][2];
    rubiksCube[0][1][2] = rubiksCube[1][2][2];
    rubiksCube[1][2][2] = rubiksCube[2][1][2];
    rubiksCube[2][1][2] = rubiksCube[1][0][2];
    rubiksCube[1][0][2] = tmp;
  }
}

void move_rev_right(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(rad, 0.0f, 0.0f)));
        rubiksCube[i][j][2]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][j][2]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][j][2]->quat = MyQuat * rubiksCube[i][j][2]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][0][2];
    rubiksCube[0][0][2] = rubiksCube[2][0][2];
    rubiksCube[2][0][2] = rubiksCube[2][2][2];
    rubiksCube[2][2][2] = rubiksCube[0][2][2];
    rubiksCube[0][2][2] = tmp;
    tmp = rubiksCube[0][1][2];
    rubiksCube[0][1][2] = rubiksCube[1][0][2];
    rubiksCube[1][0][2] = rubiksCube[2][1][2];
    rubiksCube[2][1][2] = rubiksCube[1][2][2];
    rubiksCube[1][2][2] = tmp;
  }
}


void move_left(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(rad, 0.0f, 0.0f)));
        rubiksCube[i][j][0]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][j][0]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][j][0]->quat = MyQuat * rubiksCube[i][j][0]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][0][0];
    rubiksCube[0][0][0] = rubiksCube[2][0][0];
    rubiksCube[2][0][0] = rubiksCube[2][2][0];
    rubiksCube[2][2][0] = rubiksCube[0][2][0];
    rubiksCube[0][2][0] = tmp;
    tmp = rubiksCube[0][1][0];
    rubiksCube[0][1][0] = rubiksCube[1][0][0];
    rubiksCube[1][0][0] = rubiksCube[2][1][0];
    rubiksCube[2][1][0] = rubiksCube[1][2][0];
    rubiksCube[1][2][0] = tmp;
  }
}

void move_rev_left(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        MyQuat = glm::quat(glm::radians(glm::vec3(-rad, 0.0f, 0.0f)));
        rubiksCube[i][j][0]->post_rot = glm::toMat4(MyQuat * rubiksCube[i][j][0]->quat);
        if (rad == 90.0f)
        {
            rubiksCube[i][j][0]->quat = MyQuat * rubiksCube[i][j][0]->quat;
            done = true;
        }
        id++;
    }
  }
  if (done)
  {
    t_rubik *tmp = rubiksCube[0][0][0];
    rubiksCube[0][0][0] = rubiksCube[0][2][0];
    rubiksCube[0][2][0] = rubiksCube[2][2][0];
    rubiksCube[2][2][0] = rubiksCube[2][0][0];
    rubiksCube[2][0][0] = tmp;
    tmp = rubiksCube[0][1][0];
    rubiksCube[0][1][0] = rubiksCube[1][2][0];
    rubiksCube[1][2][0] = rubiksCube[2][1][0];
    rubiksCube[2][1][0] = rubiksCube[1][0][0];
    rubiksCube[1][0][0] = tmp;
  }
}
