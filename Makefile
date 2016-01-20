
NAME=librubik3d.so
TESTNAME=rubik3d

DIRSRC= ./src/
DIROBJ= ./obj/

SRC_TEST = main.cpp

SRC= 	rubik3d.cpp \
	init.cpp \
	clean.cpp \
	cube_vertices.cpp \
	shaders.cpp \
	glsl.cpp \
	controls.cpp \
	rubik.cpp \
	parser.cpp

OBJ= $(SRC:.cpp=.o)
DIROBJS= $(addprefix $(DIROBJ), $(OBJ))

CC= g++ 

FLAGS= --std=c++11 -Wall -Werror -Wextra
UNAME_S := $(shell uname -s)

INC= -I ./includes -I ./glm
ifeq ($(UNAME_S),Linux)
LIB= -lSDL2 -lGLEW -lGL
endif
ifeq ($(UNAME_S),Darwin)
LIB= -L $(HOME)/.brew/lib/ -lSDL2 -lGLEW -framework OpenGL
INC+= -I $(HOME)/.brew/Cellar/glew/1.13.0/include/ -I $(HOME)/.brew/Cellar/sdl2/2.0.4/include/
endif

all: $(NAME)

test: all
	$(CC) $(FLAGS) $(DIRSRC)$(SRC_TEST) $(INC) -L. -lrubik3d -o $(TESTNAME)

$(NAME): $(DIROBJS)
	$(CC) $^ -shared -o $@ $(LIB)
#	$(CC) $^ -o $@ $(LIB)

$(DIROBJ)%.o:$(DIRSRC)%.cpp
	@mkdir -p obj
	$(CC) $(FLAGS) -fPIC -c $^ -o $@ $(INC)

clean:
	rm -rf $(DIROBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
