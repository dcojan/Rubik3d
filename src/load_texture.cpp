#include <rubik3d.hpp>

const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};

GLuint    loadBMP(const char *imagepath)
{
  unsigned char header[54]; //Each BMP file begins by a 54-bytes header
  unsigned int dataPos; // Position in the file where the actual fata begins
  unsigned int width, height;
  unsigned int imageSize; // width * height * 3;
  // Actual RGB data
  unsigned char * data;

  FILE * file = fopen(imagepath, "rb");
  if (!file)
  {
    printf("image could not be open");
    return 0;
  }
  if (fread(header, 1, 54, file) != 54)
  {
    printf("not a correc BMP file\n");
  }
  if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    return 0;
  }
  // Read ints from the byte array
 dataPos    = *(int*)&(header[0x0A]);
 imageSize  = *(int*)&(header[0x22]);
 width      = *(int*)&(header[0x12]);
 height     = *(int*)&(header[0x16]);
 // Some BMP files are misformatted, guess missing information
if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
if (dataPos==0)      dataPos=54; // The BMP header is done that way
// Create a buffer
 data = new unsigned char [imageSize];
 // Read the actual data from the file into the buffer
 fread(data,1,imageSize,file);
 //Everything is in memory now, the file can be closed
 fclose(file);

 // Create one OpenGL texture
 GLuint textureID;
 glGenTextures(1, &textureID);
 // "Bind" the newly created texture : all future texture functions will modify this texture
 glBindTexture(GL_TEXTURE_2D, textureID);
 // Give the image to OpenGL
 glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR,
    GL_UNSIGNED_BYTE, data);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 return textureID;
}
struct tga_header
{
  unsigned char idLength;
  unsigned char colorMapType;
  unsigned char imageTypeCode;
  unsigned char colorMapSpec[5];
  unsigned short xOrigin;
  unsigned short yOrigin;
  unsigned short width;
  unsigned short height;
  unsigned char bpp;
  unsigned char imageDesc;
};

GLuint    loadTGA(const char* filename)
{
  std::fstream filestr;
  struct tga_header   tgaheader;
char * imageData;
  	filestr.open (filename, std::fstream::in | std::fstream::binary);								// Open file
  	if (filestr.is_open())														// Do the following actions, if file is opened
  	{
  		// read TGA header
  		filestr.read((char*) &tgaheader , sizeof(struct tga_header));			// Read tga header. For more information: see tga.h and link above
  		// printf("image type: %i n", tgaheader.imageTypeCode);

  		// read pixel data
  		int imageSize = tgaheader.width * tgaheader.height * tgaheader.bpp;		// Calculate image size

  		 imageData = (char*) malloc(imageSize);							// Reserve space in the memory to store our image data
  		filestr.read((char*) imageData, imageSize);						// Read image data from file, into the reserved memory place


  		/*
  		 * TGA is stored in BGR (Blue-Green-Red) format,
  		 * we need to convert this to Red-Green-Blue (RGB).
  		 * The following section does BGR to RGB conversion
  		 */
      //
  		// if (tgaheader.bpp == 24)
  		// {
  		// 	for (int i = 0; i < imageSize; i+=3)
  		// 	{
  		// 		char c = imageData[i];
  		// 		imageData[i] = imageData[i+2];
  		// 		imageData[i+2] = c;
  		// 	}
  		// }
  		// else
  		// if (tgaheader.bpp == 32)
  		// {
  		// 	for (int i = 0; i < imageSize; i+=4)
  		// 	{
  		// 		// 32 bits per pixel   =  4 byte per pixel
  		// 		char c = imageData[i];
  		// 		imageData[i] = imageData[i+2];
  		// 		imageData[i+2] = c;
  		// 	}
  		// }

  		filestr.close();
  	}
  	else
  	{
  		std::cout << "Error opening file" << std::endl;
  		return -1;
  	}
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, tgaheader.width, tgaheader.height, 0, GL_BGR_EXT,
       GL_UNSIGNED_BYTE, imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return textureID;
  return (0);
}
typedef struct
{
    unsigned char imageTypeCode;
    short int imageWidth;
    short int imageHeight;
    unsigned char bitCount;
    unsigned char *imageData;
} TGAFILE;

GLuint LoadTGAFile(const char *filename)
{
    TGAFILE tgaFile;
    FILE *filePtr;
    unsigned char ucharBad;
    short int sintBad;
    long imageSize;
    int colorMode;
    unsigned char colorSwap;

    // Open the TGA file.
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        return false;
    }

    // Read the two first bytes we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Which type of image gets stored in imageTypeCode.
    fread(&tgaFile.imageTypeCode, sizeof(unsigned char), 1, filePtr);

    // For our purposes, the type code should be 2 (uncompressed RGB image)
    // or 3 (uncompressed black-and-white images).
    if (tgaFile.imageTypeCode != 2 && tgaFile.imageTypeCode != 3)
    {
        fclose(filePtr);
        return false;
    }

    // Read 13 bytes of data we don't need.
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);

    // Read the image's width and height.
    fread(&tgaFile.imageWidth, sizeof(short int), 1, filePtr);
    fread(&tgaFile.imageHeight, sizeof(short int), 1, filePtr);

    // Read the bit depth.
    fread(&tgaFile.bitCount, sizeof(unsigned char), 1, filePtr);

    // Read one byte of data we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Color mode -> 3 = BGR, 4 = BGRA.
    colorMode = tgaFile.bitCount / 8;
    imageSize = tgaFile.imageWidth * tgaFile.imageHeight * colorMode;

    // Allocate memory for the image data.
    tgaFile.imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

    // Read the image data.
    fread(tgaFile.imageData, sizeof(unsigned char), imageSize, filePtr);

    // Change from BGR to RGB so OpenGL can read the image data.
    for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
    {
        colorSwap = tgaFile.imageData[imageIdx];
        tgaFile.imageData[imageIdx] = tgaFile.imageData[imageIdx + 2];
        tgaFile.imageData[imageIdx + 2] = colorSwap;
    }

    fclose(filePtr);
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, tgaFile.imageWidth, tgaFile.imageHeight, 0, GL_BGR_EXT,
       GL_UNSIGNED_BYTE, tgaFile.imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return textureID;
}
