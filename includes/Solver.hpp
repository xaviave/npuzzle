/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:07:19 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/17 14:14:57 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>

# include "Heuristic.hpp"

class Solver : public Heuristic
{
	public:
		// constructor - destructor
		Solver();
		virtual ~Solver();

		// Methods
		int	a_star(Puzzle base);
	private:
		int _get_cost();
		int _get_zero_coord(const std::vector<int> g) const;
};

#endif