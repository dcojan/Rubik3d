#include <rubik.hpp>

enum parsing_state {LETTER, AFTER_LETTER, SPACE};

std::list<t_move>	*parse(std::string entry)
{
	std::list<t_move>					*lst = new std::list<t_move>();
	static const std::string			letters = "FRBLUD";
	size_t								position;
	parsing_state						state = LETTER;
	t_move								move;

	for (auto it = entry.begin(); it != entry.end(); it++)
	{
		switch (state)
		{
		case LETTER:
			if ((position = letters.find(*it)) == std::string::npos)
			{
				std::cout << "not found" << std::endl;
				return NULL;
			}
			move = static_cast<t_move>(position);
			state = AFTER_LETTER;
			break ;
		case AFTER_LETTER:
			switch (*it)
			{
			case '\'':
				lst->push_back(static_cast<t_move>(position + 6));
				state = SPACE;
				break ;
			case '2':
				lst->push_back(move);
				lst->push_back(move);
				state = SPACE;
				break ;
			case ' ':
				lst->push_back(move);
				state = LETTER;
				break ;
			default :
				std::cout << "default" << std::endl;
				return NULL;
			}
			break;
		case SPACE:
			if (*it != ' ')
			{
				std::cout << "not space" << std::endl;
				return NULL;
			}
			state = LETTER;
			break ;
		}
	}
	if (state == LETTER)
		return NULL;
	else if (state == AFTER_LETTER)
		lst->push_back(move);
	return lst;
}
