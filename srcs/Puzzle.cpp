/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/22 14:01:36 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"

/*
** Constructor - Destructor Methods
*/

Puzzle::Puzzle(const int s) : size(s), length(std::pow(s, 2)), f(0), g(0), p_ptr(0x0)
{
	// std::cout << "[DEBUG]:Puzzle Constructor | addr: " << this << std::endl;
	grid = std::vector<int> (length, 0);
}

Puzzle::Puzzle(Puzzle *obj) : size(obj->size), length(obj->length), f(obj->f), g(obj->g), grid(obj->grid),p_ptr(obj->p_ptr)
{
	// std::cout << "[DEBUG]:Puzzle Constructor | addr: " << this << std::endl;
	return ;
}

Puzzle::Puzzle(const int s, const int f_, const int g_, const std::vector<int> grid_, void *p) : size(s), length(std::pow(s, 2)), f(f_), g(g_), grid(grid_), p_ptr(p)
{
	// std::cout << "[DEBUG]:Puzzle Constructor | addr: " << this << std::endl;
	return ;
}

Puzzle::~Puzzle(void)
{
	// std::cout << "[DEBUG]:Puzzle Destructor | addr: " << this << std::endl;
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
	grid[z] = grid[z - this->size];
	grid[z - this->size] = 0;
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
	// std::cout << z << " " << this->length - this->size<< std::endl;
	if (z >= (this->length - this->size))
		return {};
	grid[z] = grid[z + this->size];
	grid[z + this->size] = 0;
	return grid;
}

/*
** Public Methods
*/

void Puzzle::_ (const std::string &name) const
{
	std::cout << std::endl << "______________________________________" <<std::endl;
	std::cout << name << std::endl << "addr: " << this << " | p_ptr: " << this->p_ptr << std::endl;
	std::cout << "f (h + g) = " << this->f << " | cost g = " << this->g << std::endl;
	std::cout << "-------------" <<std::endl;
	for (int i = 0; i < this->length; i++)
	{
		if (i != 0 && (i % this->size) == 0)
			std::cout << std::endl;
		std::cout << grid[i] << "\t";
	}
	std::cout << std::endl << "-------------" << std::endl;
	std::cout << "______________________________________" <<std::endl;
}

std::vector<int>	Puzzle::move(int m, const int z)
{
	return (this->*f_move[m])(z, this->grid);
}
