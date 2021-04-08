/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:07:19 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/07 10:32:32 by xamartin         ###   ########lyon.fr   */
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
		bool operator()(const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) const
		{
			return (lhs->f > rhs->f);
		}
};

struct NodeHasher
{
	public:
		std::size_t operator()(const Node& n) const
		{
			std::hash<int> hasher;
			size_t seed = 0;
			for (int i = 0; i < n.size; i++)
				seed ^= hasher(n.grid[i]) + 0x9e3779b9 + (seed<<6) + (seed>>2);
			return seed;
		}
};

struct VectorHasher
{
    size_t operator()(const std::vector<int>& v) const 
    {
        std::hash<int> hasher;
        size_t seed = 0;
        for (size_t i = 0; i < v.size(); i++)
            seed ^= hasher(v[i]) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
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
		int		_generate_path_solution(std::shared_ptr<Node> resolve, std::map<size_t, std::shared_ptr<Node> > hash_dict);

		// heuristic utils
		int		_get_heuristic(const int a_pos, const int t_pos, const int size) const;
		int		_linear_conflict(const Node& s, const std::vector<int>& grid) const;
		int		_calculate_f(const Node& s, const std::vector<int>& p_grid) const;
};

#endif