/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:07:16 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/08 16:48:16 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Heuristic.hpp"

/*
** Constructor - Destructor Methods
*/

Heuristic::Heuristic() : h(MANH)
{
	return ;
}

Heuristic::Heuristic(short h_func) : h(h_func)
{
	return ;
}

Heuristic::~Heuristic()
{
	return ;
}

/*
** Private Methods
*/

int	Heuristic::_manhattan_distance(int a_x, int a_y, int t_x, int t_y) const
{
	return (std::abs((float)(a_x - t_x)) + std::abs((float)(a_y - t_y)));
}

int	Heuristic::_diagonal_distance(int a_x, int a_y, int t_x, int t_y) const
{
	return (std::max(std::abs((float)(a_x - t_x)), std::abs((float)(a_y - t_y))));
}

int	Heuristic::_euclidian_distance(int a_x, int a_y, int t_x, int t_y) const
{
	return std::sqrt(std::pow((float)(a_x - t_x), 2) + std::pow((float)(a_y - t_y), 2));
}

/*
** Public Methods
*/

int	Heuristic::heuristic(int a_x, int a_y, int t_x, int t_y) const
{
	return (this->*f_heuristic[this->h])(a_x, a_y, t_x, t_y);
}