/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:10:21 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/18 09:43:56 by xamartin         ###   ########lyon.fr   */
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

int	Solver::get_number_index(const std::vector<int> g, int nu) const
{
	return std::distance(g.begin(), std::find(g.begin(), g.end(), nu));
}

int Solver::a_star(Puzzle base)
{
	std::vector<int> tmp;
	std::vector<Puzzle> openset;
	std::vector<Puzzle> closeset;
	
	openset.push_back(Puzzle(&base));
	static int z = this->_get_zero_coord(base.grid);
	for (int i = 0; i < 4; i++)
	{
		std::vector<int> tmp(base.move(i, z));
		if (!tmp.empty())
			openset.push_back(Puzzle(base.size, tmp));
	}
	return (1);
}
