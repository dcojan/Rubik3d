#include <rubik.hpp>


t_rubik   *rubiksCube[3][3][3];
GLuint position_vbo;
GLuint post_rotation_vbo;
glm::mat4 positions[27];
glm::mat4 post_rotation[27];

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

bool apply_move(t_move move, float rad) {
  switch (move) {
    		case (M_FRONT) :      return move_front(rad); break;
    		case (M_RIGHT) :      return move_right(rad); break;
    		case (M_BACK)  :      return move_back(rad); break;
    		case (M_LEFT)  :      return move_left(rad); break;
    		case (M_UP)    :      return move_up(rad); break;
    		case (M_DOWN)  :      return move_down(rad); break;
    		case (M_REV_FRONT):   return move_rev_front(rad); break;
    		case (M_REV_RIGHT):   return move_rev_right(rad); break;
    		case (M_REV_BACK):    return move_rev_back(rad); break;
    		case (M_REV_LEFT):    return move_rev_left(rad); break;
    		case (M_REV_UP):      return move_rev_up(rad); break;
    		case (M_REV_DOWN):    return move_rev_down(rad); break;
    		case (M_DOUBLE_FRONT): break;
    		case (M_DOUBLE_RIGHT): break;
    		case (M_DOUBLE_BACK):  break;
    		case (M_DOUBLE_LEFT):  break;
    		case (M_DOUBLE_UP):    break;
    		case (M_DOUBLE_DOWN):  break;
			  case (NONE):           break;
  }
  return true;
}

void draw_cube(GLuint shaderProgram)
{
  glBindVertexArray( shaderProgram );
  GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
  glm::mat4 ProjectionMatrix = getProjectionMatrix();
  glm::mat4 ViewMatrix = getViewMatrix();
  glm::mat4 mvp = ProjectionMatrix * ViewMatrix;
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
  // update translation and position
  t_rubik **it = &(rubiksCube[0][0][0]);

  	for (int i = 0 ; i < 27 ; i++)
  	{
      post_rotation[i] = (*it)->post_rot;
      positions[i] = (*it)->trans;
      it++;
  	}
  	glBindBuffer( GL_ARRAY_BUFFER, post_rotation_vbo ); //bind vbo
  	glBufferData( GL_ARRAY_BUFFER, sizeof( glm::mat4 ) * 27, &post_rotation[0][0], GL_DYNAMIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, position_vbo ); //bind vbo
	  glBufferData( GL_ARRAY_BUFFER, sizeof( glm::mat4 ) * 27, &positions[0][0], GL_DYNAMIC_DRAW );

  glDrawArraysInstanced( GL_TRIANGLES, 0, 36, 27);
}

bool move_front(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        if (rad >= 90.0f)
            rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_rev_front(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}


bool move_back(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_rev_back(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_up(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_rev_up(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_down(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_rev_down(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_right(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_rev_right(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}


bool move_left(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}

bool move_rev_left(float rad)
{
  int id = 0;
  bool done = false;
  glm::quat MyQuat;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (rad >= 90.0f)
          rad = 90.0f;
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
    return true;
  }
  return false;
}
