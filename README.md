## Rubik3d

Made in january 2016.

Dynamic lib that display a 3d Rubik's cube, handle keyboard and mouse control, auto shuffle the Rubik's cube given a set of instructions as a string.

It uses [glm](http://glm.g-truc.net/0.9.8/index.html) for math.


### IMPORTANT :

This is currently in the process of being rebuilt properly, with proper object oriented behavior, better choice in container, RAII etc ...

Though this is a C++ project, the code use mostly the C part of C++, and gather many mistakes and clumsiness.

I built this in about a week, as a bonus for a 42 school project which asked to solve a Rubik's cube using some algorithm of our own.

I learned OpenGL at this occasion.

### dependancies

libsdl2-dev
libglew-dev

### USAGE
Runs on linux

`make test`

Example :
`./test.sh ./rubik3d "F R U2 B' L' D'"`

### Controls :

* Mouse : turn around the cube
* r s : rotate right
* l m : rotate left
* u v : rotate up
* d e : rotate down
* b c : rotate back
* f g : rotate front
* Renter : if a valid move string is provided, auto shuffle the Rubik's cuke
