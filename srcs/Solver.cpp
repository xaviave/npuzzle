/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:10:21 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/19 16:40:05 by xamartin         ###   ########lyon.fr   */
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

	for (int i = 1; i < s.length; i++)
		h += this->_get_cost(this->get_number_index(p_grid, i), this->get_number_index(s.grid, i), s.size);
	return (h);
}

int		Solver::_get_min_f_pos(std::vector<Puzzle> l) const
{
	int	f = INT_MAX;
	int	ret	= 0;

	std::cout << "openset size == " << l.size() << std::endl;
	if (l.size() == 1)
		return (0);
	for (size_t i = 0; i < l.size(); i++)
	{
		if (l[i].f < f)
		{
			ret = i;
			f = l[i].f;
		}
	}
	return (ret);
}

int		Solver::_in_list(std::vector<Puzzle> *l, const std::vector<int> *grid) const
{
	for (size_t i = 0; i < (*l).size(); i++)
		if ((*l)[i].grid == *grid)
			return (i);
	return (0);`
}

void	Solver::_exec_moves(std::vector<Puzzle> *openset, std::vector<Puzzle> *closeset, Puzzle p, Puzzle s)
{
	int	e_pos;
	int	z = this->_get_zero_coord(p.grid);

	p._("================== ENTER MOVES");
	for (int i = 0; i < 4; i++)
	{
		std::vector<int> tmp(p.move(i, z));
		if (!tmp.empty())
		{
			e_pos = this->_in_list(openset, &tmp);
			if (this->_in_list(closeset, &tmp))
				;
			else if (!e_pos)
				openset->push_back(Puzzle(p.size, this->_calculate_f(tmp, s), p.cost + 1, tmp, &p));
			else if (p.cost + 1 < (*openset)[e_pos].cost)
			{
				{
					(*openset)[e_pos].cost = p.cost + 1;
					(*openset)[e_pos].f = this->_calculate_f(tmp, s) + p.cost + 1;
					(*openset)[e_pos].p_ptr= &p;
				}
			}
		}
	}
	std::cout << "================== EXIT MOVES" << std::endl;
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
	std::cout << "\n\n\n\n\nSolution founded" << std::endl;
	std::exit(1);
	return (resolve.size);
}

int 	Solver::a_star(Puzzle base, Puzzle s)
{
	int	low_f_pos;
	std::vector<int> tmp;
	std::vector<Puzzle> openset;
	std::vector<Puzzle> closeset;
	
	// s._("solution");
	openset.push_back(Puzzle(&base));
	while (openset.size())
	{
		low_f_pos = this->_get_min_f_pos(openset);
		std::cout << "if -1 error | low_pos_f value =  " << low_f_pos << std::endl;
		Puzzle t_(openset[low_f_pos]);
		openset.erase(openset.begin() + low_f_pos);
		closeset.push_back(t_);
		if (t_.grid == s.grid)
			return (this->_generate_path_solution(t_));
		this->_exec_moves(&openset, &closeset, t_, s);
	}
	std::cout << "Not possible to resolve Puzzle" << std::endl;
	for (size_t x = 0; x < openset.size(); x++)
		openset[x]._("x");
	return (1);
}
