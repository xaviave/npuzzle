/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/17 16:46:58 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"

/*
** Constructor - Destructor Methods
*/

Puzzle::Puzzle(const int s) : size(s), length(std::pow(s, 2))
{
	std::cout << "Puzzle Constructor | addr: " << this << std::endl;
	h_n = std::vector<int> (length, 0);
	grid = std::vector<int> (length, 0);
}

Puzzle::Puzzle(Puzzle *obj) : size(obj->size), length(obj->length), h_n(obj->h_n), grid(obj->grid)
{
	std::cout << "Puzzle Constructor | addr: " << this << std::endl;
	return ;
}

Puzzle::Puzzle(const int s, const std::vector<int> g) : size(s), length(std::pow(s, 2)), grid(g)
{
	std::cout << "Puzzle Constructor | addr: " << this << std::endl;
	h_n = std::vector<int> (length, 0);
}


Puzzle::~Puzzle(void)
{
	std::cout << "Puzzle Destructor | addr: " << this << std::endl;
	return ;
}

/*
** Override Methods
*/

/*
** Private Methods
*/

std::vector<int>	Puzzle::_move_left(const int z, std::vector<int> grid)
{
	if ((z % this->size) == 0)
		return {};
	grid[z] = grid[z - 1];
	grid[z - 1] = 0;
	return grid;
}

std::vector<int>	Puzzle::_move_up(const int z, std::vector<int> grid)
{
	if (z < this->size)
		return {};
	grid[z] = grid[z + this->size];
	grid[z + this->size] = 0;
	return grid;
}

std::vector<int>	Puzzle::_move_right(const int z, std::vector<int> grid)
{
	if ((z % this->size) == this->size - 1)
		return {};
	grid[z] = grid[z + 1];
	grid[z + 1] = 0;
	return grid;
}

std::vector<int>	Puzzle::_move_down(const int z, std::vector<int> grid)
{
	if (z > (this->length - this->size))
		return {};
	grid[z] = grid[z - this->size];
	grid[z - this->size] = 0;
	return grid;
}

/*
** Public Methods
*/

void Puzzle::_ () const
{
	std::cout << "need print heuristic" << std::endl;
	std::cout << "---- | addr: " << this << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		if (i != 0 && (i % this->size) == 0)
			std::cout << std::endl;
		std::cout << grid[i] << "\t";
	}
	std::cout << std::endl << "----" << std::endl;
}

std::vector<int>	Puzzle::move(int m, const int z)
{
	return (this->*f_move[m])(z, grid);
}
