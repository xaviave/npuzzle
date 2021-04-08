/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   py_launch.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:12:59 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/08 16:37:51 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzleHandler.hpp"

extern "C" {
	void launch_solver(int size, int *grid, int *solution)
	{
		std::cout << "here" << std::endl;
		Node p(size, grid);
		Node s(size, solution);
		NPuzzleHandler nph(p, s);
		nph.solve();
	}
}
