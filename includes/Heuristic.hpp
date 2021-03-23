/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:02:28 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/23 10:06:01 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# include <cmath>
# include <vector>
# include <algorithm>

# define MANH 0
# define EUCL 1
# define DIAG 2

class Heuristic
{
	typedef int	(Heuristic::*hptr)(int a_x, int a_y, int t_x, int t_y) const;
	public:
		short		h;

		Heuristic();
		Heuristic(short h_func);
		~Heuristic();

		hptr 	f_heuristic[3] = {&Heuristic::_manhattan_distance, &Heuristic::_euclidian_distance, &Heuristic::_diagonal_distance};
		int		heuristic(int a_x, int a_y, int t_x, int t_y) const;
	private:
		int		_manhattan_distance(int a_x, int a_y, int t_x, int t_y) const;
		int		_euclidian_distance(int a_x, int a_y, int t_x, int t_y) const;
		int		_diagonal_distance(int a_x, int a_y, int t_x, int t_y) const;

};

#endif
