/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:22:01 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/17 16:44:20 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ArgParser.hpp"
#include "NPuzzleHandler.hpp"

int main(int argc, char **argv)
{
	ArgParser	a("N-Puzzle");

	if (a.parse_command_line(argc, argv))
	{
		NPuzzleHandler	n(a.s_option, a.file_option);
		n.parser();
		n.solve();
	}
}