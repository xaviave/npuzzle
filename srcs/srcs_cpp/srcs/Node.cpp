/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/30 11:11:13 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Node.hpp"

/*
** Constructor - Destructor Methods
*/

Node::Node(const int s_, int * grid_) : size(s_), length(std::pow(s_, 2)), f(0), g(0), grid(std::vector<int> (length, 0)), p_ptr(0x0)
{
	for (int i = 0; i < length; i++)
		grid[i] = grid_[i];
}

Node::Node(const int s_, std::vector<int> grid_) : size(s_), length(std::pow(s_, 2)), f(0), g(0), grid(grid_), p_ptr(0x0)
{
}

Node::Node(std::shared_ptr<Node> obj) : size(obj->size), length(obj->length), f(obj->f), g(obj->g), grid(obj->grid), p_ptr(obj->p_ptr)
{
}

Node::~Node(void)
{
}

/*
** Override Methods
*/

/*
** Private Methods
*/

void	Node::_move_left(const int z)
{
	if ((z % this->size) == 0)
	{
		this->grid.clear();
		return ;
	}
	this->grid[z] = this->grid[z - 1];
	this->grid[z - 1] = 0;
}

void	Node::_move_up(const int z)
{
	if (z < this->size)
	{
		this->grid.clear();
		return ;
	}
	this->grid[z] = this->grid[z - this->size];
	this->grid[z - this->size] = 0;
}

void	Node::_move_right(const int z)
{
	if ((z % this->size) == this->size - 1)
	{
		this->grid.clear();
		return ;
	}
	this->grid[z] = this->grid[z + 1];
	this->grid[z + 1] = 0;
}

void	Node::_move_down(const int z)
{
	if (z >= (this->length - this->size))
	{
		this->grid.clear();
		return ;
	}
	this->grid[z] = this->grid[z + this->size];
	this->grid[z + this->size] = 0;
}

/*
** Public Methods
*/

void	Node::_ (const std::string &name) const
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

void	Node::move(int m, const int z)
{
	(this->*f_move[m])(z);
}
