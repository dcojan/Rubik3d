/// translation matrice
	glm::mat4 myMatrix = glm::translate(glm::vec3({10.0f, 0.0f, 0.0f}));
  glm::vec4 myVector = {10,10,10,1};
  // fill myMatrix and myVector somehow
  glm::vec4 transformedVector = myMatrix * myVector;////
	for (int i = 0; i < 4; i++)
	{
			std::cout << transformedVector[i] << std::endl;
	}
	// multiply matrix and vectors in this order exclusively
// identity matrice
	glm::mat4 myIdentityMatrix = glm::mat4(1.0f);
// scaling
	glm::mat4 myScalingMatrix = glm::scale(glm::vec3(2.0f, 2.0f ,2.0f));
// rotation
//	glm::vec3 myRotationAxis( ??, ??, ??);
 //glm::rotate( angle_in_degrees, myRotationAxis );
// cumulating transformation :
//TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
// This lines actually performs the scaling FIRST, and THEN the rotation, and THEN the translation.

// resume
/*
glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;

The Model Matrice translate Model space coordinates in World Space coordinates
// The view matrix (camera)
 glm::mat4 ViewMatrix = glm::translate(-3.0f, 0.0f ,0.0f);
 glm::mat4 CameraMatrix = glm::lookAt(
      cameraPosition, // the position of your camera, in world space
      cameraTarget,   // where you want to look at, in world space
      upVector        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
  );
	The view matrice translate world space coordinates to camera space coordinates

	// The projection matrix
	// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless

 glm::mat4 projectionMatrix = glm::perspective(
     FoV,         // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
     4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
     0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
     100.0f       // Far clipping plane. Keep as little as possible.
 );
 The projection matrice translate frome camera coordinates to homogeneous coordinates
 Homogeneous Space is : all vertices defined in a small cube, everything inside the cube is obscreen
 cumulation :
 // C++ : compute the matrix
glm::mat4 MVPmatrix = projection * view * model; // Remember : inverted !
// GLSL : apply it
 transformed_vertex = MVP * in_vertex;
*/
