/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   py_launch.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:12:59 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/09 11:04:41 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzleHandler.hpp"

extern "C" {
	PyNode *launch_solver(int size, int *grid, int *solution)
	{
		Node p(size, grid);
		Node s(size, solution);
		NPuzzleHandler nph(p, s);
		return nph.solve();
	}
}
