/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:54:09 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/17 16:46:21 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "ArgParser.hpp"

/*
** Constructor - Destructor Methods
*/

ArgParser::ArgParser(const std::string &name) : s_option(3), file_option(""), prog_name(name)
{
	return ;
}

ArgParser::~ArgParser()
{
	return ;
}

/*
** Private Methods
*/

int		ArgParser::_check_file(std::string file_name) const
{
	std::cout << "Not Implemented - args:" << file_name << std::endl;
	return (1);
}

bool 	ArgParser::_is_number(const std::string &s) const
{
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

/*
** Public Methods
*/

void	ArgParser::print_usage() const
{
	std::cerr << "Usage: " << this->prog_name << std::endl;
	std::cerr << std::endl << "Puzzle resolver using A* search algorithm" << std::endl;
	std::cerr << "\t-f, --puzzle_file\t\tPuzzle file to resolve, override generate_puzzle option" << std::endl;
	std::cerr << "\t-s, --puzzle_size\t\tSize of generated puzzle, must be a int >= 3, default value 3" << std::endl;
	std::cerr << "\t-g, --generate_puzzle\t\tGenerate a [puzzle_size] puzzle" << std::endl;
}

int		ArgParser::parse_command_line(int ac, char **av)
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
            if (i + 1 < ac && this->_check_file(av[i++]))
                this->file_option = std::string(av[i++]);
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
				this->s_option = std::stoi(av[i]);
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
