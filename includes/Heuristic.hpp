/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:02:28 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/17 13:24:32 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# include <cmath>
# include <algorithm>

class Heuristic
{
	typedef float	(Heuristic::*hptr)(int a_x, int a_y, int t_x, int t_y) const;
	public:
		short		h;

		Heuristic();
		Heuristic(short h_func);
		~Heuristic();
		
		hptr 		f_heuristic[4] = {&Heuristic::_manhattan_distance, &Heuristic::_euclidian_distance, &Heuristic::_diagonal_distance};
		float		heuristic(int a_x, int a_y, int t_x, int t_y) const;
	private:
		float		_manhattan_distance(int a_x, int a_y, int t_x, int t_y) const;
		float		_euclidian_distance(int a_x, int a_y, int t_x, int t_y) const;
		float		_diagonal_distance(int a_x, int a_y, int t_x, int t_y) const;

};

#endif
