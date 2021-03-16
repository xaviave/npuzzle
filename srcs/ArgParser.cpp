/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:54:09 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 16:15:32 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "ArgParser.hpp"

/*
** Constructor - Destructor Methods
*/

ArgParser::ArgParser() : prog_name("Default")
{
	return ;
}

ArgParser::ArgParser(std::string name) : prog_name(name)
{
	return ;
}

ArgParser::~ArgParser()
{
	return ;
}

/*
** Public Methods
*/

void	ArgParser::print_usage() const
{
	std::cerr << "Not implemented" << std::endl;
}

int		ArgParser::check_file(std::string file_name)
{
	std::cout << "Not Implemented - args:" << file_name << std::endl;
	return (1);
}

int		ArgParser::parse_command_line(int ac, char **av)
{
	std::cerr << "Not implemented - args: " << ac << av[0] << std::endl;
	return (0);
}
