/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:22:01 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 14:27:32 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzleHandler.hpp"

int main(int argc, char **argv)
{
	NPuzzleHandler n("N-Puzzle");

	if (n.parse_command_line(argc, argv))
	{
		n.parser();
		n.solve();
	}
}