/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:07:19 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/06 10:28:48 by xamartin         ###   ########lyon.fr   */
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
		bool operator()(const Node& p, const Node& c) const
		{
			return (p.f > c.f);
		}
};

template<> struct std::less<Node>
{
	bool operator() (const Node& lhs, const Node& rhs) const
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
		int		a_star(Node& base, Node& s);
		int		get_number_index(const int length, const std::vector<int>& g, const int nu) const;
	
	private:
		int		_generate_path_solution(Node *resolve);

		// heuristic utils
		int		_get_heuristic(const int a_pos, const int t_pos, const int size) const;
		int		_linear_conflict(const Node& s, const std::vector<int>& grid) const;
		int		_calculate_f(const Node& s, const std::vector<int>& p_grid) const;

		// a* search utils
		void	Solver::_exec_moves(
			std::priority_queue<Node, std::vector<Node>,LowestF>& openset,
			std::unordered_set<std::vector<int> >& closeset,
			Node& p,
			Node& s
		);
};

#endif