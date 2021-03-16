/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 16:10:58 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"

/*
** Constructor - Destructor Methods
*/

Puzzle::Puzzle(const int s) : size(s)
{
	h_n = std::vector<int> (size * size, 0);
	grid = std::vector<int> (size * size, 0);
}

Puzzle::Puzzle(Puzzle *obj) : size(obj->size), h_n(obj->h_n), grid(obj->grid)
{
	return ;
}

Puzzle::Puzzle(const int s, const std::vector<int> g) : size(s), grid(g)
{
	h_n = std::vector<int> (size * size, 0);
}


Puzzle::~Puzzle(void)
{
	return ;
}

/*
** Override Methods
*/

/*
** Private Methods
*/

/*
** Public Methods
*/

std::vector<int> Puzzle::move_left(const int z, Puzzle p)
{
	if ((z % p.size) == 0)
		return {};
	p.grid[z] = p.grid[z - 1];
	p.grid[z - 1] = 0;
	return p.grid;
}

std::vector<int> Puzzle::move_up(const int z, Puzzle p)
{
	if (z < p.size)
		return {};
	p.grid[z] = p.grid[z + p.size];
	p.grid[z + p.size] = 0;
	return p.grid;
}

std::vector<int> Puzzle::move_right(const int z, Puzzle p)
{
	if ((z % p.size) == p.size - 1)
		return {};
	p.grid[z] = p.grid[z + 1];
	p.grid[z + 1] = 0;
	return p.grid;
}

std::vector<int> Puzzle::move_down(const int z, Puzzle p)
{
	if (z > (p.size * (p.size - 1)))
		return {};
	p.grid[z] = p.grid[z - p.size];
	p.grid[z - p.size] = 0;
	return p.grid;
}

std::vector<int>	Puzzle::run(int i, const int z, Puzzle p)
{
	return (this->*moves[i])(z, p);
}