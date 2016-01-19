#include <rubik3d.hpp>

int		main(int argc, char const *argv[])
{
	std::list<t_move>	*move_list = NULL;

	if (argc > 1)
	{
		move_list = parse(std::string(argv[1]));
	}
	rubik3d(move_list);
	return 0;
}
