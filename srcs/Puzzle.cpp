/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 21:47:06 by xamartin         ###   ########lyon.fr   */
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

void Puzzle::_ () const
{
	std::cout << "need print heuristic" << std::endl;
	std::cout << "----" << std::endl;
	for (size_t i = 0; i < this->grid.size(); i++)
	{
		if (i != 0 && (i % this->size) == 0)
			std::cout << std::endl;
		std::cout << this->grid[i];
	}
	std::cout << std::endl << "----" << std::endl;
}

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

std::vector<int>	Puzzle::move(int i, const int z, Puzzle p)
{
	return (this->*moves[i])(z, p);
}
