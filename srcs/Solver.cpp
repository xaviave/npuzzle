/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:10:21 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/18 17:17:19 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"
#include "Solver.hpp"

/*
** Constructor - Destructor Methods
*/

Solver::Solver()
{
	return ;
}

Solver::~Solver()
{
	return ;
}

/*
** Private Methods
*/

int		Solver::_get_zero_coord(const std::vector<int> g) const
{
	for (auto i: g)
		if (!g[i])
			return (i);
	return (0);
}

int 	Solver::_get_cost(const int a_pos, const int t_pos, const int size) const
{
	/*
	** Calculate the cost between
	** actual number pos (a_pos) and target number pos (t_pos)
	** using predefined heurist function
	**
	** a_pos and t_pos coord are transformed from 1D coord to 2D
	*/
	return (this->heuristic((int)(a_pos / size), a_pos % size, (int)(t_pos / size), t_pos % size));
}

int		Solver::_calculate_f(const std::vector<int> p_grid, const Puzzle s) const
{
	int	h = 0;

	for (int i = 0; i < s.length; i++)
		h += this->_get_cost(this->get_number_index(p_grid, i), this->get_number_index(s.grid, i), s.size);
	return (h);
}

int		Solver::_check_f(std::vector<Puzzle> l, int f)
{
	if (!l.size())
		return (0);
	for (size_t i = 0; i < l.size(); i++)
		if (f < l[i].f)
			return (i);
	return (-1);
}

void	Solver::_exec_moves(std::vector<Puzzle> openset, std::vector<Puzzle> closeset, Puzzle p, Puzzle s)
{
	/*
	** Execute every possible move (LEFT / UP / RIGHT / DOWN)
	** If a move is executed, a new puzzle is created with parent ptr saved
	** and added to a vector (openset)
	**
	** Then the cost for every instance is calculated
	*/
	int			f;
	int			pos;
	static int	z = this->_get_zero_coord(p.grid);
	
	for (int i = 0; i < 4; i++)
	{
		std::cout << "____________________________________________"<< std::endl;
		std::vector<int> tmp(p.move(i, z));
		std::cout << !tmp.empty() << std::endl;
		if (!tmp.empty())
		{
			f = this->_calculate_f(tmp, s) + p.cost + 1;
			// get the pos of puzzle to keep the openset sorted
			pos = this->_check_f(openset, f);
			if (pos != -1 && this->_check_f(closeset, f) != -1)
			{
				openset.insert(openset.begin() + pos, Puzzle(p.size, f, p.cost + 1, tmp, &p));
				openset[pos]._("last openset");
			}
		}
	}
}

/*
** Public Methods
*/

int		Solver::get_number_index(const std::vector<int> g, int nu) const
{
	return (std::distance(g.begin(), std::find(g.begin(), g.end(), nu)));
}

int		Solver::_generate_path_solution(Puzzle resolve)
{
	return (resolve.size);
}

int 	Solver::a_star(Puzzle base, Puzzle s)
{
	std::vector<int> tmp;
	std::vector<Puzzle> openset;
	std::vector<Puzzle> closeset;

	openset.push_back(Puzzle(&base));
	while (openset.size())
	{
		Puzzle t_(openset[0]);
		openset.erase(openset.begin());
		if (t_.grid == s.grid)
			return (this->_generate_path_solution(t_));
		this->_exec_moves(openset, closeset, t_, s);
		closeset.push_back(t_);
	}
	s._("solution");
	return (1);
}
