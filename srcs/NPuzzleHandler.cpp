/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 21:49:24 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzleHandler.hpp"

/*
** Constructor - Destructor Methods
*/

NPuzzleHandler::NPuzzleHandler(const std::string &name)
{
	p = new Puzzle(3);
	prog_name = name;
}

NPuzzleHandler::~NPuzzleHandler(void)
{
	delete p;
}

/*
** Override Methods
*/

void		NPuzzleHandler::print_usage() const
{
	std::cerr << "Usage: " << this->prog_name << std::endl;
	std::cerr << std::endl << "Puzzle resolver using A* search algorithm" << std::endl;
	std::cerr << "\t-f, --puzzle_file\t\tPuzzle file to resolve, override generate_puzzle option" << std::endl;
	std::cerr << "\t-s, --puzzle_size\t\tSize of generated puzzle, must be a int >= 3, default value 3" << std::endl;
	std::cerr << "\t-g, --generate_puzzle\t\tGenerate a [puzzle_size] puzzle" << std::endl;
}

int		NPuzzleHandler::parse_command_line(int ac, char **av)
{
	std::string puzzle_file;

	if (ac == 1)
	{
		std::cout << "Start N-Puzzle with a random 3*3 Puzzle" << std::endl;
		return (1);
	}
	for (int i = 1; i < ac; i++)
	{
		if ((std::string(av[i]) == "-f") || (std::string(av[i]) == "--puzzle_file"))
		{
            if (i + 1 < ac && this->check_file(av[i++]))
                this->puzzle_file = std::string(av[i++]);
			else
			{
                std::cerr << "--puzzle_file option required one file as argument." << std::endl;
                return (0);
            }
			return (1);
        }
		else if ((std::string(av[i]) == "-s") || (std::string(av[i]) == "--puzzle_size"))
		{
            if (i + 1 < ac && this->_is_number(av[++i]))
				this->p->size = std::stoi(av[i]);
			else
			{
                std::cerr << "--size option required one postitive int as argument." << std::endl;
                return (0);
            }
        }
		else if ((std::string(av[i]) == "-g") || (std::string(av[i]) == "--generate_puzzle"))
			;
		else
		{
			this->print_usage();
			return (0);
		}
	}
	return (1);
}

/*
** Private Methods
*/

bool NPuzzleHandler::_is_number(const std::string &s)
{
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int	NPuzzleHandler::_parse_file(const std::string &file_name)
{
	if (file_name.empty())
		return (0);
	std::cout << "Exit Parser - puzzle file open and parsed" << std::endl;
	return (0);
}

int NPuzzleHandler::_generate_puzzle(const int size)
{
	int max = size * size;
	std::vector<int> v(max, 0);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
	std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });
	std::shuffle(std::begin(v), std::end(v), e);
	this->p->grid = v;
	std::cout << "Exit Parser - puzzle genrated" << std::endl;
	return (1);
}

/*
** Public Methods
*/

int NPuzzleHandler::parser()
{
	std::cout << "Enter Parser" << std::endl;
	if (!this->puzzle_file.empty())
		return (this->_parse_file(this->puzzle_file));
	else
		return this->_generate_puzzle(this->p->size);
}

int	NPuzzleHandler::solve()
{
	std::cout << "Enter Solve" << std::endl;
	this->a_star(this->p);
	std::cout << "Exit Solve" << std::endl;
	return (0);
}
