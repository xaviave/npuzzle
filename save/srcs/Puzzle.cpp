/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/30 11:11:13 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"

/*
** Constructor - Destructor Methods
*/

Puzzle::Puzzle(const int s_) : size(s_), length(std::pow(s_, 2)), f(0), g(0), grid(std::vector<int> (length, 0)), p_ptr(0x0)
{
	std::cout << "[DEBUG]:Puzzle Constructor | addr: " << this << std::endl;
}

Puzzle::Puzzle(Puzzle *obj) : size(obj->size), length(obj->length), f(obj->f), g(obj->g), p_ptr(obj->p_ptr)
{
	std::copy(grid.begin(), grid.begin() + length, obj->grid.begin());
	std::cout << "[DEBUG]:Puzzle Constructor | addr: " << this << std::endl;
}

Puzzle::Puzzle(const int s_, const int f_, const int g_, std::vector<int> grid_, void *p) : size(s_), length(std::pow(s_, 2)), f(f_), g(g_), p_ptr(p)
{
	std::copy(grid.begin(), grid.begin() + length, grid_.begin());
	std::cout << "[DEBUG]:Puzzle Constructor | addr: " << this << std::endl;
}

Puzzle::~Puzzle(void)
{
	std::cout << "[DEBUG]:Puzzle Destructor | addr: " << this << std::endl;
}

/*
** Override Methods
*/

/*
** Private Methods
*/

void	Puzzle::_move_left(const int z)
{
	if ((z % this->size) == 0)
	{
		this->grid.clear();
		return ;
	}
	std::cout << "EXEC MOVE LEFT" <<std::endl;
	this->grid[z] = this->grid[z - 1];
	this->grid[z - 1] = 0;
}

void	Puzzle::_move_up(const int z)
{
	if (z < this->size)
	{
		this->grid.clear();
		return ;
	}
	std::cout << "EXEC MOVE UP" <<std::endl;
	this->grid[z] = this->grid[z - this->size];
	this->grid[z - this->size] = 0;
}

void	Puzzle::_move_right(const int z)
{
	if ((z % this->size) == this->size - 1)
	{
		this->grid.clear();
		return ;
	}
	std::cout << "EXEC MOVE RIGHT" <<std::endl;
	this->grid[z] = this->grid[z + 1];
	this->grid[z + 1] = 0;
}

void	Puzzle::_move_down(const int z)
{
	if (z >= (this->length - this->size))
	{
		this->grid.clear();
		return ;
	}
	std::cout << "EXEC MOVE DOWN" <<std::endl;
	this->grid[z] = this->grid[z + this->size];
	this->grid[z + this->size] = 0;
}

/*
** Public Methods
*/

void	Puzzle::_ (const std::string &name) const
{
	std::cout << std::endl << "______________________________________" <<std::endl;
	std::cout << name << std::endl << "addr: " << this << " | p_ptr: " << this->p_ptr << std::endl;
	std::cout << "f = " << this->f << " | cost = " << this->g << std::endl;
	if (this->grid.size())
	{
		std::cout << "-------------" <<std::endl;
		for (size_t i = 0; i < this->grid.size(); i++)
		{
			if (i != 0 && (i % this->size) == 0)
				std::cout << std::endl;
			std::cout << this->grid[i] << "\t";
		}
		std::cout << std::endl << "-------------" << std::endl;
	}
	else
		std::cout << "grid is empty" << std::endl;	
	std::cout << "______________________________________" <<std::endl;
}

void	Puzzle::move(int m, const int z)
{
	(this->*f_move[m])(z);
}
