/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:10:21 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 21:59:31 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"
#include "Solver.hpp"

/*
** Constructor - Destructor Methods
*/

Solver::Solver()
{
	return ;
}

Solver::~Solver()
{
	return ;
}

/*
** Private Methods
*/

int Solver::_get_cost()
{
	return (0);
}

int Solver::_get_zero_coord(const std::vector<int> g) const
{
	for (size_t i = 0; i < g.size(); i++)
		if (!g[i])
			return (i);
	return (-1);
}

/*
** Public Methods
*/


int Solver::a_star(Puzzle base)
{
	std::vector<int> tmp;
	std::vector<Puzzle> openset;
	std::vector<Puzzle> closeset;
	
	openset.push_back(Puzzle(&base));
	openset[0]._();
	static int z = this->_get_zero_coord(base.grid);
	std::cout << z << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << i << "00" << std::endl;
		tmp = base.move(i, z, base);
		// abort free invalid pointer here
		if (!tmp.empty())
			openset.push_back(Puzzle(base.size, tmp));
	}
	base._();
	for (size_t i = 0; i < openset.size(); i++)
	{
		openset[i]._();
	}
	return (1);
}

int Solver::manhattan_distance()
{
	return (1);
}
