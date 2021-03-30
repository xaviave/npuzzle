/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:07:19 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/30 11:56:43 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>
# include <string>
# include <queue>
# include <map>

# include "Heuristic.hpp"

struct LowestF
{
	public:
		bool operator()(const Puzzle& p, const Puzzle& c) const
		{
			return (p.f > c.f);
		}
};

template<> struct std::less<Puzzle>
{
	bool operator() (const Puzzle& lhs, const Puzzle& rhs) const
	{
		return (lhs.grid == rhs.grid);
	}
};

class Solver : public Heuristic
{
	public:
		// constructor - destructor
		Solver();
		virtual ~Solver();

		// Methods
		int		a_star(Puzzle& base, Puzzle& s);
		int		get_number_index(const int length, const std::vector<int>& g, const int nu) const;
	
	private:
		int		_generate_path_solution(Puzzle *resolve);

		// heuristic utils
		int		_get_heuristic(const int a_pos, const int t_pos, const int size) const;
		int		_linear_conflict(const Puzzle& s, const std::vector<int>& grid) const;
		int		_calculate_f(const Puzzle& s, const std::vector<int>& p_grid) const;

		// a* search utils
		void	_exec_moves(std::priority_queue<Puzzle, std::vector<Puzzle>,LowestF>& openset, std::map<Puzzle, int>& closeset, Puzzle& p, Puzzle& s);
};

#endif