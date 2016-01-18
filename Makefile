
NAME=rubik3d

SRC= main.cpp \
	init.cpp \
	clean.cpp \
	cube_vertices.cpp \
	shaders.cpp \
	glsl.cpp \
	controls.cpp \
	rubik.cpp 
OBJ= $(SRC:.cpp=.o)

all= $(NAME)

CC= g++

FLAGS= --std=c++11

UNAME_S := $(shell uname -s)

INC= -I .
ifeq ($(UNAME_S),Linux)
LIB= -lSDL2 -lGLEW -lGL
endif
ifeq ($(UNAME_S),Darwin)
LIB= -L $(HOME)/.brew/lib/ -lSDL2 -lGLEW -framework OpenGL
INC+= -I $(HOME)/.brew/Cellar/glew/1.13.0/include/ -I $(HOME)/.brew/Cellar/sdl2/2.0.4/include/
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LIB)

%.o:%.cpp
	$(CC) $(FLAGS) -c $^ -o $@ $(INC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
