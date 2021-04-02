/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:10:21 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/30 12:18:36 by xamartin         ###   ########lyon.fr   */
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

int		Solver::_generate_path_solution(Puzzle *resolve)
{
	std::cout << "\n\n\n\n\nSolution founded" << std::endl;
	std::exit(1);
	return (resolve->size);
}

int		Solver::_linear_conflict(const Puzzle& s, const std::vector<int>& grid) const
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
			x_s = this->get_number_index(s.length, s.grid, grid[x_g]);
			y_s = this->get_number_index(s.length, s.grid, grid[y_g]);
			if (grid[x_g] && grid[y_g] &&
				(int)(x_g % s.size) < (int)(y_g % s.size) &&
				(int)(x_s % s.size) > (int)(y_s % s.size) &&
				(x_g / s.size) == (y_g / s.size) &&
				(x_s / s.size) == (y_s / s.size))
				lc++;

			// column
			x_g = r * s.size + c;
			y_g = (r + 1) * s.size + c;
			x_s = this->get_number_index(s.length, s.grid, grid[x_g]);
			y_s = this->get_number_index(s.length, s.grid, grid[y_g]);
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

int 	Solver::_get_heuristic(const int a_pos, const int t_pos, const int size) const
{
	/*
	** Calculate the g between
	** actual number pos (a_pos) and target number pos (t_pos)
	** using predefined heurist function
	**
	** a_pos and t_pos coord are transformed from 1D coord to 2D
	*/
	return (this->heuristic((int)(a_pos / size), a_pos % size, (int)(t_pos / size), t_pos % size));
}

int		Solver::_calculate_f(const Puzzle& s, const std::vector<int>& p_grid) const
{
	int	h = 0;

	for (int i = 1; i < s.length; i++)
		h += this->_get_heuristic(
			this->get_number_index(s.length, p_grid, i),
			this->get_number_index(s.length, s.grid, i),
			s.size);
	if (this->h == 5)
	{
		// std::cout << "linear conflitct " << this->_linear_conflict(p_grid, s) << std::endl;
		h += this->_linear_conflict(s, p_grid);
	}
	return (h);
}

void	Solver::_exec_moves(
	std::priority_queue<Puzzle, std::vector<Puzzle>,LowestF>& openset,
	std::map<Puzzle, int>& closeset,
	Puzzle& p,
	Puzzle& s
)
{
	int	z = this->get_number_index(p.length, p.grid, 0);

	p._("_exec_moves enter");
	for (int i = 0; i < 4; i++)
	{
		Puzzle p_ = p;
		// p_ have always the same addr / same in the queue?
		// std::cout << &p_ << " | " << &p << std::endl;
		p_.move(i, z);
		if (!p_.grid.empty())
		{
			p_.g = p.g + 1; // g(p) + cost(p->node)
			p_.f = this->_calculate_f(s, p_.grid) + p_.g;
			p_.p_ptr = &p;
			std::cout << "p_ created" << std::endl;
			
			if (closeset.find(p_) != closeset.end())
			{
				std::cout << "founded in closeset" << std::endl;
				p_._("p___");
				for (auto& x: closeset)
					x.first._("");
				std::cout << "END closeset\n\n" << std::endl;
			}
			
			if (closeset.find(p_) == closeset.end())
			{
				std::cout << "added in openset due to closeset foundinf" << std::endl;
				openset.push(p_);
			}
			else if (p.f >  p_.f)
			{
				openset.push(p_);
				std::cout << "added in openset" << std::endl;
			}
		}
		else
			std::cout << "EMPTY TMP" << std::endl;
	}
	std::cout << "_exec_moves exit" << std::endl;
}

/*
** Public Methods
*/

int		Solver::get_number_index(const int length, const std::vector<int>& g, const int nu) const
{
	for (int _ = 0; _ < length; _++)
		if (g[_] == nu)
			return (_);
	return length;
}

int 	Solver::a_star(Puzzle& base, Puzzle& s)
{
	std::priority_queue<Puzzle, std::vector<Puzzle>, LowestF> openset; // priority queue
	std::map<Puzzle, int> closeset; // hash table
	
	openset.push(base);
	while (openset.size())
	{
		Puzzle p(openset.top());
		openset.pop();
		if (p.grid == s.grid)
			return (this->_generate_path_solution(&p));
		closeset[p] = p.g;
		std::cout << "p in closeset | f = " << p.f << " | openset size = " << openset.size() << std::endl;
		this->_exec_moves(openset, closeset, p, s);
	}
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\nNot possible to resolve Puzzle" << std::endl;
	// for (size_t x = 0; x < openset.size(); x++)
	// 	openset[x]._("x");
	return (1);
}
