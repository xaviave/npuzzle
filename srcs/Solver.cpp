/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:10:21 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/23 16:24:33 by xamartin         ###   ########lyon.fr   */
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
	for (size_t _ = 0; _ < g.size(); _++)
		if (!g[_])
			return (_);
	return (-1);
}

int 	Solver::_get_heuristic(const int a_pos, const int t_pos, const int size) const
{
	/*
	** Calculate the g between
	** actual number coord (a_pos) and target number coord (t_pos)
	** using predefined heurist function
	**
	** a_pos and t_pos coord are transformed from 1D coord to 2D
	*/
	return (this->heuristic((int)(a_pos / size), a_pos % size, (int)(t_pos / size), t_pos % size));
}

int		Solver::_linear_conflict(const std::vector<int> grid, const Puzzle s) const
{
	/*
		linear conflit - if 2 elements are not in the good order on the same line,
		it will need 2 moves to swap thoses elements

		x_g for element
		y_g for element neighbour
		x_s for element solution coord
		x_s for element neigbour solution coord
	*/
	int	x_g;
	int	y_g;
	int	x_s;
	int	y_s;
	int	lc = 0;

	for (int r = 0; r < s.size - 1; r++)
	{
		for (int c = 0; c < s.size - 1; c++)
		{
			// line
			x_g = r * s.size + c;
			y_g = r * s.size + c + 1;
			x_s = this->get_number_index(s.grid, grid[x_g]);
			y_s = this->get_number_index(s.grid, grid[y_g]);
			if (grid[x_g] && grid[y_g] &&
				(int)(x_g % s.size) < (int)(y_g % s.size) &&
				(int)(x_s % s.size) > (int)(y_s % s.size) &&
				(x_g / s.size) == (y_g / s.size) &&
				(x_s / s.size) == (y_s / s.size))
				lc++;

			// column
			x_g = r * s.size + c;
			y_g = (r + 1) * s.size + c;
			x_s = this->get_number_index(s.grid, grid[x_g]);
			y_s = this->get_number_index(s.grid, grid[y_g]);
			// std::cout << "x_g | " << (x_g / s.size) << " - " << (x_g % s.size) << std::endl;
			// std::cout << "y_g | " << (y_g / s.size) << " - " << (y_g % s.size) << std::endl;
			// std::cout << "x_s | " << (x_s / s.size) << " - " << (x_s % s.size) << std::endl;
			// std::cout << "y_s | " << (y_s / s.size) << " - " << (y_s % s.size) << std::endl;
			if (grid[x_g] && grid[y_g] &&
				(int)(x_g / s.size) < (int)(y_g / s.size) &&
				(int)(x_s / s.size) > (int)(y_s / s.size) &&
				(x_g % s.size) == (y_g % s.size) &&
				(x_s % s.size) == (y_s % s.size))
				lc++;
		}
	}
	return (lc * 2);
}
int		Solver::_calculate_f(const std::vector<int> p_grid, const Puzzle s) const
{
	int	h = 0;

	for (int i = 1; i < s.length; i++)
		h += this->_get_heuristic(this->get_number_index(p_grid, i), this->get_number_index(s.grid, i), s.size);
	if (this->h == MANH)
	{
		// std::cout << "linear conflitct " << this->_linear_conflict(p_grid, s) << std::endl;
		h += this->_linear_conflict(p_grid, s);
	}
	return (h);
}

int		Solver::_get_min_f_pos(std::vector<Puzzle> l) const
{
	int	f = INT_MAX;
	int	ret	= 0;

	if (l.size() == 1)
		return (0);
	for (size_t _ = 0; _ < l.size(); _++)
	{
		if (l[_].f < f)
		{
			ret = _;
			f = l[_].f;
		}
	}
	std::cout << "low_pos_f value =  " << f << std::endl;
	return (ret);
}

int		Solver::_in_list(std::vector<Puzzle> *l, const std::vector<int> *grid) const
{
	for (size_t _ = 0; _ < (*l).size(); _++)
		if ((*l)[_].grid == *grid)
			return (_);
	return (-1);
}

void	Solver::_exec_moves(std::vector<Puzzle> *openset, std::vector<Puzzle> *closeset, Puzzle p, Puzzle s)
{
	int	g_;
	int	f_;
	int	c_pos;
	int	o_pos;
	int	z = this->_get_zero_coord(p.grid);

	// p._("================== ENTER MOVES");
	for (int i = 0; i < 4; i++)
	{
		std::vector<int> tmp(p.move(i, z));
		if (!tmp.empty())
		{
			g_ = p.g + 1;
			f_ = this->_calculate_f(tmp, s) + g_;
			c_pos = this->_in_list(closeset, &tmp);
			o_pos = this->_in_list(openset, &tmp);


			if (c_pos == -1 && o_pos == -1)
				openset->push_back(Puzzle(p.size, f_, g_, tmp, &p));
			else
			{
				if ()
				(*openset)[o_pos].g = g_;
				(*openset)[o_pos].f = f_;
				(*openset)[o_pos].p_ptr= &p;
			}
		}
	}
	// std::cout << "================== EXIT MOVES" << std::endl;
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
	resolve._("\n\n================================\n================================\n================================\n\n\nSolution founded");
	std::exit(1);
	return (resolve.size);
}

int 	Solver::a_star(Puzzle base, Puzzle s)
{
	int	low_f_pos;
	std::vector<Puzzle> openset;
	std::vector<Puzzle> closeset;
	
	base.f = this->_calculate_f(base.grid, s) + base.g;
	base._("");
	openset.push_back(Puzzle(&base));
	static int i = 0;
	while (!openset.empty())
	{
		if (i++ > 30)
			break;
		low_f_pos = this->_get_min_f_pos(openset);
		Puzzle t_(openset[low_f_pos]);
		// std::cout << "f selected = " << t_.f << std::endl;
		if (t_.grid == s.grid)
			return (this->_generate_path_solution(t_));
		openset.erase(openset.begin() + low_f_pos);
		closeset.push_back(t_);
		this->_exec_moves(&openset, &closeset, t_, s);
	}
	std::cout << "\n\n\n\n\n\n\n\n\nNot possible to resolve Puzzle" << std::endl;
	for (size_t _ = 0; _ < openset.size(); _++)
		openset[_]._("x");
	return (1);
}
