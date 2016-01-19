#include <rubik3d.hpp>

void	clean_sdl(sdl_t *sdl_var)
{
	SDL_GL_DeleteContext(sdl_var->context);
    SDL_Quit();
}
