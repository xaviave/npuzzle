/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:07:19 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/18 17:11:00 by xamartin         ###   ########lyon.fr   */
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
		int		a_star(Puzzle base, Puzzle s);
		int		get_number_index(const std::vector<int> g, int nu) const;
	private:
		int		_generate_path_solution(Puzzle resolve);

		int		_get_zero_coord(const std::vector<int> g) const;
		// heuristic utils
		int		_get_cost(const int a_pos, const int t_pos, const int size) const;
		int		_calculate_f(const std::vector<int> p_grid, const Puzzle s) const;

		// a* search utils
		int		_check_f(std::vector<Puzzle> l, int f);
		void	_exec_moves(std::vector<Puzzle> openset, std::vector<Puzzle> closeset, Puzzle p, Puzzle s);
};

#endif