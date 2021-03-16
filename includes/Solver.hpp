/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:07:19 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 15:27:23 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>

class Solver
{
	public:
		Solver();
		virtual ~Solver();

		int	a_star(Puzzle base);
		int manhattan_distance();
	private:
		int _get_cost();
		int _get_zero_coord(const std::vector<int> g) const;

};

#endif